#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

class LedgerEntry {
  string description;
  double *amounts;         // Dynamic array
  int days;                // size of the array

public:
  static int totalEntries; // count of live LedgerEntry

  // Constructor
  LedgerEntry(const string &description, int days)
      : description(description), days(days) {
    amounts = new double[days]();
    totalEntries++;
    cout << "[LedgerEntry Created] " << description << " (" << days << " days)" << endl;
  }

  // Copy Constructor — deep copy
  LedgerEntry(const LedgerEntry &other)
      : description(other.description), days(other.days) {
    amounts = new double[days];
    for (int i = 0; i < days; i++) {
      amounts[i] = other.amounts[i];
    }
    totalEntries++;
  }

  // Move Constructor — transfer ownership, leave source in valid empty state
  LedgerEntry(LedgerEntry &&other) noexcept
      : description(std::move(other.description)), amounts(other.amounts),
        days(other.days) {
    // Reset source object to empty/null state
    other.amounts = nullptr;
    other.days = 0;

    totalEntries++;
    cout << "[Move Constructor] Ownership transferred from: " << description
         << endl;
  }

  // Copy Assignment Operator — deep copy with self-assignment guard
  LedgerEntry &operator=(const LedgerEntry &other) {
    if (this != &other) {
      delete[] amounts;

      description = other.description;
      days = other.days;
      amounts = new double[days];

      for (int i = 0; i < days; i++) {
        amounts[i] = other.amounts[i];
      }
    }
    return *this;
  }

  // Move Assignment Operator — transfer ownership with self-assignment guard
  LedgerEntry &operator=(LedgerEntry &&other) noexcept {
    if (this != &other) {
      delete[] amounts; // Clean up current resources

      description = std::move(other.description);
      amounts = other.amounts;
      days = other.days;

      other.amounts = nullptr;
      other.days = 0;

      cout << "[Move Assignment] Ownership transferred from: " << description
           << endl;
    }
    return *this;
  }

  // Destructor
  ~LedgerEntry() {
    delete[] amounts;
    totalEntries--;
    if (!description.empty()) {
      cout << "[Destructor] " << description << " destroyed" << endl;
    }
  }

  // Helper to check if internal buffer is null (used after move)
  bool isAmountsNull() const {
    return amounts == nullptr;
  }

  // Add corresponding daily amounts — return a new LedgerEntry
  LedgerEntry operator+(const LedgerEntry& other) const {
    LedgerEntry result("Combined", days);
    for (int i = 0; i < days; i++) {
      double val1 = (amounts != nullptr && i < days) ? amounts[i] : 0.0;
      double val2 = (other.amounts != nullptr && i < other.days) ? other.amounts[i] : 0.0;
      result.amounts[i] = val1 + val2;
    }
    return result;
  }
  
  // Compare total sum of amounts
  bool operator==(const LedgerEntry& other) const {
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < days; i++) {
      sum1 += (amounts ? amounts[i] : 0.0);
    }
    for (int i = 0; i < other.days; i++) {
      sum2 += (other.amounts ? other.amounts[i] : 0.0);
    }
    return sum1 == sum2;
  }

  bool operator>(const LedgerEntry& other) const {
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < days; i++) {
      sum1 += (amounts ? amounts[i] : 0.0);
    }
    for (int i = 0; i < other.days; i++) {
      sum2 += (other.amounts ? other.amounts[i] : 0.0);
    }
    return sum1 > sum2;
  }
  
  // Subscript operator — access/modify individual day's amount
  double& operator[](int index) {
    if (index < 0 || index >= days) {
      throw out_of_range("Index out of bounds");
    }
    return amounts[index];
  }

  const double& operator[](int index) const {
    if (index < 0 || index >= days) {
      throw out_of_range("Index out of bounds");
    }
    return amounts[index];
  }
  
  // Stream operators — declared as friend functions
  friend ostream& operator<<(ostream& out, const LedgerEntry& entry);
  friend istream& operator>>(istream& in, LedgerEntry& entry);
};

// Initialize static member variable
int LedgerEntry::totalEntries = 0;

// Stream insertion operator definition
ostream& operator<<(ostream& out, const LedgerEntry& entry) {
  out << entry.description << " : [";
  double total = 0;
  for (int i = 0; i < entry.days; i++) {
    out << fixed << setprecision(2) << entry.amounts[i];
    total += entry.amounts[i];
    if (i < entry.days - 1) {
      out << ", ";
    }
  }
  out << "] Total: " << fixed << setprecision(2) << total;
  return out;
}

// Stream extraction operator definition
istream& operator>>(istream& in, LedgerEntry& entry) {
  for (int i = 0; i < entry.days; i++) {
    in >> entry.amounts[i];
  }
  return in;
}

int main() {
    // Objective 1 — Constructor & deep copy    
    LedgerEntry jan("January Sales", 5);
    jan[0] = 1200.50;  jan[1] = 3400.00;  jan[2] = 800.75;
    jan[3] = 2100.00;  jan[4] = 650.25;
    
    LedgerEntry feb("February Sales", 5);
    feb[0] = 900.00;   feb[1] = 2200.50;  feb[2] = 1750.00;
    feb[3] = 3000.00;  feb[4] = 475.50;
    
    cout << jan << endl;
    cout << feb << endl;
    
    
    // Objective 2 — Operator + (sum two ledgers into combined)    
    LedgerEntry combined = jan + feb;
    cout << "Combined : " << combined << endl;
    
    
    // Objective 3 — Relational operators    
    cout << "Jan == Feb : " << (jan == feb ? "Yes" : "No") << endl;
    cout << "Jan  > Feb : " << (jan  > feb ? "Yes" : "No") << endl;
    
    
    // Objective 4 — Move constructor (should NOT deep copy)    
    LedgerEntry moved = move(jan);
    cout << "After move, jan.amounts is null: "         << (jan.isAmountsNull() ? "YES" : "NO") << endl;
    cout << "Moved entry : " << moved << endl;

    // Objective 5 — Move assignment    
    LedgerEntry q1("Q1 Total", 5);
    q1 = move(feb);   // feb's resources transferred to q1    
    cout << "Q1 (moved from feb) : " << q1 << endl;
    
    // Objective 6 — Static member    
    cout << "Live LedgerEntry objects: " << LedgerEntry::totalEntries << endl;
    return 0;
}