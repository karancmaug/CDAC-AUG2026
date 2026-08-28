#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Forward declarations of structs for the bonus question
struct Layout1 {
  char c1;
  int i;
  char c2;
};

struct Layout2 {
  int i;
  char c1;
  char c2;
};

class Employee {
private:
  int empId;
  string name;
  string department;
  char grade;
  double basicSalary;
  bool isActive;

  // Static member to keep track of total employees created
  static int employeeCount;

public:
  // Constructor: Auto-assigns ID and sets safe defaults
  Employee() {
    employeeCount++;
    empId = 1000 + employeeCount;
    name = "Unknown";
    department = "HR";     // valid default
    grade = 'D';           // valid default
    basicSalary = 12000.0; // valid default within range
    isActive = true;
  }

  // Setters with validation
  void setName(const string &n) {
    if (n.empty()) {
      cout << "ERROR: Name cannot be empty." << endl;
    } else {
      name = n;
    }
  }

  void setDepartment(const string &dept) {
    if (dept == "Engineering" || dept == "HR" || dept == "Finance" ||
        dept == "Operations") {
      department = dept;
    } else {
      cout << "ERROR: '" << dept << "' is not a registered department." << endl;
    }
  }

  void setGrade(char g) {
    if (g == 'A' || g == 'B' || g == 'C' || g == 'D') {
      grade = g;
    } else {
      cout << "ERROR: Invalid grade '" << g << "'. Accepted values: A, B, C, D."
           << endl;
    }
  }

  void setBasicSalary(double salary) {
    if (salary <= 10000.0 || salary >= 500000.0) {
      cout << "ERROR: Salary must be between Rs.10,000 and Rs.5,00,000. Value "
              "rejected."
           << endl;
    } else {
      basicSalary = salary;
    }
  }

  void deactivate() { isActive = false; }

  // Getters marked const
  int getEmpId() const { return empId; }
  string getName() const { return name; }
  string getDepartment() const { return department; }
  char getGrade() const { return grade; }
  double getBasicSalary() const { return basicSalary; }
  bool getIsActive() const { return isActive; }

  // Business Logic Methods marked const
  double computeAllowances() const {
    double percentage = 0.0;
    switch (grade) {
    case 'A':
      percentage = 0.40;
      break;
    case 'B':
      percentage = 0.30;
      break;
    case 'C':
      percentage = 0.20;
      break;
    case 'D':
      percentage = 0.10;
      break;
    default:
      percentage = 0.00;
      break;
    }
    return basicSalary * percentage;
  }

  double computeGrossSalary() const {
    return basicSalary + computeAllowances();
  }

  double computeTax() const {
    double gross = computeGrossSalary();
    if (gross <= 50000.0) {
      return 0.0;
    } else if (gross <= 100000.0) {
      return (gross - 50000.0) * 0.10;
    } else {
      return 5000.0 + (gross - 100000.0) * 0.20;
    }
  }

  double computeNetSalary() const {
    return computeGrossSalary() - computeTax();
  }

  // Static function to get the count of created employees
  static int getEmployeeCount() { return employeeCount; }

  // Formatter helper for Indian style currency numbering
  string formatCurrency(double val) const {
    long long paise = (long long)(val * 100.0 + 0.5);
    long long rupees = paise / 100;
    int cents = paise % 100;

    string r_str = to_string(rupees);
    string result = "";

    int len = r_str.length();
    if (len <= 3) {
      result = r_str;
    } else {
      result = r_str.substr(len - 3);
      int pos = len - 3;
      while (pos > 0) {
        if (pos >= 2) {
          result = r_str.substr(pos - 2, 2) + "," + result;
          pos -= 2;
        } else {
          result = r_str.substr(0, 1) + "," + result;
          pos -= 1;
        }
      }
    }

    stringstream ss;
    ss << "." << setfill('0') << setw(2) << cents;
    result += ss.str();

    return result;
  }

  void printPayslip() const {
    cout << "================================================" << endl;
    cout << "          EMPLOYEE PAYSLIP - AUG 2026" << endl;
    cout << "================================================" << endl;
    cout << left << setw(16) << "Emp ID" << " : " << empId << endl;
    cout << left << setw(16) << "Name" << " : " << name << endl;
    cout << left << setw(16) << "Department" << " : " << department << endl;
    cout << left << setw(16) << "Grade" << " : " << grade << endl;
    cout << left << setw(16) << "Status" << " : "
         << (isActive ? "Active" : "Inactive") << endl;
    cout << "------------------------------------------------" << endl;

    int allowancePct = 0;
    switch (grade) {
    case 'A':
      allowancePct = 40;
      break;
    case 'B':
      allowancePct = 30;
      break;
    case 'C':
      allowancePct = 20;
      break;
    case 'D':
      allowancePct = 10;
      break;
    default:
      allowancePct = 0;
      break;
    }

    cout << left << setw(16) << "Basic Salary" << " : Rs. " << right << setw(10)
         << formatCurrency(basicSalary) << endl;
    cout << left << setw(16)
         << ("Allowances (" + to_string(allowancePct) + "%)") << " : Rs. "
         << right << setw(10) << formatCurrency(computeAllowances()) << endl;
    cout << left << setw(16) << "Gross Salary" << " : Rs. " << right << setw(10)
         << formatCurrency(computeGrossSalary()) << endl;
    cout << "------------------------------------------------" << endl;
    cout << left << setw(16) << "Tax Deduction" << " : Rs. " << right
         << setw(10) << formatCurrency(computeTax()) << endl;
    cout << left << setw(16) << "Net Salary" << " : Rs. " << right << setw(10)
         << formatCurrency(computeNetSalary()) << endl;
    cout << "================================================" << endl << endl;
  }

  // acceptDetails reads input fields from user, applying setters for validation
  void acceptDetails() {
    string tempName;
    string tempDept;
    char tempGrade;
    double tempSalary;

    cout << "Enter name: ";
    getline(cin >> ws, tempName);
    setName(tempName);

    cout << "Enter department: ";
    cin >> tempDept;
    setDepartment(tempDept);

    cout << "Enter grade: ";
    cin >> tempGrade;
    setGrade(tempGrade);

    cout << "Enter basic salary: ";
    cin >> tempSalary;
    setBasicSalary(tempSalary);
    cout << endl;
  }
};

// Initialize static member variables
int Employee::employeeCount = 0;

int main() {
  // Create objects - one on stack, two on heap
  Employee e1;
  Employee *e2 = new Employee();
  Employee *e3 = new Employee();

  e1.acceptDetails();
  e2->acceptDetails();
  e3->acceptDetails();

  e1.printPayslip();
  e2->printPayslip();
  e3->printPayslip();

  // Simulate a resignation
  e3->deactivate();
  if (!e3->getIsActive()) {
    cout << e3->getName() << " is no longer active. Payroll skipped." << endl;
  }

  cout << "Total Employees : " << Employee::getEmployeeCount() << endl << endl;

  delete e2;
  delete e3;

  // Bonus Question: Print sizes of Layout1 and Layout2
  cout << "=== BONUS: STRUCT PADDING ===" << endl;
  cout << "sizeof(Layout1): " << sizeof(Layout1) << " bytes" << endl;
  cout << "sizeof(Layout2): " << sizeof(Layout2) << " bytes" << endl;

  return 0;
}

/*
 * BONUS - Struct Padding Explanation:
 *
 * 1. Why the sizes differ:
 *    Layout1 and Layout2 contain the exact same member variables (two chars and
 * one int), but they are declared in different orders. The compiler aligns
 * variables to memory boundaries based on their data types.
 *    - In Layout1 (char, int, char):
 *      c1 (1 byte) is aligned to a 1-byte boundary.
 *      i (4 bytes) must be aligned to a 4-byte boundary. Therefore, 3 padding
 * bytes are inserted after c1. c2 (1 byte) is aligned to a 1-byte boundary.
 *      Finally, the structure size must be a multiple of the largest member's
 * alignment (4 bytes for int), so 3 trailing padding bytes are added. Total
 * Size = 1 (c1) + 3 (padding) + 4 (i) + 1 (c2) + 3 (padding) = 12 bytes.
 *    - In Layout2 (int, char, char):
 *      i (4 bytes) is aligned to a 4-byte boundary.
 *      c1 (1 byte) is aligned to a 1-byte boundary.
 *      c2 (1 byte) is aligned to a 1-byte boundary.
 *      The current size is 6 bytes. To round up to a multiple of 4 bytes, 2
 * trailing padding bytes are added. Total Size = 4 (i) + 1 (c1) + 1 (c2) + 2
 * (padding) = 8 bytes.
 *
 * 2. What padding is and why the compiler adds it:
 *    Padding consists of unused bytes inserted by the compiler between
 * structure members or at the end of a structure. Compilers add padding to
 * satisfy hardware alignment requirements. Modern CPUs read memory in word
 * sizes (e.g., 32-bit or 64-bit chunks). Aligning data to matching boundaries
 * allows the CPU to fetch variables in a single memory cycle, significantly
 * improving access speed. Misaligned data can cause performance degradation or
 * hardware faults.
 *
 * 3. Why member order matters when defining network packet headers or hardware
 * register maps: Network protocols and hardware registers have strict,
 * byte-level memory layouts. If a C++ struct is used to directly map to a
 * network packet or hardware registers, compiler-inserted padding will disrupt
 *    the expected offsets, leading to corrupt transmissions or writing to
 * incorrect registers. To prevent this, programmers must arrange members to
 * minimize padding or use compiler directives like '#pragma pack(1)' or
 * '[[no_unique_address]]' / 'alignas' to disable padding and pack the struct
 * tightly.
 */
