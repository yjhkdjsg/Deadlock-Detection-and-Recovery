# Deadlock Detection and Recovery Tool

A comprehensive C++ implementation of deadlock detection and recovery mechanisms using Banker's Algorithm, Wait-For Graph, and thread synchronization techniques.

## Introduction

### The Deadlock Problem

Deadlock is a critical issue in operating systems and concurrent programming where two or more processes are unable to proceed because each is waiting for resources held by others, creating a circular dependency. This creates a state where no process can continue execution, leading to system inefficiency and potential system crashes.

#### Real-World Impact of Deadlocks:

- **Database Systems**: Multiple transactions waiting for locks on different database records
- **Banking Systems**: Account transfers where processes lock accounts in different orders
- **Web Servers**: Thread pools competing for limited database connections and file handles
- **Manufacturing**: Robotic assembly lines where robots wait for shared conveyor belt access
- **Traffic Systems**: Intersection gridlock where vehicles block each other's paths
- **Cloud Computing**: Resource allocation conflicts in distributed systems

Deadlocks can cause:
- System freezes and application hangs
- Performance degradation
- Data corruption risks
- Economic losses in production systems
- Poor user experience

## Our Solution

Our deadlock detection and recovery system provides a multi-faceted approach:
- **Banker's Algorithm Implementation**: Ensures system safety by checking resource allocation requests against future needs
- **Wait-For Graph Detection**: Creates directed graphs to identify circular dependencies between processes
- **Thread Deadlock Simulation**: Demonstrates mutex-based deadlocks with real threading scenarios
- **Process Termination Recovery**: Selects victim processes strategically to break deadlock cycles
- **Resource Preemption Recovery**: Temporarily removes resources from processes to restore system safety
- **Interactive Testing Environment**: Supports file input, manual entry, and random data generation
- **Real-time Monitoring**: Provides detailed system state visualization and safe sequence computation
- **Prevention Mechanisms**: Demonstrates ordered locking to avoid deadlock formation

## Data Structures and Algorithms

### Core Data Structures

#### Resource Allocation Matrices
```cpp
vector<int> available;               // Available instances of each resource
vector<vector<int>> maximum;         // Maximum resource needs per process  
vector<vector<int>> allocation;      // Currently allocated resources
vector<vector<int>> need;            // Remaining resource needs (Max - Allocation)
```

#### Wait-For Graph Representation
```cpp
vector<vector<bool>> waitForGraph;   // Adjacency matrix for process dependencies
vector<bool> blocked;                // Tracks which processes are blocked
```

#### Thread Synchronization
```cpp
mutex m1, m2;                        // Two mutexes for deadlock simulation
bool threadDeadlockDetected;         // Global deadlock detection flag
```

### Key Algorithms

#### 1. Banker's Algorithm for Safety Check

**Time Complexity**: O(n²m) where n = processes, m = resources

```cpp
bool bankersAlgorithmDetection(vector<int>& safeSequence) {
    vector<int> work = available;           // Copy available resources
    vector<bool> finish(numProcesses, false);  
    
    while (count < numProcesses) {
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                // Check if process can complete with current resources
                bool canFinish = true;
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) { 
                        canFinish = false; 
                        break; 
                    }
                }
                if (canFinish) {
                    // Add allocated resources back to work
                    for (int j = 0; j < numResources; j++) 
                        work[j] += allocation[i][j];
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) return false; // Deadlock detected
    }
    return true; // Safe state
}
```

#### 2. Wait-For Graph Cycle Detection

**Time Complexity**: O(n²) using DFS traversal

```cpp
bool waitForGraphDetection() {
    // Build wait-for graph
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            if (need[i][j] > available[j]) {
                for (int k = 0; k < numProcesses; ++k) {
                    if (k != i && allocation[k][j] > 0) {
                        waitForGraph[i][k] = true; // Pi waits for Pk
                    }
                }
            }
        }
    }
    
    // DFS cycle detection
    function<bool(int)> hasCycle = [&](int v) -> bool {
        visited[v] = true;
        recStack[v] = true;
        for (int u = 0; u < numProcesses; ++u) {
            if (waitForGraph[v][u]) {
                if (!visited[u] && hasCycle(u)) return true;
                else if (recStack[u]) return true; // Back edge = cycle
            }
        }
        recStack[v] = false;
        return false;
    };
}
```

#### 3. Thread Deadlock Simulation

```cpp
void simulateThreadDeadlock(int delayA, int delayB) {
    auto threadA = [&]() {
        m1.lock();  // Thread A locks m1 first
        this_thread::sleep_for(chrono::milliseconds(delayA));
        if (!m2.try_lock()) {  // Non-blocking attempt on m2
            threadDeadlockDetected = true;
        } else {
            m2.unlock();
        }
        m1.unlock();
    };
    
    auto threadB = [&]() {
        m2.lock();  // Thread B locks m2 first (opposite order)
        this_thread::sleep_for(chrono::milliseconds(delayB));
        if (!m1.try_lock()) {  // Non-blocking attempt on m1
            threadDeadlockDetected = true;
        } else {
            m1.unlock();
        }
        m2.unlock();
    };
}
```

## Test Cases

### Command Line Execution
```bash
g++ -std=c++11 -pthread deadlock_detection_and_recovery.cpp -o deadlock_system
./deadlock_system
```

### Case 1 - Thread Deadlock Detection & Recovery
```
========================================================
      DEADLOCK DETECTION & RECOVERY SYSTEM
========================================================
  1. Load predefined data from files
  2. Enter data manually
  3. Generate random data
  4. Thread Deadlock Detection & Recovery
  0. Exit
========================================================
Enter your choice: 4

========================================================
         THREAD DEADLOCK DETECTION & RECOVERY
========================================================
  1. Run predefined thread deadlock simulation
  2. Run custom thread deadlock simulation
  3. Demonstrate deadlock prevention (ordered locking)
  0. Back to main menu
========================================================
Enter your choice: 1

Running predefined thread deadlock simulation...
Using delays: Thread A = 100ms, Thread B = 100ms
Thread A locking m1...
Thread B locking m2...
Thread A trying to lock m2...
Thread A failed to lock m2. Possible deadlock detected.
Thread A released m1.
Thread B trying to lock m1...
Thread B successfully acquired m1.
Thread B released m2.

Checking for thread deadlock...
Thread deadlock detected!

Attempting recovery...

Recovering from thread deadlock using ordered locking...
Successfully acquired both locks in ordered manner.
Thread deadlock recovered successfully.
```

### Case 2 - Deadlock Detection and Recovery of Predefined Data From Files
```
========================================================
      DEADLOCK DETECTION & RECOVERY SYSTEM
========================================================
  1. Load predefined data from files
  2. Enter data manually
  3. Generate random data
  4. Thread Deadlock Detection & Recovery
  0. Exit
========================================================
Enter your choice: 1

[SUCCESS] Data loaded from files successfully!

========== CURRENT SYSTEM STATE ==========

Available Resources: R0:3 R1:3 R2:2

Allocation Matrix:
     R0  R1  R2
P0:   0   1   0
P1:   2   0   0
P2:   3   0   2
P3:   2   1   1
P4:   0   0   2

Maximum Matrix:
     R0  R1  R2
P0:   7   5   3
P1:   3   2   2
P2:   9   0   2
P3:   2   2   2
P4:   4   3   3

Need Matrix:
     R0  R1  R2
P0:   7   4   3
P1:   1   2   2
P2:   6   0   0
P3:   0   1   1
P4:   4   3   1
==========================================

========================================================
            DEADLOCK DETECTION - PHASE 1
========================================================
  1. Deadlock Detection - Banker's Algorithm
  2. Deadlock Detection - Wait-For Graph
========================================================
Enter your choice: 1

[SAFE STATE] No deadlock detected.
Safe sequence: P1 P3 P4 P0 P2

========================================================
            DEADLOCK RECOVERY - PHASE 2
========================================================
  1. Recovery Strategy - Process Termination
  2. Recovery Strategy - Resource Preemption
  0. Back to Data Menu
========================================================
Enter your choice: 1

========== PROCESS TERMINATION RECOVERY ==========
No recovery needed (system safe).
```

### Case 3 - Deadlock Detection and Recovery of Manually Entered Data
```
========================================================
      DEADLOCK DETECTION & RECOVERY SYSTEM
========================================================
  1. Load predefined data from files
  2. Enter data manually
  3. Generate random data
  4. Thread Deadlock Detection & Recovery
  0. Exit
========================================================
Enter your choice: 2

========== USER INPUT MODE ==========
Enter number of processes: 2
Enter number of resources: 2

Enter total instances of each resource:
Resource R0: 2
Resource R1: 2

Enter Maximum Matrix (max need for each process):
Process P0 (enter 2 values): 2
2
Process P1 (enter 2 values): 2
2

Enter Allocation Matrix (currently allocated resources):
Process P0 (enter 2 values): 0
2
Process P1 (enter 2 values): 2
0

[SUCCESS] Data entered successfully!

[SUCCESS] User data loaded successfully!

========== CURRENT SYSTEM STATE ==========

Available Resources: R0:0 R1:0

Allocation Matrix:
     R0  R1
P0:   0   2
P1:   2   0

Maximum Matrix:
     R0  R1
P0:   2   2
P1:   2   2

Need Matrix:
     R0  R1
P0:   2   0
P1:   0   2
==========================================

========================================================
            DEADLOCK DETECTION - PHASE 1
========================================================
  1. Deadlock Detection - Banker's Algorithm
  2. Deadlock Detection - Wait-For Graph
========================================================
Enter your choice: 2

========== WAIT-FOR GRAPH DETECTION ==========

Processes currently blocked (need > available): P0 P1

Wait-For Graph (Pi waits for Pj):
P0 -> P1
P1 -> P0

Deadlock exists.

========================================================
            DEADLOCK RECOVERY - PHASE 2
========================================================
  1. Recovery Strategy - Process Termination
  2. Recovery Strategy - Resource Preemption
  0. Back to Data Menu
========================================================
Enter your choice: 2

========== RESOURCE PREEMPTION RECOVERY ==========
Attempting resource preemption...
Preempting resources from P0 -> R1:2
Recovered. Safe sequence: P1
```

## Performance Analysis

### Algorithm Complexity Analysis

| Algorithm | Time Complexity | Space Complexity | Best Case | Worst Case |
|-----------|----------------|------------------|-----------|------------|
| Banker's Algorithm | O(n²m) | O(nm) | O(nm) | O(n²m) |
| Wait-For Graph | O(n²) | O(n²) | O(n) | O(n²) |
| DFS Cycle Detection | O(V+E) | O(V) | O(V) | O(V+E) |
| Process Termination | O(n²m) | O(n) | O(nm) | O(n²m) |
| Resource Preemption | O(nm) | O(n) | O(nm) | O(nm) |

Where: n = number of processes, m = number of resources, V = vertices, E = edges

### Scalability Analysis

#### Detection Efficiency
- **Banker's Algorithm**: Performs well up to 50 processes
- **Wait-For Graph**: More efficient for sparse resource dependencies  
- **Thread Simulation**: Constant overhead regardless of system size

#### Memory Utilization
- **Linear scaling** with number of processes and resources
- **Efficient matrix storage** using vector containers
- **Minimal overhead** for temporary variables during computation

#### Recovery Performance
- **Process Termination**: Fast victim selection O(n)
- **Resource Preemption**: Immediate resource reallocation
- **Thread Recovery**: Atomic lock acquisition using std::lock

## Conclusion

Our Deadlock Detection and Recovery Tool provides a comprehensive solution for managing resource allocation conflicts in concurrent systems. The implementation successfully demonstrates:

### Key Achievements

- **Robust Detection Mechanisms**: Both Banker's Algorithm and Wait-For Graph methods provide reliable deadlock identification with complementary strengths
- **Effective Recovery Strategies**: Process termination and resource preemption offer flexible approaches to deadlock resolution
- **Real-world Applicability**: Thread synchronization examples bridge the gap between theoretical concepts and practical programming challenges
- **Performance Efficiency**: Optimized algorithms ensure scalability for systems with hundreds of processes and resources
- **Educational Value**: Clear visualization of system states helps users understand deadlock mechanics and prevention strategies

### Technical Contributions

- **Hybrid Detection Approach**: Combining multiple algorithms provides comprehensive coverage of different deadlock scenarios
- **Non-blocking Thread Implementation**: Using `try_lock()` prevents indefinite blocking during deadlock simulation
- **Intelligent Victim Selection**: Resource-based and allocation-based heuristics for optimal recovery performance
- **Extensible Architecture**: Modular design allows easy integration of additional detection and recovery methods

### Future Enhancements

- **Distributed System Support**: Extend algorithms for multi-node deadlock detection
- **Machine Learning Integration**: Predictive models for deadlock prevention
- **GUI Interface**: Visual representation of wait-for graphs and resource allocation
- **Performance Monitoring**: Real-time metrics collection and analysis tools

This tool serves as both an educational resource for understanding deadlock concepts and a practical foundation for building robust concurrent systems. The comprehensive approach to detection, recovery, and prevention makes it valuable for system administrators, software developers, and computer science students working with concurrent programming and operating system design.

---

**Repository**: [Deadlock-Detection-and-Recovery](https://github.com/yjhkdjsg/Deadlock-Detection-and-Recovery)  
**Language**: C++11 with threading support  
**Platform**: Cross-platform (Windows, Linux, macOS)  
