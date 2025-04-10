#include "../include/Camera.h"
#include <algorithm>
#include <stdexcept>
#include <future>
#include <thread>
#include <iostream>

// Constructor to initialize camera data
Camera::Camera(const std::vector<Item>& data) : data(data) {}

Camera::Camera(const Camera& other) : data(other.data) {}

Camera& Camera::operator=(const Camera& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

// Public interface to detect periods based on the chosen method
std::vector<MotionPeriod > Camera::detectPeriodsAboveThreshold(double threshold, int numThreads, const std::string& method) {
    // Reset the count before starting a new detection
    exceedPeriodCount = 0;

    if (method == "future") {
        return detectPeriodsAboveThresholdWithFutures(threshold, numThreads);
    } else if (method == "thread") {
        return detectPeriodsAboveThresholdWithThreads(threshold, numThreads);
    } else {
        throw std::invalid_argument("Invalid method. Please choose 'thread' or 'future'.");
    }
}

// Detect periods using std::future
std::vector<MotionPeriod > Camera::detectPeriodsAboveThresholdWithFutures(double threshold, int numThreads) {
    int dataSize = data.size();
    if (dataSize == 0) {
        throw std::invalid_argument("No data available.");
    }
    if (numThreads <= 0) {
        throw std::invalid_argument("Number of threads must be greater than 0.");
    }
    if (numThreads > dataSize) {
        numThreads = dataSize;
    }
    int chunkSize = dataSize / numThreads;
    std::vector<std::future<std::vector<MotionPeriod >>> futures;
    std::vector<MotionPeriod > result;

    // Launch multiple futures to process different parts of the data
    for (int i = 0; i < numThreads; ++i) {
        int startIdx = i * chunkSize;
        int endIdx = (i == numThreads - 1) ? dataSize - 1 : (startIdx + chunkSize - 1);
        futures.push_back(std::async(std::launch::async, &Camera::detectPeriodsWithFutureTask, this, startIdx, endIdx, threshold));
    }

    // Collect results from futures
    for (auto& future : futures) {
        auto periods = future.get();
        result.insert(result.end(), periods.begin(), periods.end());
    }

    // Sort results by start time
    std::sort(result.begin(), result.end(), [](const MotionPeriod & a, const MotionPeriod & b) {
        return a.start < b.start;
    });

    // Output the total count of periods exceeding the threshold
    std::cout << "Number of periods exceeding the threshold: " << exceedPeriodCount << std::endl;

    return result;
}

// Helper function to perform the task for std::future
std::vector<MotionPeriod > Camera::detectPeriodsWithFutureTask(int startIdx, int endIdx, double threshold) {
    auto periods = detectPeriodsInRange(startIdx, endIdx, threshold);
    // Update the exceed period count if any period is detected
    if (!periods.empty()) {
        ++exceedPeriodCount;
    }
    return periods;
}

// Detect periods using std::thread
std::vector<MotionPeriod > Camera::detectPeriodsAboveThresholdWithThreads(double threshold, int numThreads) {
    int dataSize = data.size();
    if (dataSize == 0) {
        throw std::invalid_argument("No data available.");
    }
    if (numThreads <= 0) {
        throw std::invalid_argument("Number of threads must be greater than 0.");
    }
    if (numThreads > dataSize) {
        numThreads = dataSize;
    }
    int chunkSize = dataSize / numThreads;
    std::vector<std::thread> threads;
    std::vector<MotionPeriod > result;

    // Launch multiple threads to process different parts of the data
    for (int i = 0; i < numThreads; ++i) {
        int startIdx = i * chunkSize;
        int endIdx = (i == numThreads - 1) ? dataSize - 1 : (startIdx + chunkSize - 1);
        threads.emplace_back(&Camera::detectInThread, this, startIdx, endIdx, threshold, std::ref(result));
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    // Sort results by start time
    std::sort(result.begin(), result.end(), [](const MotionPeriod & a, const MotionPeriod & b) {
        return a.start < b.start;
    });

    // Output the total count of periods exceeding the threshold
    std::cout << "Number of periods exceeding the threshold: " << exceedPeriodCount << std::endl;

    return result;
}

// Thread function to detect periods
void Camera::detectInThread(int startIdx, int endIdx, double threshold, std::vector<MotionPeriod >& result) {
    auto localResult = detectPeriodsInRange(startIdx, endIdx, threshold);
    // Lock before modifying shared resource
    {
        std::lock_guard<std::mutex> lock(resultMutex);
        result.insert(result.end(), localResult.begin(), localResult.end());
    }
    // Update the exceed period count
    if (!localResult.empty()) {
        ++exceedPeriodCount;
    }
}

// Helper function to detect periods in a specific range
std::vector<MotionPeriod > Camera::detectPeriodsInRange(int startIdx, int endIdx, double threshold) {
    std::vector<MotionPeriod > periods;
    bool inPeriod = false;
    int start = 0;

    for (int i = startIdx; i <= endIdx; ++i) {
        if (data[i].intensity >= threshold) {
            if (!inPeriod) {
                start = data[i].timestamp;
                inPeriod = true;
            }
        } else {
            if (inPeriod) {
                periods.push_back({start, data[i].timestamp});
                inPeriod = false;
            }
        }
    }

    // Close the last period if still open
    if (inPeriod) {
        periods.push_back({start, data[endIdx].timestamp});
    }

    return periods;
}

// Get the count of periods that exceeded the threshold
int Camera::getExceedPeriodCount() const {
    return exceedPeriodCount;
}
