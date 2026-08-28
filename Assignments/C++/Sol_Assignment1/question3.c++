#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    double grid[3][3];
    cout << "Enter temperature values for 3 floors (3 rooms per floor, total 9 values):\n";
    for (int r = 0; r < 3; ++r) {
        cout << "Floor " << r + 1 << " (Room 1, Room 2, Room 3): ";
        for (int c = 0; c < 3; ++c) {
            if (!(cin >> grid[r][c])) {
                cout << "Invalid input.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                return 1;
            }
        }
    }

    // 2. Display the readings in a formatted table
    cout << "\n";
    cout << "          " << left << setw(8) << "Room1" << setw(8) << "Room2" << "Room3\n";
    for (int r = 0; r < 3; ++r) {
        cout << "Floor " << r + 1 << " : ";
        for (int c = 0; c < 3; ++c) {
            if (c < 2) {
                cout << fixed << setprecision(1) << left << setw(8) << grid[r][c];
            } else {
                cout << fixed << setprecision(1) << grid[r][c];
            }
        }
        cout << "\n";
    }
    cout << "\n";

    // 3. Find and report the hottest room (floor and room number)
    double max_temp = -999.0;
    int max_r = 0, max_c = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (grid[r][c] > max_temp) {
                max_temp = grid[r][c];
                max_r = r;
                max_c = c;
            }
        }
    }
    cout << "Hottest Room  : Floor " << max_r + 1 << ", Room " << max_c + 1 
         << "  →  " << fixed << setprecision(1) << max_temp << "°C\n";

    // 4. Find and report the floor with the highest average temperature
    double floor_avg[3];
    double max_floor_avg = -999.0;
    int max_floor_idx = 0;
    for (int r = 0; r < 3; ++r) {
        double sum_floor = 0;
        for (int c = 0; c < 3; ++c) {
            sum_floor += grid[r][c];
        }
        floor_avg[r] = sum_floor / 3.0;
        if (floor_avg[r] > max_floor_avg) {
            max_floor_avg = floor_avg[r];
            max_floor_idx = r;
        }
    }
    cout << "Hottest Floor : Floor " << max_floor_idx + 1 
         << "  (avg " << fixed << setprecision(2) << max_floor_avg << "°C)\n";

    // 5. Count total rooms at or above the WARNING threshold (30°C)
    int warning_above_cnt = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (grid[r][c] >= 30.0) {
                warning_above_cnt++;
            }
        }
    }
    cout << "Rooms at WARNING or above : " << warning_above_cnt << "\n";

    return 0;
}
