#include <iostream>

using namespace std;

bool parsePacket(const int *rawData, int size, int **outMin, int **outMax) {
  if (size <= 0)
    return false;

  *outMin = rawData;
  *outMax = rawData;

  for (int i = 0; i < size; i++) {
    if (**outMin > *(rawData + i)) {
      *outMin = rawData + i;
    }
  }

  for (int i = 0; i < size; i++) {
    if (**outMax < *(rawData + i)) {
      *outMax = rawData + i;
    }
  }
  return true;
}
// If size <= 0 : return false, leave output pointers unchanged
// Otherwise   : set *outMin to point at the minimum element in rawData
//               set *outMax to point at the maximum element in rawData
//               return true

int main() {

  int packet[] = {45, 12, 67, 8, 55, 31};
  int *minPtr = nullptr;
  int *maxPtr = nullptr;
  if (parsePacket(packet, 6, &minPtr, &maxPtr)) {
    cout << "Calibration Min : " << *minPtr << endl;
    cout << "Calibration Max : " << *maxPtr << endl;
  }
}