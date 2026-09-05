#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
#include <cctype>
#include <type_traits>

using namespace std;

// ==========================================
// Part A: Abstract DataProcessor Interface
// ==========================================
class DataProcessor {
public:
  // Pure virtual functions — all subclasses MUST implement these
  virtual void loadData(const string& source) = 0;
  virtual void processData() = 0;
  virtual void exportResult(const string& destination) = 0;
  virtual string processorType() const = 0;
  virtual int recordCount() const = 0;

  // Non-pure virtual — base provides a default report format
  virtual void printSummary() const {
    cout << "[" << processorType() << "] Summary — Records Processed: " << recordCount() << endl;
  }

  virtual ~DataProcessor() = default;
};

// Concrete Processor: CSVProcessor
class CSVProcessor : public DataProcessor {
  vector<string> records;

public:
  void loadData(const string& source) override {
    // Simulating loading CSV rows
    records = {
      "emp_101,John Doe,Engineering,85000",
      "emp_102,Jane Smith,Marketing,72000",
      "emp_103,Bob Johnson,Sales,68000",
      "emp_104,Alice Brown,HR,65000",
      "emp_105,Charlie White,Finance,90000"
    };
    cout << "[CSVProcessor] Loaded " << records.size() << " records from " << source << endl;
  }

  void processData() override {
    // Converts each record to uppercase
    for (auto& row : records) {
      for (char& c : row) {
        c = toupper(c);
      }
    }
  }

  void exportResult(const string& destination) override {
    cout << "[CSV EXPORT -> " << destination << "]" << endl;
    for (const auto& row : records) {
      cout << "  " << row << endl;
    }
  }

  string processorType() const override {
    return "CSV Processor";
  }

  int recordCount() const override {
    return static_cast<int>(records.size());
  }
};

// Concrete Processor: SensorStreamProcessor
class SensorStreamProcessor : public DataProcessor {
  vector<double> readings;
  double mean = 0.0;
  double minVal = 0.0;
  double maxVal = 0.0;

public:
  void loadData(const string& source) override {
    // Simulating 8 sensor readings
    readings = {23.4, 21.8, 25.1, 24.6, 22.9, 26.3, 23.8, 24.5};
    cout << "[SensorStreamProcessor] Loaded " << readings.size() << " readings from " << source << endl;
  }

  void processData() override {
    if (readings.empty()) return;
    double sum = 0.0;
    minVal = readings[0];
    maxVal = readings[0];

    for (double val : readings) {
      sum += val;
      if (val < minVal) minVal = val;
      if (val > maxVal) maxVal = val;
    }
    mean = sum / readings.size();
  }

  void exportResult(const string& destination) override {
    cout << "[SENSOR EXPORT -> " << destination << "]" << endl;
    cout << "  Statistical Summary => Mean: " << fixed << setprecision(2) << mean
         << " | Min: " << setprecision(1) << minVal << " | Max: " << setprecision(1) << maxVal << endl;
    cout.unsetf(ios_base::floatfield);
    cout << setprecision(6);
  }

  string processorType() const override {
    return "Sensor Stream Processor";
  }

  int recordCount() const override {
    return static_cast<int>(readings.size());
  }

  double getMean() const {
    return mean;
  }
};

// ==========================================
// Part B: Class Template DataBuffer<T>
// ==========================================
/*
 Why template definitions cannot be in a separate .cpp file:
 C++ templates are instantiated at compile time. When a template is used with a concrete
 type (such as DataBuffer<int>), the compiler needs access to the complete implementation
 to generate the machine code for that specific specialization. If the member function
 definitions are placed in a separate .cpp file, the compiler compiles that .cpp without knowing
 which specializations are needed in other translation units, resulting in unresolved external
 symbol / linker errors during linking. Thus, templates must be defined in the header or in the
 same translation unit.
*/
template <typename T>
class DataBuffer {
private:
  T* data;         // heap-allocated circular array
  int capacity;
  int head;        // index of oldest element
  int tail;        // index where next element is written
  int count;       // current number of elements

public:
  DataBuffer(int capacity)
      : capacity(capacity), head(0), tail(0), count(0) {
    if (capacity <= 0) {
      throw invalid_argument("Capacity must be positive");
    }
    data = new T[capacity];
  }

  ~DataBuffer() {
    delete[] data;
  }

  // Add element — overwrites oldest if full (circular buffer behavior)
  void push(const T& value) {
    data[tail] = value;
    tail = (tail + 1) % capacity;
    if (count == capacity) {
      // Overwrote the oldest element at head, so advance head forward
      head = (head + 1) % capacity;
    } else {
      count++;
    }
  }

  // Remove and return oldest element
  T pop() {
    if (isEmpty()) {
      throw underflow_error("Buffer is empty");
    }
    T val = data[head];
    head = (head + 1) % capacity;
    count--;
    return val;
  }

  // View oldest without removing
  T peek() const {
    if (isEmpty()) {
      throw underflow_error("Buffer is empty");
    }
    return data[head];
  }

  bool isEmpty() const {
    return count == 0;
  }

  bool isFull() const {
    return count == capacity;
  }

  int size() const {
    return count;
  }

  // Template friend — print all elements in order
  template <typename U>
  friend ostream& operator<<(ostream& out, const DataBuffer<U>& buf);
};

template <typename U>
ostream& operator<<(ostream& out, const DataBuffer<U>& buf) {
  out << "[";
  for (int i = 0; i < buf.count; i++) {
    int idx = (buf.head + i) % buf.capacity;
    if constexpr (is_same_v<U, string>) {
      out << "\"" << buf.data[idx] << "\"";
    } else {
      out << buf.data[idx];
    }
    if (i < buf.count - 1) {
      out << ", ";
    }
  }
  out << "]";
  return out;
}

int main() {
  // --------------------------------------------------------------------------
  // Part A — Abstract DataProcessor Interface
  // --------------------------------------------------------------------------
  // Verify that attempting to instantiate DataProcessor causes a compile error:
  // DataProcessor dp; // ERROR: cannot declare variable 'dp' to be of abstract type 'DataProcessor'

  cout << "=== Part A: Abstract DataProcessor Interface ===" << endl;
  vector<DataProcessor*> pipeline;
  pipeline.push_back(new CSVProcessor());
  pipeline.push_back(new SensorStreamProcessor());

  for (auto* p : pipeline) {
    p->loadData("source_data");
    p->processData();
    p->printSummary();
    p->exportResult("output_dir");
    cout << "---" << endl;
  }

  // --------------------------------------------------------------------------
  // Bonus — dynamic_cast Safety Check
  // --------------------------------------------------------------------------
  /*
   Why static_cast is unsafe while dynamic_cast is safe:
   static_cast performs downcasting at compile time without any runtime type checks.
   If a base pointer pointing to a CSVProcessor is incorrectly static_cast to a
   SensorStreamProcessor*, the compiler permits it, but calling getMean() invokes undefined
   behavior, reading garbage memory or crashing.
   In contrast, dynamic_cast uses Run-Time Type Information (RTTI). It safely checks the
   actual derived type at runtime and returns nullptr if the cast is invalid, preventing
   invalid memory accesses.
  */
  cout << "=== Bonus: dynamic_cast Safety Check ===" << endl;
  for (auto* p : pipeline) {
    if (auto* csv = dynamic_cast<CSVProcessor*>(p)) {
      cout << "Found CSV Processor with " << csv->recordCount() << " records." << endl;
    } else if (auto* sensor = dynamic_cast<SensorStreamProcessor*>(p)) {
      cout << "Found Sensor Processor — Mean: " << fixed << setprecision(2) << sensor->getMean() << endl;
      cout.unsetf(ios_base::floatfield);
      cout << setprecision(6);
    }
  }
  cout << endl;

  // Cleanup Part A heap resources
  for (auto* p : pipeline) {
    delete p;
  }
  pipeline.clear();

  // --------------------------------------------------------------------------
  // Part B — Class Template DataBuffer<T>
  // --------------------------------------------------------------------------
  cout << "=== Part B: Class Template DataBuffer<T> ===" << endl;

  // Integer buffer — simulate sensor tick IDs
  DataBuffer<int> tickBuffer(5);
  for (int i = 1; i <= 7; i++) {
    tickBuffer.push(i * 10); // Should overwrite oldest (10 and 20 overwritten)
  }
  cout << "Tick Buffer: " << tickBuffer << " (10 and 20 were overwritten)" << endl;

  // Double buffer — simulate temperature readings
  DataBuffer<double> tempBuffer(4);
  tempBuffer.push(36.6);
  tempBuffer.push(37.1);
  tempBuffer.push(38.2);
  tempBuffer.push(36.9);
  cout << "Before pop: " << tempBuffer << endl;
  cout << "Popped: " << tempBuffer.pop() << endl;
  cout << "After pop: " << tempBuffer << endl;

  // String buffer — simulate log message queue
  DataBuffer<string> logBuffer(3);
  logBuffer.push("INFO: Server started");
  logBuffer.push("WARN: High memory usage");
  logBuffer.push("ERROR: DB connection timeout");
  logBuffer.push("INFO: Retry successful"); // Overwrites oldest ("INFO: Server started")
  cout << "Log Buffer: " << logBuffer << endl;

  return 0;
}
