# 🔒 Deadlock Detection and Recovery Tool

## 📋 Table of Contents

- [🔒 Deadlock Detection and Recovery System](#-deadlock-detection-and-recovery-system)
  - [📋 Table of Contents](#-table-of-contents)
  - [✨ Features](#-features)
  - [🏗️ System Architecture](#️-system-architecture)
  - [🚀 Quick Start](#-quick-start)
    - [Prerequisites](#prerequisites)
    - [Compilation](#compilation)
    - [Running the Program](#running-the-program)
  - [📖 Usage Guide](#-usage-guide)
    - [1. Main Menu Options](#1-main-menu-options)
    - [2. Input Methods](#2-input-methods)
    - [3. Detection Algorithms](#3-detection-algorithms)
    - [4. Recovery Strategies](#4-recovery-strategies)
    - [5. Thread Deadlock Simulation](#5-thread-deadlock-simulation)
  - [📁 File Structure](#-file-structure)
  - [🔧 Input File Formats](#-input-file-formats)
    - [available.txt](#availabletxt)
    - [maximum.txt](#maximumtxt)
    - [allocation.txt](#allocationtxt)
  - [🧮 Algorithms Implemented](#-algorithms-implemented)
    - [1. Banker's Algorithm](#1-bankers-algorithm)
    - [2. Wait-For Graph](#2-wait-for-graph)
    - [3. Thread Deadlock Detection](#3-thread-deadlock-detection)
  - [🛠️ Recovery Mechanisms](#️-recovery-mechanisms)
    - [Process Termination](#process-termination)
    - [Resource Preemption](#resource-preemption)
    - [Ordered Locking (Prevention)](#ordered-locking-prevention)
  - [💡 Example Scenarios](#-example-scenarios)
    - [Scenario 1: Safe State Detection](#scenario-1-safe-state-detection)
    - [Scenario 2: Deadlock Detection and Recovery](#scenario-2-deadlock-detection-and-recovery)
    - [Scenario 3: Thread Deadlock Simulation](#scenario-3-thread-deadlock-simulation)
  - [🔬 Technical Details](#-technical-details)
    - [Class Structure](#class-structure)
    - [Key Data Structures](#key-data-structures)
    - [Thread Safety](#thread-safety)
  - [📊 Performance Analysis](#-performance-analysis)
  - [🎯 Educational Applications](#-educational-applications)
  - [🚨 Troubleshooting](#-troubleshooting)
    - [Common Issues](#common-issues)
    - [Error Messages](#error-messages)
  - [🤝 Contributing](#-contributing)
  - [📜 License](#-license)
  - [👥 Authors](#-authors)
  - [🙏 Acknowledgments](#-acknowledgments)

## ✨ Features

### 🔍 **Deadlock Detection Algorithms**
- **Banker's Algorithm**: Resource allocation safety verification
- **Wait-For Graph**: Cycle detection in resource dependency graphs
- **Safe Sequence Generation**: Finding safe execution order for processes

### 🔧 **Recovery Strategies**
- **Process Termination**: Strategic process elimination to break deadlocks
- **Resource Preemption**: Temporary resource reallocation
- **Victim Selection**: Optimal process selection for minimal impact

### 🧵 **Thread Deadlock Simulation**
- **Mutex-based Deadlock**: Real-world thread synchronization scenarios
- **Custom Delay Configuration**: Adjustable timing for deadlock conditions
- **Prevention Demonstration**: Ordered locking techniques

### 📊 **Input Methods**
- **File-based Input**: Predefined test cases from external files
- **Manual Input**: Interactive data entry with validation
- **Random Generation**: Automated test case creation

### 🎛️ **User Interface**
- **Menu-driven Interface**: Easy navigation and operation
- **Detailed Output**: Comprehensive status reporting and analysis
- **Error Handling**: Robust input validation and error recovery

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Main Application                          │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────────┐    ┌──────────────────────────────┐    │
│  │   Input Module  │    │      Detection Module       │    │
│  │                 │    │                              │    │
│  │ • File Input    │◄──►│ • Banker's Algorithm         │    │
│  │ • Manual Input  │    │ • Wait-For Graph             │    │
│  │ • Random Gen    │    │ • Safe Sequence Generation   │    │
│  └─────────────────┘    └──────────────────────────────┘    │
│           │                           │                     │
│           ▼                           ▼                     │
│  ┌─────────────────┐    ┌──────────────────────────────┐    │
│  │ Thread Deadlock │    │      Recovery Module         │    │
│  │   Simulation    │    │                              │    │
│  │                 │    │ • Process Termination        │    │
│  │ • Mutex Demo    │    │ • Resource Preemption        │    │
│  │ • Prevention    │    │ • State Restoration          │    │
│  │ • Custom Tests  │    │ • Victim Selection           │    │
│  └─────────────────┘    └──────────────────────────────┘    │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## 🚀 Quick Start

### Prerequisites

- **C++ Compiler**: GCC 7.0+ or Visual Studio 2017+
- **C++ Standard**: C++11 or later
- **Operating System**: Windows, Linux, or macOS
- **Memory**: Minimum 4MB RAM
- **Storage**: 50MB available space

### Compilation

**Using GCC (Linux/Windows with MinGW):**
```bash
g++ -std=c++11 -pthread -o deadlock_detector deadlock_detection_and_recovery.cpp
```

**Using Visual Studio (Windows):**
```cmd
cl /EHsc /std:c++11 deadlock_detection_and_recovery.cpp
```

**Using Clang (macOS/Linux):**
```bash
clang++ -std=c++11 -pthread -o deadlock_detector deadlock_detection_and_recovery.cpp
```

### Running the Program

```bash
# Linux/macOS
./deadlock_detector

# Windows
deadlock_detector.exe
```

## 📖 Usage Guide

### 1. Main Menu Options

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
```

### 2. Input Methods

#### **Option 1: File Input**
- Requires three input files: `available.txt`, `maximum.txt`, `allocation.txt`
- Automatically loads and validates system state
- Ideal for batch testing and predefined scenarios

#### **Option 2: Manual Input**
- Interactive data entry with real-time validation
- Guides user through process and resource configuration
- Perfect for custom scenarios and educational demonstrations

#### **Option 3: Random Generation**
- Automated test case creation with configurable parameters
- Generates realistic resource allocation scenarios
- Excellent for stress testing and algorithm analysis

### 3. Detection Algorithms

#### **Banker's Algorithm**
- Determines if the system is in a safe state
- Generates safe execution sequence if available
- Identifies processes that cannot complete

#### **Wait-For Graph**
- Constructs dependency graph between processes
- Detects cycles indicating deadlock conditions
- Provides visual representation of process relationships

### 4. Recovery Strategies

#### **Process Termination**
- Selects victim processes for termination
- Minimizes impact through strategic selection
- Restores system to safe state

#### **Resource Preemption**
- Temporarily reallocates resources
- Rollback capability for failed recovery
- Maintains system consistency

### 5. Thread Deadlock Simulation

```
========================================================
         THREAD DEADLOCK DETECTION & RECOVERY         
========================================================
  1. Run predefined thread deadlock simulation         
  2. Run custom thread deadlock simulation             
  3. Demonstrate deadlock prevention (ordered locking) 
  0. Back to main menu                                 
========================================================
```

## 📁 File Structure

```
OSSP/
├── deadlock_detection_and_recovery.cpp    # Main source code
├── README.md                               # This documentation
├── Project_Synopsis.md                     # Project synopsis
├── available.txt                           # Available resources (optional)
├── maximum.txt                            # Maximum resource needs (optional)
├── allocation.txt                         # Current allocations (optional)
└── examples/                              # Example input files
    ├── safe_scenario/
    │   ├── available.txt
    │   ├── maximum.txt
    │   └── allocation.txt
    └── deadlock_scenario/
        ├── available.txt
        ├── maximum.txt
        └── allocation.txt
```

## 🔧 Input File Formats

### available.txt
```
3
2 1 0
```
- First line: Number of resource types
- Second line: Available instances of each resource type

### maximum.txt
```
5 3
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
```
- First line: Number of processes and resource types
- Following lines: Maximum resource needs for each process

### allocation.txt
```
5 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
```
- First line: Number of processes and resource types
- Following lines: Currently allocated resources for each process

## 🧮 Algorithms Implemented

### 1. Banker's Algorithm

**Purpose**: Determine if a resource allocation request can be safely granted

**Steps**:
1. Check if request ≤ need
2. Check if request ≤ available
3. Temporarily allocate resources
4. Run safety algorithm
5. Grant or deny request based on safety

**Time Complexity**: O(n²m) where n = processes, m = resource types

**Code Example**:
```cpp
bool bankersAlgorithmDetection(vector<int>& safeSequence) {
    vector<int> work = available;
    vector<bool> finish(numProcesses, false);
    
    // Find safe sequence
    while (count < numProcesses) {
        // Find process that can finish
        if (canFinish && !finish[i]) {
            // Allocate resources and mark as finished
        }
    }
    
    return safeSequenceFound;
}
```

### 2. Wait-For Graph

**Purpose**: Detect deadlock by identifying cycles in process dependency graph

**Steps**:
1. Construct wait-for graph
2. Identify blocked processes
3. Create edges between waiting processes
4. Perform cycle detection using DFS
5. Report deadlock if cycle found

**Time Complexity**: O(n²) for graph construction + O(n+e) for cycle detection

**Code Example**:
```cpp
bool waitForGraphDetection() {
    // Build wait-for graph
    for (int i = 0; i < numProcesses; ++i) {
        if (processIsBlocked(i)) {
            for (int j = 0; j < numProcesses; ++j) {
                if (processHoldsNeededResource(j, i)) {
                    waitForGraph[i][j] = true;
                }
            }
        }
    }
    
    // Detect cycles using DFS
    return hasCycle(waitForGraph);
}
```

### 3. Thread Deadlock Detection

**Purpose**: Simulate and detect mutex-based deadlocks in multi-threaded environments

**Mechanism**:
- Thread A: locks m1 → tries m2
- Thread B: locks m2 → tries m1
- Detection: Use `try_lock()` to avoid blocking
- Recovery: Use `std::lock()` for ordered acquisition

**Code Example**:
```cpp
void simulateThreadDeadlock(int delayA, int delayB) {
    auto threadA = [&]() {
        m1.lock();
        this_thread::sleep_for(chrono::milliseconds(delayA));
        if (!m2.try_lock()) {
            threadDeadlockDetected = true;
        }
        m1.unlock();
    };
    
    // Similar for threadB
    thread t1(threadA), t2(threadB);
    t1.join(); t2.join();
}
```

## 🛠️ Recovery Mechanisms

### Process Termination

**Strategy**: Terminate minimum number of processes to break deadlock

**Selection Criteria**:
- Minimum resource allocation
- Lowest priority processes
- Least progress made

**Implementation**:
```cpp
void processTermination(bool deadlockDetected) {
    if (deadlockDetected) {
        // Select victim with minimum allocation
        int victim = findMinimumAllocationProcess();
        
        // Terminate and reclaim resources
        terminateProcess(victim);
        
        // Verify system is now safe
        verifySystemSafety();
    }
}
```

### Resource Preemption

**Strategy**: Temporarily remove resources from processes

**Considerations**:
- Rollback capability
- Process state preservation
- Resource type constraints

**Implementation**:
```cpp
void resourcePreemption(bool deadlockDetected) {
    if (deadlockDetected) {
        // Select victim for preemption
        int victim = selectPreemptionVictim();
        
        // Preempt resources
        preemptResources(victim);
        
        // Attempt to resolve deadlock
        if (!tryResolveDeadlock()) {
            rollbackPreemption(victim);
        }
    }
}
```

### Ordered Locking (Prevention)

**Strategy**: Prevent deadlocks by consistent lock ordering

**Benefits**:
- No deadlock detection overhead
- Guaranteed deadlock freedom
- Simple implementation

**Implementation**:
```cpp
void preventiveThreadExample() {
    // Both threads acquire locks in same order
    auto threadFunction = []() {
        lock(m1, m2);  // Atomic ordered acquisition
        // Critical section
        m2.unlock();
        m1.unlock();
    };
}
```

## 💡 Example Scenarios

### Scenario 1: Safe State Detection

**Input**:
```
Processes: 5, Resources: 3
Available: [3, 3, 2]
Maximum:   [[7,5,3], [3,2,2], [9,0,2], [2,2,2], [4,3,3]]
Allocation:[[0,1,0], [2,0,0], [3,0,2], [2,1,1], [0,0,2]]
```

**Output**:
```
[SAFE STATE] No deadlock detected.
Safe sequence: P1 P3 P4 P0 P2
```

### Scenario 2: Deadlock Detection and Recovery

**Input** (Deadlock scenario):
```
Processes: 3, Resources: 2
Available: [0, 0]
Maximum:   [[3,2], [2,3], [1,1]]
Allocation:[[2,1], [1,2], [1,0]]
```

**Output**:
```
[DEADLOCK DETECTED] System is in unsafe state!
Processes that cannot finish: P0 P1 P2

Terminating culprit process P2
Recovered. New safe sequence: P0 P1
```

### Scenario 3: Thread Deadlock Simulation

**Execution**:
```bash
Running predefined thread deadlock simulation...
Using delays: Thread A = 100ms, Thread B = 100ms

Thread A locking m1...
Thread B locking m2...
Thread A trying to lock m2...
Thread A failed to lock m2. Possible deadlock detected.
Thread B trying to lock m1...
Thread B failed to lock m1. Possible deadlock detected.

Thread deadlock detected!

Recovering from thread deadlock using ordered locking...
Successfully acquired both locks in ordered manner.
Thread deadlock recovered successfully.
```

## 🔬 Technical Details

### Class Structure

```cpp
class DeadlockDetector {
private:
    int numProcesses;                    // System size
    int numResources;                    // Resource types
    vector<int> available;               // Available resources
    vector<vector<int>> maximum;         // Max needs
    vector<vector<int>> allocation;      // Current allocation
    vector<vector<int>> need;            // Remaining needs

public:
    bool readFromFiles();                // File input
    bool inputFromUser();                // Manual input
    bool generateRandomInput();          // Random generation
    void displayState();                 // System state display
    bool bankersAlgorithmDetection();    // Banker's algorithm
    bool waitForGraphDetection();        // Wait-for graph
    void processTermination();           // Recovery by termination
    void resourcePreemption();           // Recovery by preemption
};
```

### Key Data Structures

**Matrices Used**:
- **Available[m]**: Available instances of each resource type
- **Maximum[n][m]**: Maximum resource needs per process
- **Allocation[n][m]**: Currently allocated resources
- **Need[n][m]**: Remaining resource needs (Max - Allocation)

**Thread Synchronization**:
- **mutex m1, m2**: Two mutexes for deadlock simulation
- **bool threadDeadlockDetected**: Global deadlock detection flag

### Thread Safety

**Synchronization Mechanisms**:
- `std::mutex` for resource protection
- `std::lock()` for ordered acquisition
- `try_lock()` for non-blocking attempts
- `std::thread::join()` for synchronization

**Deadlock Prevention**:
- Consistent lock ordering
- Timeout mechanisms
- Non-blocking operations

## 📊 Performance Analysis

### Time Complexities

| Algorithm | Best Case | Average Case | Worst Case |
|-----------|-----------|--------------|------------|
| Banker's Algorithm | O(nm) | O(n²m) | O(n²m) |
| Wait-For Graph | O(n²) | O(n²) | O(n²) |
| Cycle Detection | O(n+e) | O(n+e) | O(n+e) |

**Where**: n = number of processes, m = number of resource types, e = edges

### Space Complexity

- **Banker's Algorithm**: O(nm) for matrices
- **Wait-For Graph**: O(n²) for adjacency matrix
- **Thread Simulation**: O(1) for synchronization primitives

### Scalability

**Recommended Limits**:
- Processes: Up to 1000 for optimal performance
- Resources: Up to 100 resource types
- Concurrent Threads: Limited by system capabilities

## 🎯 Educational Applications

### **Operating Systems Courses**
- Practical demonstration of deadlock concepts
- Algorithm implementation and analysis
- Resource management understanding

### **Concurrent Programming**
- Thread synchronization techniques
- Mutex usage and best practices
- Deadlock prevention strategies

### **Algorithm Analysis**
- Complexity analysis and optimization
- Graph algorithms and cycle detection
- Safety and liveness properties

### **System Design**
- Resource allocation strategies
- Recovery mechanism design
- Performance trade-off analysis

## 🚨 Troubleshooting

### Common Issues

**Compilation Errors**:
```bash
# Missing thread support
g++ -std=c++11 -pthread deadlock_detection_and_recovery.cpp

# C++ standard issues
g++ -std=c++14 deadlock_detection_and_recovery.cpp
```

**Runtime Issues**:
```bash
# File not found
Error: Could not open one or more input files!
Solution: Ensure input files exist in current directory

# Invalid input
Invalid input! Values must be positive.
Solution: Check input format and value ranges
```

**Thread Issues**:
```bash
# Pthread linking (Linux)
g++ -pthread deadlock_detection_and_recovery.cpp

# Windows thread support
Use Visual Studio or MinGW with pthread support
```

### Error Messages

| Error Message | Cause | Solution |
|---------------|-------|----------|
| "Could not open input files" | Missing input files | Create required .txt files |
| "Invalid process ID" | Out of range process ID | Use valid process indices |
| "Allocation exceeds maximum" | Invalid resource allocation | Check allocation constraints |
| "Request denied - unsafe state" | Unsafe resource request | Modify request or system state |

## 🤝 Contributing

We welcome contributions to improve the Deadlock Detection and Recovery System!

### **How to Contribute**

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### **Contribution Guidelines**

- **Code Style**: Follow existing code formatting and commenting standards
- **Testing**: Include test cases for new features
- **Documentation**: Update README and inline comments
- **Performance**: Consider algorithm efficiency and memory usage

### **Areas for Enhancement**

- **GUI Interface**: Graphical user interface development
- **Distributed Systems**: Network-based deadlock detection
- **Performance Optimization**: Algorithm efficiency improvements
- **Additional Algorithms**: Implementation of other detection methods
- **Visualization**: Graphical representation of system states
- **Real-time Monitoring**: Continuous system monitoring capabilities

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2025 Deadlock Detection System Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

## 👥 Authors

- **Primary Developer**: [Your Name] - *Initial work and implementation*
- **Contributors**: See [Contributors](https://github.com/username/deadlock-detection/contributors) for full list

### **Contact Information**
- **Email**: your.email@example.com
- **GitHub**: [@yourusername](https://github.com/yourusername)
- **LinkedIn**: [Your Profile](https://linkedin.com/in/yourprofile)

## 🙏 Acknowledgments

### **Academic References**
- **Dijkstra, E. W.** - Banker's Algorithm and Semaphore concepts
- **Holt, R. C.** - Wait-For Graph methodology
- **Silberschatz, Galvin, Gagne** - Operating System Concepts

### **Technical Inspiration**
- **C++ Standards Committee** - Modern C++ threading capabilities
- **POSIX Threads** - Thread synchronization standards
- **Operating Systems Community** - Deadlock research and solutions

### **Educational Support**
- **University Faculty** - Guidance and theoretical foundation
- **Student Community** - Testing and feedback
- **Open Source Projects** - Implementation patterns and best practices

---

**⭐ If you find this project helpful, please consider giving it a star!**

**📫 Questions or suggestions? Feel free to open an issue or contact the maintainers.**

---

*Last Updated: November 24, 2025*
