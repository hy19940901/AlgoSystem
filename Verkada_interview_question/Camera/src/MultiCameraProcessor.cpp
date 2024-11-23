#include "../include/MultiCameraProcessor.h"
#include "../include/Camera.h"
#include <future>
#include <thread>
#include <stdexcept>

// Constructor to initialize the processor with multiple cameras
MultiCameraProcessor::MultiCameraProcessor(const std::vector<Camera>& cameras) : cameras(cameras) {
    if (cameras.empty()) {
        throw std::invalid_argument("The list of cameras cannot be empty.");
    }
}

// Detect periods above a threshold for all cameras using the specified method
std::vector<std::vector<MotionPeriod>> MultiCameraProcessor::detectPeriodsForAllCameras(double threshold, int numThreads, const std::string& method) {
    // Reset the count before starting a new detection
    exceedCount = 0;

    if (method == "future") {
        return detectPeriodsWithFutures(threshold, numThreads);
    } else if (method == "thread") {
        return detectPeriodsWithThreads(threshold, numThreads);
    } else {
        throw std::invalid_argument("Invalid method. Please choose 'thread' or 'future'.");
    }
}

// Helper function to detect periods using std::future
std::vector<std::vector<MotionPeriod>> MultiCameraProcessor::detectPeriodsWithFutures(double threshold, int numThreads) {
    std::vector<std::future<std::vector<MotionPeriod>>> futures;
    std::vector<std::vector<MotionPeriod>> allResults(cameras.size());

    // Launch async tasks for each camera
    for (size_t i = 0; i < cameras.size(); ++i) {
        futures.push_back(std::async(std::launch::async, &MultiCameraProcessor::detectForSingleCameraWithFuture, this, i, threshold, numThreads));
    }

    // Collect results from futures
    for (size_t i = 0; i < futures.size(); ++i) {
        allResults[i] = futures[i].get(); // Wait for each task to complete and get the result
    }

    return allResults;
}

// Helper function to detect periods using std::thread
std::vector<std::vector<MotionPeriod>> MultiCameraProcessor::detectPeriodsWithThreads(double threshold, int numThreads) {
    std::vector<std::vector<MotionPeriod>> allResults(cameras.size());
    std::vector<std::thread> threads;

    // Launch threads for each camera
    for (size_t i = 0; i < cameras.size(); ++i) {
        threads.emplace_back(&MultiCameraProcessor::detectForSingleCameraWithThread, this, i, threshold, numThreads, std::ref(allResults));
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    return allResults;
}

// Helper function for std::future to detect periods for a single camera
std::vector<MotionPeriod> MultiCameraProcessor::detectForSingleCameraWithFuture(int cameraIndex, double threshold, int numThreads) {
    auto periods = cameras[cameraIndex].detectPeriodsAboveThreshold(threshold, numThreads, "future");
    
    // Update the exceed count if any period is detected
    if (!periods.empty()) {
        ++exceedCount;
    }

    return periods;
}

// Helper function for std::thread to detect periods for a single camera
void MultiCameraProcessor::detectForSingleCameraWithThread(int cameraIndex, double threshold, int numThreads, std::vector<std::vector<MotionPeriod>>& allResults) {
    auto periods = cameras[cameraIndex].detectPeriodsAboveThreshold(threshold, numThreads, "thread");

    // Lock before modifying shared resource
    {
        std::lock_guard<std::mutex> lock(resultMutex);
        allResults[cameraIndex] = std::move(periods);
    }

    // Update the exceed count if any period is detected
    if (!allResults[cameraIndex].empty()) {
        ++exceedCount;
    }
}

// Get the count of cameras that exceeded the threshold
int MultiCameraProcessor::getExceedCount() const {
    return exceedCount;
}
