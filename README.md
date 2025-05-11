# AlgoSystem

This repository contains both **real-world system-level C++ projects** and **algorithmic practice code**.
It is organized into clearly separated folders for system development, LeetCode problems, and reusable algorithm components.

---

## 📁 Directory Structure

| Folder                             | Description                                                            |
| ---------------------------------- | ---------------------------------------------------------------------- |
| `SystemDev/`                     | 🔧 Realistic C++ modules using Boost, multithreading, networking, etc. |
| `LeetCode/`                      | 📘 LeetCode-style algorithm problem solutions with comments and tests  |
| `GeneralAlgorithmDataStructure/` | 📚 Reusable data structures and algorithms in C and C++                |
| `RealInterviewCollection/`       | 💼 Problem patterns and coding questions from real-world interviews    |
| `README.md`                      | This file                                                              |

---

## 🔧 What’s in `SystemDev/`

The `SystemDev` directory is organized like a real software project, with:

- Google C++ Style Guide (`snake_case`, `PascalCase` class names)
- `include/`, `src/`, `bin/`, `lib/`, `Makefile`
- Modular Boost examples: threads, socket, serialization, coroutine, etc.

See [`SystemDev/README.md`](./SystemDev/README.md) for full breakdown.

---

## 🧠 Learning Sections

These directories are for self-practice, algorithm templates, and interview prep.
Naming conventions are relaxed here, and structure prioritizes readability.

### `LeetCode/`

- Categorized problems (DP, graph, backtracking, math, bitwise)
- Each file contains:
  - Problem description
  - Edge case analysis
  - Full commented solution with `main()` testing

### `GeneralAlgorithmDataStructure/`

- C/C++ code for:
  - Union-Find, Trie, Segment Tree, Heap, Graph traversal
  - Sorts (Quick/Merge/Heap), BFS/DFS, KMP/Z-algo, Sliding window

---

## 🧪 How I Use This Repo

- 📘 Use `LeetCode/` and `RealInterviewCollection/` for daily problem-solving
- 🔨 Build robust systems in `SystemDev/` to simulate real infrastructure
- 🧹 Maintain style only in `SystemDev/`; other folders are exploratory

---

## 🛠 Future Plans

- `MachineLearningCpp/`: Math-based ML implementation in C++
- `LinuxTools/`: GDB, Valgrind, Makefile, Docker practice
- `ConcurrencySandbox/`: Lock-free, thread-safe container implementations
- `RustCppInterop/`: Call C++ modules from Rust and vice versa

---
