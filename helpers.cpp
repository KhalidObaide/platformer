#include <chrono>

int current_epoch() {
    auto now = std::chrono::system_clock::now();
    auto millis = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    int epoch_millis = millis.time_since_epoch().count();
    return epoch_millis;
}

