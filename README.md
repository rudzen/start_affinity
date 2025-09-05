# 🚀 StartAffinity

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Windows](https://img.shields.io/badge/Platform-Windows-0078D4.svg)](https://www.microsoft.com/windows)
[![License](https://img.shields.io/badge/License-GPL%20v2-green.svg)](https://www.gnu.org/licenses/gpl-2.0)
[![Version](https://img.shields.io/badge/Version-1.4.1-orange.svg)](#)

> A high-performance CPU affinity control utility for Windows that launches applications with specific processor core assignments. Coupled with a vastly overengineered readme.

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Examples](#-examples)
- [Implementation](#-implementation)
- [Performance Benefits](#-performance-benefits)
- [Architecture](#-architecture)
- [Building](#-building)
- [License](#-license)

## 🎯 Overview

**StartAffinity** is a lightweight, efficient command-line utility that allows you to launch Windows applications with predefined CPU core affinity settings. By controlling which processor cores an application can utilize, you can optimize system performance, reduce context switching overhead, and ensure critical applications get dedicated processing resources.

### 🌟 Key Highlights

- **Zero Dependencies**: Pure C implementation with minimal system footprint
- **Memory Efficient**: Custom arena allocator for optimal memory management
- **High Performance**: Direct Windows API integration for minimal overhead
- **User Friendly**: Simple command-line interface with comprehensive error handling
- **Robust**: Extensive validation of file existence and core availability

## ✨ Features

### Core Functionality
- 🎛️ **CPU Affinity Control**: Assign specific processor cores (0-31) to applications
- 📁 **File Validation**: Automatic verification of executable file existence
- 🔍 **Core Validation**: Ensures requested cores are available on the system
- 🛡️ **Error Handling**: Comprehensive error reporting with Windows API integration
- 💾 **Memory Management**: Custom arena allocator for efficient memory usage

### Technical Features
- ⚡ **Low Latency**: Minimal startup overhead
- 🔧 **Direct API Access**: Uses Windows Process and Thread API directly
- 📊 **System Integration**: Respects system processor affinity masks
- 🚀 **Optimized Parsing**: Efficient command-line argument processing

## 🚀 Installation

### Prerequisites
- Windows 10/11 or Windows Server 2016+
- Visual Studio 2019+ or MinGW-w64 with C++17 support
- CMake 3.15 or higher

### Quick Install
```bash
git clone https://github.com/rudzen/start_affinity.git
cd start_affinity
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

## 💻 Usage

### Basic Syntax
```bash
StartAffinity.exe -f <executable> <core0> [core1] [core2] ... [coreN]
```

### Parameters
- `-f <executable>`: Path to the executable file to launch
- `<core0..N>`: CPU core numbers (0-31) to assign to the process

### Validation Rules
- ✅ Executable file must exist and be accessible
- ✅ Core numbers must be integers between 0 and 31
- ✅ Cores must be available on the current system
- ✅ At least one valid core must be specified

## 📖 Examples

### Single Core Assignment
```bash
# Run Notepad on CPU core 0
StartAffinity.exe -f notepad.exe 0
```

### Multi-Core Assignment
```bash
# Run a game on cores 0, 2, 4, and 6 (even cores for performance)
StartAffinity.exe -f "C:\Games\MyGame.exe" 0 2 4 6

# Run a video encoder on cores 8-15 (dedicated high-performance cores)
StartAffinity.exe -f ffmpeg.exe 8 9 10 11 12 13 14 15
```

### Real-World Scenarios

#### Gaming Performance Optimization
```bash
# Dedicate cores 0-3 for a demanding game, leaving others for system processes
StartAffinity.exe -f "Steam\steamapps\common\game\game.exe" 0 1 2 3
```

#### Scientific Computing
```bash
# Assign specific cores for parallel computation to avoid interference
StartAffinity.exe -f "matlab.exe" 4 5 6 7 8 9 10 11
```

#### Server Applications
```bash
# Isolate database server to specific cores
StartAffinity.exe -f "mysqld.exe" 12 13 14 15
```

## 🏗️ Implementation

### Architecture Overview

StartAffinity is built with performance and reliability as core principles:

```
┌─────────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   Command Line      │───▶│   Argument       │───▶│   Process       │
│   Interface         │    │   Validation     │    │   Creation      │
└─────────────────────┘    └──────────────────┘    └─────────────────┘
           │                          │                        │
           ▼                          ▼                        ▼
┌─────────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   Arena Memory      │    │   File System    │    │   Affinity      │
│   Management        │    │   Validation     │    │   Assignment    │
└─────────────────────┘    └──────────────────┘    └─────────────────┘
```

### Custom Arena Allocator

The application uses a custom arena allocator that provides several advantages:

```cpp
namespace arena {
    struct Arena {
        char* memory;
        size_t size;
        size_t offset;
    };
}
```

**Benefits:**
- **No Memory Fragmentation**: Single large allocation reduces heap fragmentation
- **Fast Allocation**: O(1) allocation time with simple pointer arithmetic
- **Automatic Cleanup**: Single free operation cleans up all allocations
- **Cache Friendly**: Linear memory layout improves cache performance

### Windows API Integration

Direct integration with Windows Process and Thread API ensures:
- **Minimal Overhead**: No additional abstraction layers
- **System Compatibility**: Full compatibility with Windows security model
- **Process Control**: Complete control over process creation and affinity

### Error Handling Strategy

Comprehensive error handling with multiple validation layers:
1. **Command Line Validation**: Syntax and parameter checking
2. **File System Validation**: Executable existence and accessibility
3. **System Validation**: Core availability and system limits
4. **Runtime Validation**: Process creation and affinity assignment

## 🚀 Performance Benefits

### Why CPU Affinity Matters

CPU affinity control provides significant performance benefits in various scenarios:

#### 🎯 **Reduced Context Switching**
- Prevents the OS from migrating processes between cores
- Maintains CPU cache locality
- Reduces overhead from cache misses

#### ⚡ **NUMA Optimization**
- Ensures processes run on cores with local memory access
- Reduces memory latency in multi-socket systems
- Improves bandwidth utilization

#### 🔒 **Resource Isolation**
- Prevents interference between critical and non-critical processes
- Guarantees dedicated resources for high-priority applications
- Enables predictable performance for real-time applications

#### 📊 **Performance Metrics**

(Hypothetical data based on typical use cases)

| Scenario             | Performance Gain      | Use Case                |
|----------------------|-----------------------|-------------------------|
| Gaming               | 5-15% FPS increase    | High-refresh gaming     |
| Video Encoding       | 10-25% faster         | Content creation        |
| Scientific Computing | 15-30% improvement    | HPC workloads           |
| Database Servers     | 10-20% better latency | Enterprise applications |

### When to Use StartAffinity

✅ **Recommended Scenarios:**
- High-performance gaming on multi-core systems
- Video encoding and media processing
- Scientific computing and simulations
- Database and server applications
- Real-time applications requiring predictable latency

❌ **Not Recommended:**
- Single-core systems
- Lightweight desktop applications
- Applications that benefit from dynamic core scheduling

## 🏛️ Architecture

### Design Principles

1. **Simplicity**: Clean, readable C code with minimal complexity
2. **Performance**: Direct system calls and efficient memory management
3. **Reliability**: Comprehensive error handling and validation
4. **Portability**: Windows-specific but architecturally sound design

### Memory Management Philosophy

The custom arena allocator embodies several key principles:

- **Predictable Performance**: No unexpected allocation delays
- **Memory Safety**: Automatic cleanup prevents memory leaks
- **Efficiency**: Minimal overhead compared to general-purpose allocators
- **Simplicity**: Easy to understand and maintain

### Code Quality

- **Modern C++**: Leverages C++17 features where beneficial
- **const-correctness**: Extensive use of const for safety
- **RAII Principles**: Automatic resource management
- **Error Handling**: Comprehensive error checking and reporting

## 🔨 Building

### Build Commands

#### Debug Build
```bash
cmake --build . --config Debug
```

#### Release Build (Recommended)
```bash
cmake --build . --config Release
```

Or just use the basic g++ since there are no dependencies.

## 📄 License

```
StartAffinity 1.4.1 (c) 2020-2025 Rudy Alex Kohn
StartAffinity 1.3.1 (c) 2006 Adsci Engineering, LLC

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
```

See [LICENSE](LICENSE) for full details.

---

<div>

**⭐ Star this repository if you find it useful!**

[Report Bug](https://github.com/rudzen/start_affinity/issues) • [Request Feature](https://github.com/rudzen/start_affinity/issues) • [Documentation](https://github.com/rudzen/start_affinity/wiki)

</div>
