#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

// Pure function: only checks values, no I/O
bool checkVitals(float temperature, float pulseRate, float spo2, string& message) {
    if (temperature > 102 || temperature < 95) {
        message = "Temperature is critical!";
        return false;
    }
    if (pulseRate < 60 || pulseRate > 100) {
        message = "Pulse Rate is out of range!";
        return false;
    }
    if (spo2 < 90) {
        message = "Oxygen Saturation out of range!";
        return false;
    }
    return true;
}

// Reusable function: handles blinking alert animation
void showAlert(const string& message, int blinkCount = 6, int delaySeconds = 1) {
    cout << message << "\n";
    for (int i = 0; i < blinkCount; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(delaySeconds));
        cout << "\r *" << flush;
        sleep_for(seconds(delaySeconds));
    }
    cout << "\n";
}

// Wrapper: ties pure check with UI/animation
int vitalsOk(float temperature, float pulseRate, float spo2) {
    string message;
    bool ok = checkVitals(temperature, pulseRate, spo2, message);
    if (!ok) {
        showAlert(message);
        return 0;
    }
    return 1;
}
