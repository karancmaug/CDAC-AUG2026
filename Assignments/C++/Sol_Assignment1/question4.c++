#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// CLI version
void runProblem4(int argc, char* argv[]) {
    // If arguments are missing, print usage and exit
    if (argc < 4) {
        cout << "Usage : " << argv[0] << " <warn_threshold> <critical_threshold> <num_readings>\n";
        cout << "Error : Missing arguments.\n";
        exit(1);
    }

    double warn_threshold = stod(argv[1]);
    double critical_threshold = stod(argv[2]);
    int num_readings = stoi(argv[3]);

    // Validate: warn < critical, 1 <= num_readings <= 500
    if (warn_threshold >= critical_threshold) {
        cout << "Error : Warning threshold must be less than critical threshold.\n";
        exit(1);
    }

    if (num_readings < 1 || num_readings > 500) {
        cout << "Error : Number of readings must be between 1 and 500.\n";
        exit(1);
    }

    cout << "Config : Warn=" << fixed << setprecision(0) << warn_threshold 
         << "°C Critical=" << critical_threshold << "°C Readings=" << num_readings << "\n";

    int normal_cnt = 0;
    int warning_cnt = 0;
    int critical_cnt = 0;
    int shutdown_cnt = 0;

    // Simulate num_readings using rand() % 70
    for (int i = 0; i < num_readings; ++i) {
        double val = rand() % 70;
        if (val < warn_threshold) {
            normal_cnt++;
        } else if (val < critical_threshold) {
            warning_cnt++;
        } else if (val < 60.0) {
            critical_cnt++;
        } else {
            shutdown_cnt++;
        }
    }

    cout << "Results : Normal:" << normal_cnt 
         << " Warning:" << warning_cnt 
         << " Critical:" << critical_cnt 
         << " Shutdown:" << shutdown_cnt << "\n";
}

// Interactive Mode version
void runProblem4Interactive() {
    double warn_threshold;
    double critical_threshold;
    int num_readings;

    cout << "Enter warning threshold: ";
    if (!(cin >> warn_threshold)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    cout << "Enter critical threshold: ";
    if (!(cin >> critical_threshold)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    cout << "Enter number of readings (1-500): ";
    if (!(cin >> num_readings)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (warn_threshold >= critical_threshold) {
        cout << "Error : Warning threshold must be less than critical threshold.\n";
        return;
    }

    if (num_readings < 1 || num_readings > 500) {
        cout << "Error : Number of readings must be between 1 and 500.\n";
        return;
    }

    cout << "\nConfig : Warn=" << fixed << setprecision(0) << warn_threshold 
         << "°C Critical=" << critical_threshold << "°C Readings=" << num_readings << "\n";

    int normal_cnt = 0;
    int warning_cnt = 0;
    int critical_cnt = 0;
    int shutdown_cnt = 0;

    for (int i = 0; i < num_readings; ++i) {
        double val = rand() % 70;
        if (val < warn_threshold) {
            normal_cnt++;
        } else if (val < critical_threshold) {
            warning_cnt++;
        } else if (val < 60.0) {
            critical_cnt++;
        } else {
            shutdown_cnt++;
        }
    }

    cout << "Results : Normal:" << normal_cnt 
         << " Warning:" << warning_cnt 
         << " Critical:" << critical_cnt 
         << " Shutdown:" << shutdown_cnt << "\n";
}

int main(int argc, char* argv[]) {
    // Set console output code page to UTF-8 on Windows
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // Seed the random number generator
    srand(time(NULL));

    // Dual Mode: If CLI arguments are provided, run CLI Mode directly
    if (argc > 1) {
        runProblem4(argc, argv);
        return 0;
    }

    // Otherwise run Interactive Mode directly
    runProblem4Interactive();
    return 0;
}
