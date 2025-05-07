#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <string>
#include <mutex>
#include <atomic>

// Data structure to hold timestamp and intensity
struct Item {
    int timestamp;
    double intensity;
};

// Structure to represent a detected period
struct MotionPeriod  {
    int start;
    int end;
};

class Camera {
public:
    // Constructor
    Camera(const std::vector<Item>& data);
    Camera(const Camera& other);
    Camera& operator=(const Camera& other);

    // Function to detect periods above a threshold using the specified method
    std::vector<MotionPeriod > detectPeriodsAboveThreshold(double threshold, int numThreads, const std::string& method);

    // Get the count of periods that exceeded the threshold
    int getExceedPeriodCount() const;

private:
    // Helper functions
    std::vector<MotionPeriod > detectPeriodsAboveThresholdWithFutures(double threshold, int numThreads);
    std::vector<MotionPeriod > detectPeriodsAboveThresholdWithThreads(double threshold, int numThreads);
    std::vector<MotionPeriod > detectPeriodsInRange(int startIdx, int endIdx, double threshold);
    void detectInThread(int startIdx, int endIdx, double threshold, std::vector<MotionPeriod >& result);
    std::vector<MotionPeriod > detectPeriodsWithFutureTask(int startIdx, int endIdx, double threshold);

    std::vector<Item> data;           // Camera data
    std::mutex resultMutex;           // Mutex for protecting shared result access
    std::atomic<int> exceedPeriodCount{0};  // Atomic counter for counting periods exceeding the threshold
};

#endif // CAMERA_H
