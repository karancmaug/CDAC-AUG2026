#include <iostream>

using namespace std;

int main() {

  // Registers mapping to memory addresses
  int statusReg = 0b10110001;  // Read-only from firmware side
  int controlReg = 0b00000000; // Firmware writes here
  int dataReg = 0b11001010;    // For reassignment demo

  cout << "--- Initial Register Values (Decimal) ---" << endl;
  cout << "statusReg  : " << statusReg << endl;
  cout << "controlReg : " << controlReg << endl;
  cout << "dataReg    : " << dataReg << endl << endl;

  // ==========================================
  // REQUIREMENT 1: Pointer to Constant Data (const int*)
  // ==========================================
  // The data pointed to cannot be modified, but the pointer itself can point to
  // a new address.
  const int *regPtr1 = &statusReg;
  cout << "regPtr1 value (statusReg): " << *regPtr1 << endl;

  // Attempt a write (Uncommenting this will cause a COMPILER ERROR)
  //*regPtr1 = 0b11111111;
  // ERROR EXPLANATION:
  // "assignment of read-only location '* regPtr1'"
  // Since regPtr1 is a pointer to constant int ('const int*'), C++ prevents
  // modifying the value at the address it points to. This enforces read-only
  // access to statusReg.

  // Attempt a repoint (Historically allowed for 'const int*', but commented out
  // as requested) regPtr1 = &controlReg; EXPLANATION: This action is legally
  // ALLOWED by C++ compilers because regPtr1 itself is NOT const (only the data
  // it points to is const). However, it is commented out per requirement
  // instructions.

  // ==========================================
  // REQUIREMENT 2: Constant Pointer (int* const)
  // ==========================================
  // The pointer itself cannot point to a new address (cannot be repointed),
  // but the data at the address it points to can be modified.
  int *const regPtr2 = &controlReg;

  // Write a new value through the pointer (ALLOWED)
  *regPtr2 = 0b11110000; // (240 in decimal)
  cout << "regPtr2 updated controlReg to: " << *regPtr2 << endl;

  // Attempt a repoint (Uncommenting this will cause a COMPILER ERROR)
  // regPtr2 = &statusReg;
  // ERROR EXPLANATION:
  // "assignment of read-only variable 'regPtr2'"
  // Since regPtr2 is a constant pointer ('int* const'), the memory address it
  // holds is locked at initialization. You cannot assign a new address to it
  // (i.e., you cannot "repoint" it).

  // ==========================================
  // REQUIREMENT 3: Constant Pointer to Constant Data (const int* const)
  // ==========================================
  // Neither the pointer address nor the data it points to can be changed.
  const int* const regPtr3 = &dataReg;
  cout << "regPtr3 value (dataReg): " << *regPtr3 << endl;

  // Attempt a write (Uncommenting this will cause a COMPILER ERROR)
  // *regPtr3 = 0b11111111;
  // ERROR EXPLANATION:
  // "assignment of read-only location '*(const int*)regPtr3'"
  // You cannot write through regPtr3 because the data is constant ('const
  // int').

  // Attempt a repoint (Uncommenting this will cause a COMPILER ERROR)
  // regPtr3 = &statusReg;
  // ERROR EXPLANATION:
  // "assignment of read-only variable 'regPtr3'"
  // You cannot repoint regPtr3 because the pointer itself is constant ('*
  // const').

  return 0;
}