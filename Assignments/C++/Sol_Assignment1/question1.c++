#include <iomanip>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    double reading;
    cout << "Enter sensor reading (in °C): ";
    if (!(cin >> reading)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return 1;
    }

    // Store reading as double, derive status code as int using if-else
    int status_code = 0;
    string status_label = "";
    if (reading < 0) {
        status_code = -1;
        status_label = "SENSOR_ERROR";
    } else if (reading < 30) {
        status_code = 0;
        status_label = "NORMAL";
    } else if (reading < 45) {
        status_code = 1;
        status_label = "WARNING";
    } else if (reading < 60) {
        status_code = 2;
        status_label = "CRITICAL";
    } else {
        status_code = 3;
        status_label = "SHUTDOWN";
    }

    // Use switch on the status code to print the action
    string action = "";
    switch (status_code) {
        case -1:
            action = "Sensor fault — check wiring";
            break;
        case 0:
            action = "No action required";
            break;
        case 1:
            action = "Alert sent to supervisor";
            break;
        case 2:
            action = "Cooling system triggered";
            break;
        case 3:
            action = "Emergency shutdown initiated";
            break;
    }

    // Temperature in Fahrenheit
    double fahrenheit = (reading * 9.0 / 5.0) + 32.0;

    // Use the ternary operator to print Above Average or Below Average relative to 25°C
    string avg_comparison = (reading >= 25.0) ? "Above Average" : "Below Average";

    // Expected Output Formatting
    cout << "\n";
    cout << "Temperature : " << fixed << setprecision(1) << reading << "°C / "
         << setprecision(2) << fahrenheit << "°F\n";
    cout << "Status      : " << status_label << "\n";
    cout << "Action      : " << action << "\n";
    cout << "Reading     : " << avg_comparison << "\n";

    return 0;
}
