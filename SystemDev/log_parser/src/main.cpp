#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <regex>

// Define a struct to represent each log entry
struct LogEntry {
    std::string key;
    int value;
    int original_position;

    // Default constructor
    LogEntry() : key(""), value(0), original_position(0) {}

    // Custom constructor
    LogEntry(const std::string& k, int v, int pos) : key(k), value(v), original_position(pos) {}

    // Comparison operator for sorting by value, then by original position
    bool operator<(const LogEntry& other) const {
        if (value != other.value) {
            return value < other.value;
        }
        return original_position < other.original_position;
    }
};

// Method 1: Using unordered_map for deduplication and vector + stable_sort for sorting
void method1(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }

    std::unordered_map<std::string, LogEntry> entries_map;
    std::string line;
    std::regex pattern("\"(\\w+)\":\\s*(\\d+)");
    int position = 0;

    while (std::getline(file, line)) {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            std::string key = match[1];
            int value = std::stoi(match[2]);

            entries_map[key] = LogEntry(key, value, position++);
        }
    }
    file.close();

    std::vector<LogEntry> entries;
    for (const auto& pair : entries_map) {
        entries.push_back(pair.second);
    }

    std::stable_sort(entries.begin(), entries.end(), [](const LogEntry& a, const LogEntry& b) {
        return a.value != b.value ? a.value < b.value : a.original_position < b.original_position;
    });

    std::cout << "Method 1 (unordered_map + vector + stable_sort):" << std::endl;
    for (const auto& entry : entries) {
        std::cout << entry.key << " : " << entry.value << std::endl;
    }
    std::cout << std::endl;
}

// Method 2: Using map to automatically sort keys and set for stable sorting by value
void method2(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }

    std::map<std::string, LogEntry> entries_map;
    std::string line;
    std::regex pattern("\"(\\w+)\":\\s*(\\d+)");
    int position = 0;

    while (std::getline(file, line)) {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            std::string key = match[1];
            int value = std::stoi(match[2]);

            entries_map[key] = LogEntry(key, value, position++);
        }
    }
    file.close();

    std::set<LogEntry> sorted_entries;
    for (const auto& pair : entries_map) {
        sorted_entries.insert(pair.second);
    }

    std::cout << "Method 2 (map + set):" << std::endl;
    for (const auto& entry : sorted_entries) {
        std::cout << entry.key << " : " << entry.value << std::endl;
    }
    std::cout << std::endl;
}



int main() {
    std::string file_name = "./src/log.txt";

    // Run each method
    method1(file_name);  // Using unordered_map and stable_sort
    method2(file_name);  // Using map and set

    return 0;
}
