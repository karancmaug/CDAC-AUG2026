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

    int N;
    cout << "Enter number of readings (1 to 100): ";
    if (!(cin >> N) || N < 1 || N > 100) {
        cout << "Invalid number of readings. Must be between 1 and 100.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return 1;
    }

    double readings[100];
    cout << "Enter " << N << " temperature values:\n";
    for (int i = 0; i < N; ++i) {
        if (!(cin >> readings[i])) {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return 1;
        }
    }

    cout << "\n";
    cout << "Readings entered : " << N << "\n";

    // 2. Print all valid readings — skip values below 0 (sensor error) using continue
    cout << "Valid readings   :";
    int skipped = 0;
    for (int i = 0; i < N; ++i) {
        if (readings[i] < 0) {
            skipped++;
            continue;
        }
        cout << " " << fixed << setprecision(1) << readings[i];
    }
    cout << "\n";
    cout << "Skipped (errors) : " << skipped << "\n\n";

    // 3. Scan for the first reading at or above 45°C — print its index and stop scanning using break
    int first_critical_idx = -1;
    double first_critical_val = 0.0;
    for (int i = 0; i < N; ++i) {
        if (readings[i] >= 45.0) {
            first_critical_idx = i;
            first_critical_val = readings[i];
            break;
        }
    }

    if (first_critical_idx != -1) {
        cout << "First CRITICAL   : Index " << first_critical_idx 
             << " → " << fixed << setprecision(1) << first_critical_val << "°C\n\n";
    } else {
        cout << "First CRITICAL   : None\n\n";
    }

    // 4. Compute min, max, and average in one single loop pass
    // 5. Count readings per category: Normal / Warning / Critical / Shutdown
    double min_val = 999999.0;
    double max_val = -999999.0;
    double sum = 0.0;
    int valid_count = 0;

    int normal_cnt = 0;
    int warning_cnt = 0;
    int critical_cnt = 0;
    int shutdown_cnt = 0;

    for (int i = 0; i < N; ++i) {
        if (readings[i] < 0) {
            continue;
        }
        double val = readings[i];
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
        sum += val;
        valid_count++;

        // Categorize based on Problem 1 thresholds
        if (val < 30.0) {
            normal_cnt++;
        } else if (val < 45.0) {
            warning_cnt++;
        } else if (val < 60.0) {
            critical_cnt++;
        } else {
            shutdown_cnt++;
        }
    }

    if (valid_count > 0) {
        double avg_val = sum / valid_count;
        cout << "Min : " << fixed << setprecision(1) << min_val << "°C   "
             << "Max : " << max_val << "°C   "
             << "Avg : " << setprecision(2) << avg_val << "°C\n\n";
    } else {
        cout << "Min : N/A   Max : N/A   Avg : N/A\n\n";
    }

    // Note: The sample counts in the PDF have a minor discrepancy (Normal:2, Warning:3). 
    // This code correctly classifies based on the exact thresholds: Normal (0-29.9) and Warning (30.0-44.9).
    cout << "Normal:" << normal_cnt << "   "
         << "Warning:" << warning_cnt << "   "
         << "Critical:" << critical_cnt << "   "
         << "Shutdown:" << shutdown_cnt << "\n";

    return 0;
}
