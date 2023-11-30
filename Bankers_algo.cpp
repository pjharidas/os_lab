#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_PROCESSES = 5;
const int MAX_RESOURCES = 3;

vector<int> available(MAX_RESOURCES, 0);
vector<vector<int>> maximum(MAX_PROCESSES, vector<int>(MAX_RESOURCES, 0));
vector<vector<int>> allocation(MAX_PROCESSES, vector<int>(MAX_RESOURCES, 0));
vector<vector<int>> need(MAX_PROCESSES, vector<int>(MAX_RESOURCES, 0));
vector<bool> finished(MAX_PROCESSES, false);

bool isSafe(int process, vector<int>& work) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        if (need[process][i] > work[i]) {
            return false;
        }
    }
    return true;
}

void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool requestResources(int process, vector<int>& request) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false;
        }
    }

    for (int i = 0; i < MAX_RESOURCES; ++i) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    return true;
}

void releaseResources(int process, vector<int>& release) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        available[i] += release[i];
        allocation[process][i] -= release[i];
        need[process][i] += release[i];
    }
}

bool bankersAlgorithm() {
    vector<int> work = available;
    vector<int> safeSequence;

    for (int count = 0; count < MAX_PROCESSES; ++count) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (!finished[i] && isSafe(i, work)) {
                for (int j = 0; j < MAX_RESOURCES; ++j) {
                    work[j] += allocation[i][j];
                }
                safeSequence.push_back(i);
                finished[i] = true;
                found = true;
            }
        }

        if (!found) {
            // No safe sequence found
            return false;
        }
    }

    cout << "Safe Sequence: ";
    for (int i = 0; i < safeSequence.size(); ++i) {
        cout << "P" << safeSequence[i];
        if (i < safeSequence.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    return true;
}

int main() {
    // Input maximum resources for each process
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        cout << "Enter maximum resources for Process P" << i << ": ";
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            cin >> maximum[i][j];
        }
    }

    // Input available resources
    cout << "Enter available resources: ";
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        cin >> available[i];
    }

    // Input allocation for each process
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        cout << "Enter allocation for Process P" << i << ": ";
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            cin >> allocation[i][j];
        }
    }

    calculateNeed();

    if (bankersAlgorithm()) {
        cout << "System is in a safe state." << endl;
    } else {
        cout << "System is in an unsafe state." << endl;
    }

    return 0;
}
