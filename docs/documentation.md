---
layout: default
title: Documentation
permalink: /docs/
---

# 📚 Documentation

## Installation Guide

### System Requirements

- **Operating System**: Windows 10/11 or Windows Server 2016+
- **Compiler**: Visual Studio 2019+ or MinGW-w64 with C++17 support
- **Build System**: CMake 3.15 or higher
- **Memory**: Minimum 4MB free RAM
- **Disk Space**: 2MB for executable

### Build from Source

1. **Clone the repository**
   ```bash
   git clone https://github.com/rudzen/start_affinity.git
   cd start_affinity
   ```

2. **Create build directory**
   ```bash
   mkdir build && cd build
   ```

3. **Configure with CMake**
   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```

4. **Build the project**
   ```bash
   cmake --build . --config Release
   ```

5. **Find the executable**
   The built executable will be in `exe/Release/sa.exe`

## Command Line Reference

### Syntax
```
StartAffinity.exe -f <executable> <core0> [core1] [core2] ... [coreN]
```

### Parameters

| Parameter         | Description             | Required | Valid Values    |
|-------------------|-------------------------|----------|-----------------|
| `-f <executable>` | Path to executable file | Yes      | Valid file path |
| `<core0..N>`      | CPU core numbers        | Yes      | Integers 0-31   |

### Validation Rules

- ✅ **File Validation**: Executable must exist and be accessible
- ✅ **Core Validation**: Each core number must be between 0-31
- ✅ **System Validation**: Cores must be available on current system
- ✅ **Argument Validation**: At least one core must be specified

## Advanced Usage

### CPU Core Selection Strategies

#### Even/Odd Core Strategy
```bash
# Use even cores for gaming (often better for performance)
StartAffinity.exe -f game.exe 0 2 4 6

# Use odd cores for background tasks
StartAffinity.exe -f backup.exe 1 3 5 7
```

#### NUMA-Aware Selection
```bash
# First NUMA node (typically cores 0-7 on dual-socket systems)
StartAffinity.exe -f app.exe 0 1 2 3

# Second NUMA node (typically cores 8-15)
StartAffinity.exe -f app.exe 8 9 10 11
```

#### Hyperthreading Considerations
```bash
# Physical cores only (avoid hyperthreads)
StartAffinity.exe -f cpu_intensive.exe 0 2 4 6 8 10

# Include hyperthreads for I/O bound applications
StartAffinity.exe -f io_app.exe 0 1 2 3 4 5 6 7
```

### Performance Tuning Tips

#### For Gaming
- Reserve cores 0-3 for the game
- Leave remaining cores for Windows and background processes
- Disable hyperthreading siblings if experiencing stuttering

#### For Content Creation
- Use high-performance cores (typically higher numbered)
- Assign 50-75% of available cores
- Monitor temperatures under sustained load

#### For Servers
- Isolate server processes to specific cores
- Reserve at least 1-2 cores for system processes
- Consider NUMA topology for multi-socket systems

## Troubleshooting

### Common Issues

#### "Failed to initialize memory arena"
**Cause**: Insufficient memory or system restrictions
**Solution**: 
- Ensure at least 4MB of free RAM
- Run as administrator if needed
- Close unnecessary applications

#### "File not found" Error
**Cause**: Specified executable doesn't exist or path is incorrect
**Solution**:
- Verify file path is correct
- Use absolute paths for files outside current directory
- Check file permissions

#### "Invalid core number" Error
**Cause**: Specified core number is outside valid range (0-31)
**Solution**:
- Use `wmic cpu get NumberOfLogicalProcessors` to check available cores
- Ensure core numbers are between 0 and (NumberOfLogicalProcessors - 1)

#### Process Starts but Affinity Not Set
**Cause**: Insufficient privileges or system restrictions
**Solution**:
- Run as administrator
- Check Windows security policies
- Verify target process allows affinity changes

### Debugging Steps

1. **Verify System Information**
   ```cmd
   wmic cpu get Name,NumberOfCores,NumberOfLogicalProcessors
   ```

2. **Check Current Process Affinity**
   ```cmd
   wmic process where name="processname.exe" get ProcessAffinityMask
   ```

3. **Test with Simple Application**
   ```cmd
   StartAffinity.exe -f notepad.exe 0
   ```

## API Reference

### Core Data Structures

```cpp
// Arena allocator for memory management
struct Arena {
    char* memory;    // Allocated memory block
    size_t size;     // Total size of arena
    size_t offset;   // Current allocation offset
};

// CPU cores container
struct Cores {
    int* cores;      // Array of core numbers
    int count;       // Number of cores
};
```

### Key Functions

#### `arena_init(Arena* arena, size_t size)`
Initializes the memory arena with specified size.

**Parameters:**
- `arena`: Pointer to Arena structure
- `size`: Size in bytes to allocate

**Returns:** 1 on success, 0 on failure

#### `parse_args(Arena* arena, int argc, char* argv[], char** filename, Cores* cores)`
Parses command line arguments and validates input.

**Parameters:**
- `arena`: Memory arena for allocations
- `argc`: Argument count
- `argv`: Argument vector
- `filename`: Output parameter for executable path
- `cores`: Output parameter for core list

**Returns:** 1 on success, 0 on failure

#### `run_start_affinity(const char* filename, const Cores* cores)`
Launches the specified executable with CPU affinity set.

**Parameters:**
- `filename`: Path to executable
- `cores`: CPU cores to assign

**Returns:** 0 on success, non-zero on failure

## Examples Gallery

### Real-World Scenarios

#### High-Performance Gaming Setup
```bash
# Primary game on dedicated cores
StartAffinity.exe -f "C:\Games\Cyberpunk2077\bin\x64\Cyberpunk2077.exe" 0 1 2 3

# Game launcher on different cores
StartAffinity.exe -f "C:\Program Files (x86)\GOG Galaxy\GalaxyClient.exe" 4 5

# Background apps on remaining cores
StartAffinity.exe -f "C:\Program Files\OBS Studio\bin\64bit\obs64.exe" 6 7
```

#### Video Production Workflow
```bash
# Video editor on high-performance cores
StartAffinity.exe -f "C:\Program Files\Adobe\Premiere Pro 2023\Adobe Premiere Pro.exe" 8 9 10 11 12 13 14 15

# Media encoder on separate cores
StartAffinity.exe -f "C:\Program Files\Adobe\Adobe Media Encoder 2023\Adobe Media Encoder.exe" 4 5 6 7

# Preview playback on dedicated cores
StartAffinity.exe -f vlc.exe 0 1
```

#### Server Environment
```bash
# Database server
StartAffinity.exe -f "C:\Program Files\MySQL\MySQL Server 8.0\bin\mysqld.exe" 8 9 10 11

# Web server
StartAffinity.exe -f "C:\nginx\nginx.exe" 4 5 6 7

# Monitoring tools
StartAffinity.exe -f "C:\Program Files\Prometheus\prometheus.exe" 12 13
```

## Best Practices

### Performance Optimization
1. **Profile Before Optimizing**: Use performance monitoring tools
2. **Start Conservative**: Begin with fewer cores and add more as needed
3. **Monitor System Health**: Watch CPU temperatures and utilization
4. **Test Thoroughly**: Validate performance improvements with benchmarks

### System Stability
1. **Reserve System Cores**: Always leave cores for Windows
2. **Avoid Core 0**: Reserve core 0 for system interrupts when possible
3. **Gradual Changes**: Make incremental adjustments
4. **Document Configuration**: Keep records of working configurations

### Security Considerations
1. **Run with Minimum Privileges**: Use standard user account when possible
2. **Validate Executables**: Only run trusted applications
3. **Monitor Resource Usage**: Watch for unexpected behavior
4. **Regular Updates**: Keep system and applications updated
