#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Function to detect cycles using DFS
bool hasCycle(const string &course, unordered_map<string, vector<string>> &catalog, unordered_set<string> &visited, unordered_set<string> &recStack) {
    if (recStack.count(course)) return true;  // Cycle detected
    if (visited.count(course)) return false;  // Already processed

    visited.insert(course);
    recStack.insert(course);

    for (const string &dependency : catalog[course]) {
        if (hasCycle(dependency, catalog, visited, recStack))
            return true;
    }

    recStack.erase(course);
    return false;
}

// Function to validate the catalog
bool isValidCatalog(unordered_map<string, vector<string>> &catalog) {
    // Step 1: Check if all dependencies exist as keys in the catalog
    for (const auto &[course, dependencies] : catalog) {
        for (const string &dependency : dependencies) {
            if (catalog.find(dependency) == catalog.end()) {
                cout << "Invalid catalog: '" << dependency << "' is not a valid category." << endl;
                return false;
            }
        }
    }

    // Step 2: Check for cyclic dependencies using DFS
    unordered_set<string> visited, recStack;
    for (const auto &[course, _] : catalog) {
        if (!visited.count(course)) {
            if (hasCycle(course, catalog, visited, recStack)) {
                cout << "Invalid catalog: Cycle detected!" << endl;
                return false;
            }
        }
    }

    return true;
}

int main() {
    unordered_map<string, vector<string>> catalog = {
        {"Databases", {"Security", "Logging"}},
        {"Security", {"Logging"}},
        {"Logging", {}} // No dependencies
    };

    if (isValidCatalog(catalog)) {
        cout << "Valid catalog." << endl;
    } else {
        cout << "Invalid catalog." << endl;
    }

    return 0;
}
