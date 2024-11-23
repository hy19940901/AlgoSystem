#include <iostream>
#include "../include/Camera.h"
#include "../include/MultiCameraProcessor.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>

// Function to input camera data
std::vector<Item> inputCameraData(int n) {
    std::vector<Item> cameraData;

    if (n <= 5) {
        // Manually input data
        for (int i = 0; i < n; ++i) {
            int timestamp;
            double intensity;
            std::cout << "Enter timestamp and intensity for data point " << i + 1 << ": ";
            std::cin >> timestamp >> intensity;
            cameraData.push_back({timestamp, intensity});
        }
    } else {
        // Automatically generate data
        std::srand(std::time(0));
        for (int i = 0; i < n; ++i) {
            int timestamp = i + 1;
            double intensity = (static_cast<double>(std::rand()) / RAND_MAX) * 100;
            cameraData.push_back({timestamp, intensity});
        }
        std::cout << n << " data points have been automatically generated.\n";
    }

    return cameraData;
}

// Function to test single camera processing
void testSingleCamera() {
    int n, threshold, numThreads;
    std::string method;

    // Get the number of data points from the user
    std::cout << "Enter the number of data points: ";
    std::cin >> n;

    // Input camera data
    std::vector<Item> cameraData = inputCameraData(n);

    // Input the threshold value
    std::cout << "Enter the intensity threshold: ";
    std::cin >> threshold;

    numThreads = std::thread::hardware_concurrency();

    std::cout << "Enter the number of threads to use: ";

    // Input the method to use ("thread" or "future")
    std::cout << "Enter the method to use (thread/future): ";
    std::cin >> method;

    // Create a Camera object
    Camera camera(cameraData);

    try {
        // Detect periods where intensity is above the threshold
        std::vector<MotionPeriod > periods = camera.detectPeriodsAboveThreshold(threshold, numThreads, method);

        // Output the detected periods
        std::cout << "Detected periods above threshold:\n";
        for (const auto& period : periods) {
            std::cout << "Start: " << period.start << ", End: " << period.end << "\n";
            std::cout << "Intensity values during this period:\n";
            for (int i = period.start - 1; i <= period.end - 1; ++i) {
                if (cameraData[i].intensity >= threshold) {
                    std::cout << "Timestamp: " << cameraData[i].timestamp
                              << ", Intensity: " << cameraData[i].intensity << "\n";
                }
            }
            std::cout << "---------------------\n";
        }

        // Output the number of detected periods that exceeded the threshold
        std::cout << "Number of periods exceeding the threshold: " << camera.getExceedPeriodCount() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to test multiple cameras processing
void testMultipleCameras() {
    int numCameras, n, threshold, numThreads;
    std::string method;
    std::vector<Camera> cameras;

    // Get the number of cameras from the user
    std::cout << "Enter the number of cameras: ";
    std::cin >> numCameras;

    // For each camera, generate data
    for (int camIndex = 0; camIndex < numCameras; ++camIndex) {
        std::cout << "\nCamera " << camIndex + 1 << ":\n";
        std::cout << "Enter the number of data points: ";
        std::cin >> n;

        // Input camera data
        std::vector<Item> cameraData = inputCameraData(n);

        // Create a Camera object and add it to the list
        cameras.emplace_back(cameraData);
    }

    // Input the threshold value
    std::cout << "Enter the intensity threshold: ";
    std::cin >> threshold;

    numThreads = std::thread::hardware_concurrency();
    std::cout << "Enter the number of threads to use: ";

    // Input the method to use ("thread" or "future")
    std::cout << "Enter the method to use (thread/future): ";
    std::cin >> method;

    // Create a MultiCameraProcessor to handle multiple cameras
    MultiCameraProcessor processor(cameras);

    try {
        // Detect periods where intensity is above the threshold for all cameras
        std::vector<std::vector<MotionPeriod >> allResults = processor.detectPeriodsForAllCameras(threshold, numThreads, method);

        // Output the detected periods for each camera
        for (size_t camIndex = 0; camIndex < allResults.size(); ++camIndex) {
            std::cout << "\nCamera " << camIndex + 1 << " results:\n";
            const auto& periods = allResults[camIndex];
            for (const auto& period : periods) {
                std::cout << "Start: " << period.start << ", End: " << period.end << "\n";
            }
            std::cout << "---------------------\n";
        }

        // Output the count of cameras exceeding the threshold
        std::cout << "Number of cameras exceeding the threshold: " << processor.getExceedCount() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Main function to choose between single and multiple camera tests
int main() {
    int choice;
    std::cout << "Choose the test type:\n";
    std::cout << "1. Single Camera Test\n";
    std::cout << "2. Multiple Cameras Test\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        testSingleCamera();
    } else if (choice == 2) {
        testMultipleCameras();
    } else {
        std::cerr << "Invalid choice. Please choose 1 or 2.\n";
    }

    return 0;
}
