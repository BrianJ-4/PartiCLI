#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::cout << "\033[2J\033[H";
        for (int i = 0; i < 500; ++i) {
        // Move cursor to start
        std::string frameBuffer = "\033[H";

        // Construct the frame in RAM
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 60; ++x) {
                // Create a moving pattern based on 'i'
                if ((x + y + i) % 10 == 0) {
                    frameBuffer += "@";
                } else {
                    frameBuffer += ".";
                }
            }
            frameBuffer += "\n";
        }

        // Only one system call to send the entire block of data
        std::cout << frameBuffer << std::flush;

        // Update at 60 fps
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    // Reset terminal settings if any were changed (optional but good practice)
    std::cout << "\033[0m";
    return 0;
}