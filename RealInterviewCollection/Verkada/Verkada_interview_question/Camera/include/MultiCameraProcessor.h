#ifndef MULTICAMERAPROCESSOR_H
#define MULTICAMERAPROCESSOR_H

#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include "Camera.h"

class MultiCameraProcessor {
public:
    // Constructor to initialize the processor with multiple cameras
    MultiCameraProcessor(const std::vector<Camera>& cameras);

    // Detect periods above a threshold for all cameras using the specified method
    std::vector<std::vector<MotionPeriod >> detectPeriodsForAllCameras(double threshold, int numThreads, const std::string& method);

    // Get the count of cameras that exceeded the threshold
    int getExceedCount() const;

private:
    // Helper functions
    std::vector<std::vector<MotionPeriod >> detectPeriodsWithFutures(double threshold, int numThreads);
    std::vector<std::vector<MotionPeriod >> detectPeriodsWithThreads(double threshold, int numThreads);
    std::vector<MotionPeriod > detectForSingleCameraWithFuture(int cameraIndex, double threshold, int numThreads);
    void detectForSingleCameraWithThread(int cameraIndex, double threshold, int numThreads, std::vector<std::vector<MotionPeriod >>& allResults);

    std::vector<Camera> cameras;         // List of cameras
    std::mutex resultMutex;              // Mutex for protecting shared result access
    std::atomic<int> exceedCount{0};     // Atomic counter for counting cameras exceeding threshold
};

#endif // MULTICAMERAPROCESSOR_H
