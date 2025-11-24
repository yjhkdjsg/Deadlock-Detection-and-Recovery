// Deadlock Detection and Recovery System
// Implements Banker's Algorithm, Wait-For Graph, and Thread Deadlock Detection

#include <iostream>     // Input/output operations
#include <fstream>      // File operations
#include <vector>       // Dynamic arrays
#include <string>       // String operations
#include <algorithm>    // STL algorithms
#include <iomanip>      // Output formatting
#include <cstdlib>      // Random number generation
#include <ctime>        // Time functions
#include <functional>   // Function objects
#include <climits>      // Integer limits
#include <thread>       // Thread operations
#include <mutex>        // Mutex operations
#include <chrono>       // Time duration

using namespace std;

// Thread deadlock simulation globals
mutex m1, m2;                           // Two mutexes for deadlock simulation
bool threadDeadlockDetected = false;    // Flag to track deadlock detection

// Simulate thread deadlock with two threads and specified delays
void simulateThreadDeadlock(int delayA, int delayB) {
    threadDeadlockDetected = false;  // Reset detection flag
    
    // Thread A: locks m1 first, then tries m2
    auto threadA = [&]() {
        cout << "Thread A locking m1...\n";
        m1.lock();  // Acquire first mutex
        this_thread::sleep_for(chrono::milliseconds(delayA));  // Simulate work

        cout << "Thread A trying to lock m2...\n";
        if (!m2.try_lock()) {  // Non-blocking attempt to avoid indefinite wait
            cout << "Thread A failed to lock m2. Possible deadlock detected.\n";
            threadDeadlockDetected = true;  // Set deadlock flag
        } else {
            cout << "Thread A successfully acquired m2.\n";
            m2.unlock();  // Release second mutex
        }
        m1.unlock();  // Release first mutex
        cout << "Thread A released m1.\n";
    };

    // Thread B: locks m2 first, then tries m1 (opposite order)
    auto threadB = [&]() {
        cout << "Thread B locking m2...\n";
        m2.lock();  // Acquire second mutex first
        this_thread::sleep_for(chrono::milliseconds(delayB));  // Simulate work

        cout << "Thread B trying to lock m1...\n";
        if (!m1.try_lock()) {  // Non-blocking attempt
            cout << "Thread B failed to lock m1. Possible deadlock detected.\n";
            threadDeadlockDetected = true;  // Set deadlock flag
        } else {
            cout << "Thread B successfully acquired m1.\n";
            m1.unlock();  // Release first mutex
        }
        m2.unlock();  // Release second mutex
        cout << "Thread B released m2.\n";
    };

    // Create and start both threads
    thread t1(threadA);
    thread t2(threadB);

    // Wait for both threads to complete
    t1.join();
    t2.join();
}

// Recover from thread deadlock using ordered locking strategy
void recoverThreadDeadlock() {
    if (threadDeadlockDetected) {
        cout << "\nRecovering from thread deadlock using ordered locking...\n";
        
        // Use std::lock to acquire both mutexes atomically in consistent order
        lock(m1, m2);
        cout << "Successfully acquired both locks in ordered manner.\n";
        
        // Release both locks
        m1.unlock();
        m2.unlock();
        cout << "Thread deadlock recovered successfully.\n";
        
        threadDeadlockDetected = false;  // Reset flag
    } else {
        cout << "No thread deadlock detected. Recovery not needed.\n";
    }
}

// Display and handle thread deadlock detection menu
void threadDeadlockMenu() {
    while (true) {  // Menu loop
        cout << "\n========================================================\n";
        cout << "         THREAD DEADLOCK DETECTION & RECOVERY         \n";
        cout << "========================================================\n";
        cout << "  1. Run predefined thread deadlock simulation         \n";
        cout << "  2. Run custom thread deadlock simulation             \n";
        cout << "  3. Demonstrate deadlock prevention (ordered locking) \n";
        cout << "  0. Back to main menu                                 \n";
        cout << "========================================================\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) {  // Exit condition
            cout << "Returning to main menu...\n";
            break;
        }

        switch (choice) {
            case 1: {  // Predefined simulation
                cout << "\nRunning predefined thread deadlock simulation...\n";
                cout << "Using delays: Thread A = 100ms, Thread B = 100ms\n";
                
                threadDeadlockDetected = false;  // Reset flag
                simulateThreadDeadlock(100, 100);  // Run with fixed delays

                cout << "\nChecking for thread deadlock...\n";
                if (threadDeadlockDetected) {
                    cout << "Thread deadlock detected!\n";
                } else {
                    cout << "No thread deadlock detected.\n";
                }

                cout << "\nAttempting recovery...\n";
                recoverThreadDeadlock();
                break;
            }
            
            case 2: {  // Custom simulation
                cout << "\nCustom thread deadlock simulation:\n";
                int delayA, delayB;
                
                // Get user-defined delays
                cout << "Enter delay for Thread A (ms): ";
                cin >> delayA;
                cout << "Enter delay for Thread B (ms): ";
                cin >> delayB;
                
                cout << "\nRunning custom thread deadlock simulation...\n";
                cout << "Using delays: Thread A = " << delayA << "ms, Thread B = " << delayB << "ms\n";
                
                threadDeadlockDetected = false;
                simulateThreadDeadlock(delayA, delayB);

                cout << "\nChecking for thread deadlock...\n";
                if (threadDeadlockDetected) {
                    cout << "Thread deadlock detected!\n";
                } else {
                    cout << "No thread deadlock detected.\n";
                }

                cout << "\nAttempting recovery...\n";
                recoverThreadDeadlock();
                break;
            }
            
            case 3: {  // Deadlock prevention demo
                cout << "\nDemonstrating deadlock prevention using ordered locking...\n";
                
                // Thread A using ordered locking (m1 then m2)
                auto preventiveThreadA = []() {
                    cout << "Preventive Thread A: Acquiring locks in order (m1, then m2)...\n";
                    lock(m1, m2);  // Atomic acquisition in consistent order
                    cout << "Preventive Thread A: Successfully acquired both locks.\n";
                    this_thread::sleep_for(chrono::milliseconds(50));  // Simulate work
                    m2.unlock();  // Release in reverse order
                    m1.unlock();
                    cout << "Preventive Thread A: Released both locks.\n";
                };
                
                // Thread B using same ordered locking (m1 then m2)
                auto preventiveThreadB = []() {
                    cout << "Preventive Thread B: Acquiring locks in order (m1, then m2)...\n";
                    lock(m1, m2);  // Same order as Thread A prevents deadlock
                    cout << "Preventive Thread B: Successfully acquired both locks.\n";
                    this_thread::sleep_for(chrono::milliseconds(50));  // Simulate work
                    m2.unlock();  // Release in reverse order
                    m1.unlock();
                    cout << "Preventive Thread B: Released both locks.\n";
                };
                
                // Create and start prevention threads
                thread pt1(preventiveThreadA);
                thread pt2(preventiveThreadB);
                
                // Wait for completion
                pt1.join();
                pt2.join();
                
                cout << "Deadlock prevention demonstration completed successfully!\n";
                cout << "No deadlock occurred because both threads acquired locks in the same order.\n";
                break;
            }
            
            default:
                cout << "\n[ERROR] Invalid choice! Please try again.\n";
                break;
        }
    }
}

// Main class for Banker's Algorithm and Wait-For Graph deadlock detection
class DeadlockDetector {
private:
    // System parameters
    int numProcesses;                    // Number of processes in system
    int numResources;                    // Number of resource types
    
    // Banker's algorithm matrices
    vector<int> available;               // Available instances of each resource
    vector<vector<int>> maximum;         // Maximum resource needs per process
    vector<vector<int>> allocation;      // Currently allocated resources
    vector<vector<int>> need;            // Remaining resource needs

    // Calculate need matrix: Need = Maximum - Allocation
    void calculateNeed() {
        need.assign(numProcesses, vector<int>(numResources, 0));
        for (int i = 0; i < numProcesses; ++i) {
            for (int j = 0; j < numResources; ++j) {
                need[i][j] = maximum[i][j] - allocation[i][j];
                if (need[i][j] < 0) need[i][j] = 0; // Safety check
            }
        }
    }

public:
    // Constructor: Initialize system parameters and seed random generator
    DeadlockDetector() : numProcesses(0), numResources(0) {
        srand(static_cast<unsigned>(time(nullptr)));  // Seed for random data generation
    }

    // Read system state from input files
    bool readFromFiles() {
        // Open required input files
        ifstream availFile("available.txt");
        ifstream maxFile("maximum.txt");
        ifstream allocFile("allocation.txt");

        // Check if all files opened successfully
        if (!availFile || !maxFile || !allocFile) {
            cout << "Error: Could not open one or more input files!\n";
            cout << "Required files: available.txt, maximum.txt, allocation.txt\n";
            return false;
        }

        // Read available resources from file
        int fileNumResources = 0;
        if (!(availFile >> fileNumResources)) {
            cout << "Error reading available.txt header.\n";
            return false;
        }
        numResources = fileNumResources;
        available.assign(numResources, 0);
        for (int i = 0; i < numResources; ++i) {
            if (!(availFile >> available[i])) {
                cout << "Error: available.txt does not contain enough resource values.\n";
                return false;
            }
        }

        int fileNumProcesses = 0, fileNumResources2 = 0;
        if (!(maxFile >> fileNumProcesses >> fileNumResources2)) {
            cout << "Error reading maximum.txt header. Expect: <numProcesses> <numResources>\n";
            return false;
        }
        if (fileNumResources2 != numResources) {
            cout << "Warning: numResources in maximum.txt (" << fileNumResources2
                 << ") differs from available.txt (" << numResources << "). Using maximum.txt value.\n";
            numResources = fileNumResources2;
        }
        numProcesses = fileNumProcesses;
        maximum.assign(numProcesses, vector<int>(numResources, 0));
        for (int i = 0; i < numProcesses; ++i) {
            for (int j = 0; j < numResources; ++j) {
                if (!(maxFile >> maximum[i][j])) {
                    cout << "Error: maximum.txt does not contain enough matrix values.\n";
                    return false;
                }
            }
        }

        int allocP = 0, allocR = 0;
        if (!(allocFile >> allocP >> allocR)) {
            cout << "Error reading allocation.txt header. Expect: <numProcesses> <numResources>\n";
            return false;
        }
        if (allocP != numProcesses || allocR != numResources) {
            cout << "Warning: allocation.txt dimensions (" << allocP << "x" << allocR
                 << ") differ from maximum.txt (" << numProcesses << "x" << numResources << ").\n";
            if (allocP > 0) numProcesses = allocP;
            if (allocR > 0) numResources = allocR;
            maximum.assign(numProcesses, vector<int>(numResources, 0)); 
            allocFile.clear();
            allocFile.seekg(0);
            if (!(allocFile >> allocP >> allocR)) return false; 
        }

        allocation.assign(numProcesses, vector<int>(numResources, 0));
        for (int i = 0; i < numProcesses; ++i) {
            for (int j = 0; j < numResources; ++j) {
                if (!(allocFile >> allocation[i][j])) {
                    cout << "Error: allocation.txt does not contain enough matrix values.\n";
                    return false;
                }
            }
        }

        if ((int)available.size() != numResources) available.assign(numResources, 0);

        calculateNeed();

        availFile.close();
        maxFile.close();
        allocFile.close();
        return true;
    }

    // Get system state through user input
    bool inputFromUser() {
        cout << "\n========== USER INPUT MODE ==========\n";

        cout << "Enter number of processes: ";
        if (!(cin >> numProcesses)) { cin.clear(); cin.ignore(INT_MAX,'\n'); return false; }

        cout << "Enter number of resources: ";
        if (!(cin >> numResources)) { cin.clear(); cin.ignore(INT_MAX,'\n'); return false; }

        if (numProcesses <= 0 || numResources <= 0) {
            cout << "Invalid input! Values must be positive.\n";
            return false;
        }

        vector<int> totalResources(numResources);
        cout << "\nEnter total instances of each resource:\n";
        for (int i = 0; i < numResources; i++) {
            cout << "Resource R" << i << ": ";
            cin >> totalResources[i];
            if (totalResources[i] < 0) totalResources[i] = 0;
        }

        maximum.assign(numProcesses, vector<int>(numResources, 0));
        cout << "\nEnter Maximum Matrix (max need for each process):\n";
        for (int i = 0; i < numProcesses; i++) {
            cout << "Process P" << i << " (enter " << numResources << " values): ";
            for (int j = 0; j < numResources; j++) {
                cin >> maximum[i][j];
                if (maximum[i][j] < 0) maximum[i][j] = 0;
            }
        }

        allocation.assign(numProcesses, vector<int>(numResources, 0));
        cout << "\nEnter Allocation Matrix (currently allocated resources):\n";
        for (int i = 0; i < numProcesses; i++) {
            cout << "Process P" << i << " (enter " << numResources << " values): ";
            for (int j = 0; j < numResources; j++) {
                cin >> allocation[i][j];
                if (allocation[i][j] < 0) allocation[i][j] = 0;
                if (allocation[i][j] > maximum[i][j]) {
                    cout << "Error: Allocation cannot exceed maximum for P" << i << " R" << j << "!\n";
                    return false;
                }
            }
        }

        available.assign(numResources, 0);
        for (int j = 0; j < numResources; j++) {
            int totalAllocated = 0;
            for (int i = 0; i < numProcesses; i++) totalAllocated += allocation[i][j];
            available[j] = totalResources[j] - totalAllocated;
            if (available[j] < 0) {
                cout << "Error: Allocation exceeds total resources for R" << j << "!\n";
                return false;
            }
        }

        calculateNeed();
        cout << "\n[SUCCESS] Data entered successfully!\n";
        return true;
    }

    // Generate random system state for testing
    bool generateRandomInput() {
        cout << "\n========== RANDOM INPUT GENERATION ==========\n";

        cout << "Enter number of processes (or 0 for random 3-7): ";
        int p; cin >> p;
        if (p == 0) numProcesses = 3 + rand() % 5;
        else numProcesses = p;

        cout << "Enter number of resources (or 0 for random 3-5): ";
        int r; cin >> r;
        if (r == 0) numResources = 3 + rand() % 3;
        else numResources = r;

        if (numProcesses <= 0 || numResources <= 0) {
            cout << "Invalid input!\n";
            return false;
        }

        cout << "\nGenerating random data...\n";
        cout << "Processes: " << numProcesses << "\n";
        cout << "Resources: " << numResources << "\n";

        vector<int> totalResources(numResources);
        for (int j = 0; j < numResources; j++) totalResources[j] = 5 + rand() % 11;

        maximum.assign(numProcesses, vector<int>(numResources, 0));
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                int half = max(1, totalResources[j] / 2);
                maximum[i][j] = 1 + rand() % (half + 1);
            }
        }

        allocation.assign(numProcesses, vector<int>(numResources, 0));
        vector<int> totalAllocated(numResources, 0);
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                int maxAlloc = min(maximum[i][j], totalResources[j] - totalAllocated[j]);
                if (maxAlloc < 0) maxAlloc = 0;
                allocation[i][j] = (maxAlloc == 0) ? 0 : rand() % (maxAlloc + 1);
                totalAllocated[j] += allocation[i][j];
            }
        }

        available.assign(numResources, 0);
        for (int j = 0; j < numResources; j++) available[j] = totalResources[j] - totalAllocated[j];

        calculateNeed();
        cout << "\n[SUCCESS] Random data generated successfully!\n";
        return true;
    }

    // Display current system state (all matrices)
    void displayState() {
        cout << "\n========== CURRENT SYSTEM STATE ==========\n";

        cout << "\nAvailable Resources: ";
        for (int i = 0; i < numResources; i++) {
            cout << "R" << i << ":" << available[i] << " ";
        }
        cout << "\n";

        cout << "\nAllocation Matrix:\n     ";
        for (int j = 0; j < numResources; j++) cout << "R" << j << "  ";
        cout << "\n";
        for (int i = 0; i < numProcesses; i++) {
            cout << "P" << i << ": ";
            for (int j = 0; j < numResources; j++) cout << setw(3) << allocation[i][j] << " ";
            cout << "\n";
        }

        cout << "\nMaximum Matrix:\n     ";
        for (int j = 0; j < numResources; j++) cout << "R" << j << "  ";
        cout << "\n";
        for (int i = 0; i < numProcesses; i++) {
            cout << "P" << i << ": ";
            for (int j = 0; j < numResources; j++) cout << setw(3) << maximum[i][j] << " ";
            cout << "\n";
        }

        cout << "\nNeed Matrix:\n     ";
        for (int j = 0; j < numResources; j++) cout << "R" << j << "  ";
        cout << "\n";
        for (int i = 0; i < numProcesses; i++) {
            cout << "P" << i << ": ";
            for (int j = 0; j < numResources; j++) cout << setw(3) << need[i][j] << " ";
            cout << "\n";
        }
        cout << "==========================================\n";
    }

    // Banker's Algorithm: Check for safe state and find safe sequence
    bool bankersAlgorithmDetection(vector<int>& safeSequence, const vector<bool>* terminatedProcesses = nullptr) {
        vector<int> work = available;           // Work vector (copy of available)
        vector<bool> finish(numProcesses, false);  // Process completion flags
        safeSequence.clear();                   // Clear previous sequence

        if (terminatedProcesses != nullptr) {
            for (int i = 0; i < numProcesses; i++) {
                if ((*terminatedProcesses)[i]) {
                    finish[i] = true;
                }
            }
        }

        int activeProcesses = numProcesses;
        if (terminatedProcesses != nullptr) {
            for (int i = 0; i < numProcesses; i++) {
                if ((*terminatedProcesses)[i]) activeProcesses--;
            }
        }

        int count = 0;
        while (count < activeProcesses) {
            bool found = false;
            for (int i = 0; i < numProcesses; i++) {
                if (!finish[i]) {
                    bool canFinish = true;
                    for (int j = 0; j < numResources; j++) {
                        if (need[i][j] > work[j]) { canFinish = false; break; }
                    }
                    if (canFinish) {
                        for (int j = 0; j < numResources; j++) work[j] += allocation[i][j];
                        safeSequence.push_back(i);
                        finish[i] = true;
                        found = true;
                        count++;
                    }
                }
            }
            if (!found) {
                cout << "\n[DEADLOCK DETECTED] System is in unsafe state!\n";
                cout << "Processes that cannot finish: ";
                for (int i = 0; i < numProcesses; ++i) {
                    if (!finish[i] && (terminatedProcesses == nullptr || !(*terminatedProcesses)[i])) {
                        cout << "P" << i << " ";
                    }
                }
                cout << "\n";
                return false;
            }
        }

        cout << "\n[SAFE STATE] No deadlock detected.";
        if (!safeSequence.empty()) {
            cout << "\nSafe sequence: ";
            for (int i : safeSequence) cout << "P" << i << " ";
        } else {
            cout << "\nAll processes have been terminated.";
        }
        cout << "\n";
        return true;
    }

    bool bankersAlgorithmCompute(vector<int>& safeSequence, const vector<bool>* terminatedProcesses = nullptr) {
        vector<int> work = available;
        vector<bool> finish(numProcesses, false);
        safeSequence.clear();
        if (terminatedProcesses != nullptr) {
            for (int i = 0; i < numProcesses; ++i) if ((*terminatedProcesses)[i]) finish[i] = true;
        }
        int active = numProcesses;
        if (terminatedProcesses != nullptr) for (int i = 0; i < numProcesses; ++i) if ((*terminatedProcesses)[i]) active--;
        int count = 0;
        while (count < active) {
            bool found = false;
            for (int i = 0; i < numProcesses; ++i) if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < numResources; ++j) if (need[i][j] > work[j]) { canFinish = false; break; }
                if (canFinish) {
                    for (int j = 0; j < numResources; ++j) work[j] += allocation[i][j];
                    finish[i] = true; safeSequence.push_back(i); found = true; count++;
                }
            }
            if (!found) return false; // unsafe
        }
        return true;
    }

    // Wait-For Graph: Detect deadlock using graph cycle detection
    bool waitForGraphDetection() {
        cout << "\n========== WAIT-FOR GRAPH DETECTION ==========" << "\n";

        vector<vector<bool>> waitForGraph(numProcesses, vector<bool>(numProcesses, false));
        vector<bool> blocked(numProcesses, false);

        for (int i = 0; i < numProcesses; ++i) {
            bool isBlocked = false;
            for (int j = 0; j < numResources; ++j) {
                if (need[i][j] > available[j]) { isBlocked = true; break; }
            }
            blocked[i] = isBlocked;
            if (!isBlocked) continue;

            for (int j = 0; j < numResources; ++j) {
                if (need[i][j] > available[j]) {
                    for (int k = 0; k < numProcesses; ++k) {
                        if (k != i && allocation[k][j] > 0) {
                            waitForGraph[i][k] = true;
                        }
                    }
                }
            }
        }

        cout << "\nProcesses currently blocked (need > available): ";
        bool anyBlocked = false;
        for (int i = 0; i < numProcesses; ++i) if (blocked[i]) { cout << "P" << i << " "; anyBlocked = true; }
        if (!anyBlocked) cout << "None";
        cout << "\n";

        cout << "\nWait-For Graph (Pi waits for Pj):\n";
        for (int i = 0; i < numProcesses; ++i) {
            cout << "P" << i << " -> ";
            bool anyEdge = false;
            for (int j = 0; j < numProcesses; ++j) {
                if (waitForGraph[i][j]) { cout << "P" << j << " "; anyEdge = true; }
            }
            if (!anyEdge) cout << "None";
            cout << "\n";
        }

        vector<bool> visited(numProcesses, false), recStack(numProcesses, false);
        function<bool(int)> hasCycle = [&](int v) -> bool {
            visited[v] = true;
            recStack[v] = true;
            for (int u = 0; u < numProcesses; ++u) {
                if (waitForGraph[v][u]) {
                    if (!visited[u] && hasCycle(u)) return true;
                    else if (recStack[u]) return true;
                }
            }
            recStack[v] = false;
            return false;
        };

        for (int i = 0; i < numProcesses; ++i) {
            if (!visited[i] && hasCycle(i)) {
                cout << "\nDeadlock exists.\n";
                return false;
            }
        }

        vector<int> safeSeq;
        if (bankersAlgorithmCompute(safeSeq)) {
            cout << "\nSafe sequence: ";
            for (int p : safeSeq) cout << "P" << p << " ";
            cout << "\n";
            return true;
        } else {
            cout << "\nDeadlock exists (unsafe state without WFG cycle).\n";
            return false;
        }
    }

    // Recovery strategy: Terminate processes to break deadlock
    void processTermination(bool deadlockPreviouslyDetected) {
        cout << "\n========== PROCESS TERMINATION RECOVERY ==========" << "\n";
        if (!deadlockPreviouslyDetected) { cout << "No recovery needed (system safe).\n"; return; }
        vector<bool> terminated(numProcesses, false);
        int culprit = -1; int minAlloc = INT_MAX;
        for (int i = 0; i < numProcesses; ++i) {
            int totalAlloc = 0; for (int j = 0; j < numResources; ++j) totalAlloc += allocation[i][j];
            if (totalAlloc < minAlloc && totalAlloc > 0) { minAlloc = totalAlloc; culprit = i; }
        }
        if (culprit == -1) { cout << "No suitable culprit to terminate.\n"; return; }
        cout << "Terminating culprit process P" << culprit << "\n";
        for (int j = 0; j < numResources; ++j) { available[j] += allocation[culprit][j]; allocation[culprit][j] = 0; need[culprit][j] = 0; }
        terminated[culprit] = true;
        vector<int> safeSeq;
        if (bankersAlgorithmCompute(safeSeq, &terminated)) {
            cout << "Recovered. New safe sequence: "; for (int p : safeSeq) cout << "P" << p << " "; cout << "\n";
        } else {
            cout << "Initial termination insufficient; escalating...\n";
            int terminationCount = 1;
            while (true) {
                int minProcess = -1; int minAllocation2 = INT_MAX;
                for (int i = 0; i < numProcesses; ++i) if (!terminated[i]) {
                    int totalAlloc = 0; for (int j = 0; j < numResources; ++j) totalAlloc += allocation[i][j];
                    if (totalAlloc < minAllocation2) { minAllocation2 = totalAlloc; minProcess = i; }
                }
                if (minProcess == -1) break;
                cout << "Terminating additional process P" << minProcess << "\n";
                for (int j = 0; j < numResources; ++j) { available[j] += allocation[minProcess][j]; allocation[minProcess][j] = 0; need[minProcess][j] = 0; }
                terminated[minProcess] = true; terminationCount++;
                if (bankersAlgorithmCompute(safeSeq, &terminated)) {
                    cout << "Recovered after terminating " << terminationCount << " processes. Safe sequence: ";
                    for (int p : safeSeq) cout << "P" << p << " "; cout << "\n"; return;
                }
            }
            cout << "Recovery failed: still unsafe after terminations.\n";
        }
    }

    // Recovery strategy: Preempt resources from victim process
    void resourcePreemption(bool deadlockPreviouslyDetected) {
        cout << "\n========== RESOURCE PREEMPTION RECOVERY ==========" << "\n";
        if (!deadlockPreviouslyDetected) { cout << "No recovery needed (system safe).\n"; return; }
        cout << "Attempting resource preemption...\n";
        int victim = -1; int minAlloc = INT_MAX;
        for (int i = 0; i < numProcesses; ++i) {
            int totalAlloc = 0; for (int j = 0; j < numResources; ++j) totalAlloc += allocation[i][j];
            if (totalAlloc > 0 && totalAlloc < minAlloc) { minAlloc = totalAlloc; victim = i; }
        }
        if (victim == -1) { cout << "No suitable victim found.\n"; return; }
        cout << "Preempting resources from P" << victim << " -> ";
        vector<bool> preempted(numProcesses, false);
        for (int j = 0; j < numResources; ++j) if (allocation[victim][j] > 0) {
            cout << "R" << j << ":" << allocation[victim][j] << " ";
            available[j] += allocation[victim][j]; allocation[victim][j] = 0; need[victim][j] = 0; preempted[victim] = true;
        }
        cout << "\n";
        vector<int> safeSeq;
        if (bankersAlgorithmCompute(safeSeq, &preempted)) {
            cout << "Recovered. Safe sequence: "; for (int p : safeSeq) cout << "P" << p << " "; cout << "\n";
        } else {
            cout << "Still unsafe after preemption. Consider termination strategy.\n";
        }
    }

    bool requestResources(int processId, vector<int>& requestVec) {
        cout << "\n========== BANKER'S ALGORITHM: RESOURCE REQUEST ==========\n";
        if (processId < 0 || processId >= numProcesses) {
            cout << "Invalid process ID!\n"; return false;
        }
        if ((int)requestVec.size() != numResources) {
            cout << "Request vector length mismatch!\n"; return false;
        }

        cout << "Process P" << processId << " requesting: ";
        for (int r : requestVec) cout << r << " ";
        cout << "\n";

        for (int i = 0; i < numResources; ++i) {
            if (requestVec[i] > need[processId][i]) {
                cout << "[REQUEST DENIED] Request exceeds maximum need!\n"; return false;
            }
            if (requestVec[i] > available[i]) {
                cout << "[REQUEST DENIED] Resources not currently available!\n"; return false;
            }
        }

        auto oldAvailable = available;
        auto oldAlloc = allocation[processId];
        auto oldNeed = need[processId];

        for (int i = 0; i < numResources; ++i) {
            available[i] -= requestVec[i];
            allocation[processId][i] += requestVec[i];
            need[processId][i] -= requestVec[i];
        }

        vector<int> safeSeq;
        if (bankersAlgorithmDetection(safeSeq)) {
            cout << "[REQUEST GRANTED] Resources allocated safely.\n";
            return true;
        } else {
            available = oldAvailable;
            allocation[processId] = oldAlloc;
            need[processId] = oldNeed;
            cout << "[REQUEST DENIED] Allocation would lead to unsafe state.\n";
            return false;
        }
    }

    void simulateResourceRequest() {
        cout << "\n========== SIMULATE RESOURCE REQUEST ==========\n";
        int processId;
        cout << "Enter process ID (0-" << max(0, numProcesses - 1) << "): ";
        cin >> processId;
        if (processId < 0 || processId >= numProcesses) { cout << "Invalid process ID!\n"; return; }

        vector<int> requestVec(numResources);
        cout << "Enter request for " << numResources << " resources: ";
        for (int i = 0; i < numResources; ++i) cin >> requestVec[i];

        requestResources(processId, requestVec);
    }

    bool isDataLoaded() const { return numProcesses > 0 && numResources > 0; }
};

// Display main menu options
void displayMainMenu() {
    cout << "\n========================================================\n";
    cout << "      DEADLOCK DETECTION & RECOVERY SYSTEM           \n";
    cout << "========================================================\n";
    cout << "  1. Load predefined data from files                   \n";
    cout << "  2. Enter data manually                               \n";
    cout << "  3. Generate random data                              \n";
    cout << "  4. Thread Deadlock Detection & Recovery              \n";
    cout << "  0. Exit                                              \n";
    cout << "========================================================\n";
    cout << "Enter your choice: ";
}

void displayDetectionMenu1() {
    cout << "\n========================================================\n";
    cout << "            DEADLOCK DETECTION - PHASE 1              \n";
    cout << "========================================================\n";
    cout << "  1. Deadlock Detection - Banker's Algorithm           \n";
    cout << "  2. Deadlock Detection - Wait-For Graph               \n";
    cout << "========================================================\n";
    cout << "Enter your choice: ";
}

void displayRecoveryMenu() {
    cout << "\n========================================================\n";
    cout << "            DEADLOCK RECOVERY - PHASE 2               \n";
    cout << "========================================================\n";
    cout << "  1. Recovery Strategy - Process Termination           \n";
    cout << "  2. Recovery Strategy - Resource Preemption           \n";
    cout << "  0. Back to Data Menu                                 \n";
    cout << "========================================================\n";
    cout << "Enter your choice: ";
}

// Main function: Program entry point and control flow
int main() {
    DeadlockDetector detector;          // Create detector instance
    char choice;                        // User menu choice
    bool deadlockDetected = false;      // Track deadlock status

    while (true) {  // Main program loop
        displayMainMenu();
        cin >> choice;
        cin.ignore();  // Clear input buffer 

        bool dataLoaded = false;
        switch (choice) {
            case '1':
                if (detector.readFromFiles()) {
                    cout << "\n[SUCCESS] Data loaded from files successfully!\n";
                    dataLoaded = true;
                }
                break;
            case '2':
                if (detector.inputFromUser()) {
                    cout << "\n[SUCCESS] User data loaded successfully!\n";
                    dataLoaded = true;
                }
                break;
            case '3':
                if (detector.generateRandomInput()) {
                    cout << "\n[SUCCESS] Random data generated successfully!\n";
                    dataLoaded = true;
                }
                break;
            case '4':
                threadDeadlockMenu();
                continue;
            case '0':
                return 0;
            default:
                cout << "\n[ERROR] Invalid choice! Please try again.\n";
                continue;
        }

        if (!dataLoaded) continue;

        detector.displayState();

        while (true) {
            displayDetectionMenu1();
            cin >> choice;
            cin.ignore(); 

            vector<int> safeSequence;
            switch (choice) {
                case '1':
                    deadlockDetected = !detector.bankersAlgorithmDetection(safeSequence);
                    break;
                case '2':
                    deadlockDetected = !detector.waitForGraphDetection();
                    break;
                default:
                    cout << "\n[ERROR] Invalid choice! Please try again.\n";
                    continue;
            }
            break; 
        }

        while (true) {
            displayRecoveryMenu();
            cin >> choice;
            cin.ignore();
            switch (choice) {
                case '1':
                    detector.processTermination(deadlockDetected);
                    break;
                case '2':
                    detector.resourcePreemption(deadlockDetected);
                    break;
                case '0':
                    cout << "\nReturning to Data Menu...\n";
                    goto main_menu_return;
                default:
                    cout << "\n[ERROR] Invalid choice! Please try again.\n";
                    continue;
            }
            break;
        }

        main_menu_return:
        cout << "\n"; 
    }

    return 0;
}
