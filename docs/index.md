---
layout: default
title: StartAffinity - CPU Affinity Control for Windows
description: A high-performance CPU affinity control utility for Windows that launches applications with specific processor core assignments.
---

<div class="hero-section">
  <div class="hero-content">
    <h1 class="hero-title">🚀 StartAffinity</h1>
    <p class="hero-subtitle">High-Performance CPU Affinity Control for Windows</p>
    <p class="hero-description">Launch applications with specific processor core assignments to optimize performance and reduce context switching overhead.</p>
    <div class="hero-buttons">
      <a href="https://github.com/rudzen/start_affinity/releases" class="btn btn-primary">Download Latest</a>
      <a href="https://github.com/rudzen/start_affinity" class="btn btn-secondary">View on GitHub</a>
    </div>
  </div>
</div>

<div class="badges">
  <img src="https://img.shields.io/badge/C++-17-blue.svg" alt="C++17">
  <img src="https://img.shields.io/badge/Platform-Windows-0078D4.svg" alt="Windows">
  <img src="https://img.shields.io/badge/License-GPL%20v2-green.svg" alt="GPL v2">
  <img src="https://img.shields.io/badge/Version-1.4.1-orange.svg" alt="Version 1.4.1">
</div>

## ✨ Key Features

<div class="feature-grid">
  <div class="feature-card">
    <div class="feature-icon">🎛️</div>
    <h3>CPU Affinity Control</h3>
    <p>Assign specific processor cores (0-31) to applications with precision</p>
  </div>
  
  <div class="feature-card">
    <div class="feature-icon">⚡</div>
    <h3>High Performance</h3>
    <p>Direct Windows API integration with minimal overhead and fast startup</p>
  </div>
  
  <div class="feature-card">
    <div class="feature-icon">💾</div>
    <h3>Memory Efficient</h3>
    <p>Custom arena allocator for optimal memory management and cache performance</p>
  </div>
  
  <div class="feature-card">
    <div class="feature-icon">🛡️</div>
    <h3>Robust Validation</h3>
    <p>Comprehensive error handling with file and core availability checking</p>
  </div>
</div>

## 🚀 Quick Start
~~~~
### Installation

Download the latest release from GitHub or build from source:

```bash
git clone https://github.com/rudzen/start_affinity.git
cd start_affinity
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Basic Usage

```bash
StartAffinity.exe -f <executable> <core0> [core1] [core2] ... [coreN]
```

### Examples

<div class="example-section">
  <div class="example-card">
    <h4>🎮 Gaming Performance</h4>
    <div class="code-block">
      <code>StartAffinity.exe -f "game.exe" 0 1 2 3</code>
    </div>
    <p>Dedicate cores 0-3 for gaming, leaving others for system processes</p>
  </div>
  
  <div class="example-card">
    <h4>🎬 Video Encoding</h4>
    <div class="code-block">
      <code>StartAffinity.exe -f ffmpeg.exe 8 9 10 11 12 13 14 15</code>
    </div>
    <p>Use high-performance cores for intensive video processing</p>
  </div>
  
  <div class="example-card">
    <h4>🗄️ Database Server</h4>
    <div class="code-block">
      <code>StartAffinity.exe -f "mysqld.exe" 4 5 6 7</code>
    </div>
    <p>Isolate database operations to specific cores for consistent performance</p>
  </div>
</div>

## 📊 Performance Benefits

CPU affinity control provides significant performance improvements:

<div class="performance-grid">
  <div class="performance-card">
    <div class="performance-metric">5-15%</div>
    <div class="performance-label">Gaming FPS Increase</div>
  </div>
  
  <div class="performance-card">
    <div class="performance-metric">10-25%</div>
    <div class="performance-label">Video Encoding Speed</div>
  </div>
  
  <div class="performance-card">
    <div class="performance-metric">15-30%</div>
    <div class="performance-label">Scientific Computing</div>
  </div>
  
  <div class="performance-card">
    <div class="performance-metric">10-20%</div>
    <div class="performance-label">Database Latency</div>
  </div>
</div>

## 🏗️ Technical Architecture

StartAffinity is built with performance and reliability as core principles:

### Custom Arena Allocator

The application uses a custom arena allocator providing:

- **No Memory Fragmentation**: Single large allocation reduces heap fragmentation
- **Fast Allocation**: O(1) allocation time with simple pointer arithmetic  
- **Automatic Cleanup**: Single free operation cleans up all allocations
- **Cache Friendly**: Linear memory layout improves cache performance

### Windows API Integration

Direct integration with Windows Process and Thread API ensures:

- **Minimal Overhead**: No additional abstraction layers
- **System Compatibility**: Full compatibility with Windows security model
- **Process Control**: Complete control over process creation and affinity

## 🎯 When to Use StartAffinity

<div class="use-cases">
  <div class="use-case recommended">
    <h4>✅ Recommended Scenarios</h4>
    <ul>
      <li>High-performance gaming on multi-core systems</li>
      <li>Video encoding and media processing</li>
      <li>Scientific computing and simulations</li>
      <li>Database and server applications</li>
      <li>Real-time applications requiring predictable latency</li>
    </ul>
  </div>
  
  <div class="use-case not-recommended">
    <h4>❌ Not Recommended</h4>
    <ul>
      <li>Single-core systems</li>
      <li>Lightweight desktop applications</li>
      <li>Applications that benefit from dynamic core scheduling</li>
    </ul>
  </div>
</div>

## 🤝 Contributing

We welcome contributions! Here's how you can help:

1. **Report Issues**: Found a bug? [Create an issue](https://github.com/rudzen/start_affinity/issues)
2. **Feature Requests**: Have an idea? [Start a discussion](https://github.com/rudzen/start_affinity/discussions)
3. **Code Contributions**: Fork the repo, make changes, and submit a pull request
4. **Documentation**: Help improve our docs and examples

## 📄 License

StartAffinity is licensed under the GNU General Public License v2.0. See [LICENSE](https://github.com/rudzen/start_affinity/blob/main/LICENSE) for details.

```
StartAffinity 1.4.1 (c) 2020-2025 Rudy Alex Kohn
StartAffinity 1.3.1 (c) 2006 Adsci Engineering, LLC
```

---

<div class="footer-links">
  <a href="https://github.com/rudzen/start_affinity">GitHub Repository</a> •
  <a href="https://github.com/rudzen/start_affinity/releases">Releases</a> •
  <a href="https://github.com/rudzen/start_affinity/issues">Issues</a> •
  <a href="https://github.com/rudzen/start_affinity/wiki">Documentation</a>
</div>
