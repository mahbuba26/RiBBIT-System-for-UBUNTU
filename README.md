# Arborescent Garbage Collector (C Implementation)

This project implements a custom **Arborescent Garbage Collector (GC)** in C, inspired by dynamic graph-based memory management techniques.

Unlike traditional collectors (e.g., Mark-and-Sweep), this GC:

- Tracks object relationships as a **reference graph**
- Maintains a **spanning forest** to represent reachability
- Performs **immediate cycle collection**
- Supports **phase-wise visualization** using Graphviz (DOT format)

The system also includes benchmark programs (`fib`, `sum`, `ack`) to evaluate GC behavior and performance under different allocation patterns.

---

## Features

- ✅ Custom memory management (no direct use of `malloc/free`)
- ✅ Graph-based reachability tracking
- ✅ Immediate garbage collection (no deferred cycle detection)
- ✅ Clearly defined GC phases:
  - `init`
  - `drop`
  - `catch`
  - `collect`
- ✅ DOT/SVG visualization export
- ✅ Integrated benchmarks:
  - Fibonacci
  - Summation
  - Ackermann

---

## Project Structure

GC-Arborescent/
│── main.c # Entry point

│── gc.c # Garbage collector implementation

│── gc.h

│── bench.c # Benchmark logic (fib, sum, ack)

│── bench.h

│── CMakeLists.txt


---

## How to Build 

'''bash

mkdir build

cd build

cmake ..

make'''

---

## Visualization (Graphviz)

This project exports GC states as DOT/SVG files for each phase.

Example:
gc_init();
gc_export_dot("graph_init.dot");

gc_drop();
gc_export_dot("graph_drop.dot");

gc_catch();
gc_export_dot("graph_catch.dot");

gc_collect();
gc_export_dot("graph_collect.dot");

---

## How to View Graphs

Install Graphviz:

sudo apt install graphviz

Generate and view SVG:

dot -Tsvg graph_init.dot -o output.svg

xdg-open output.svg

🎨 Node Color Meaning
Color	Meaning
🟢 Green	Root / Anchor node
🔴 Red	Falling (GC candidate)
⚪ Gray	Normal node

---

## Benchmarks

The system includes:

fib → recursive allocation (deep tree structure)

sum → iterative allocation (large number of nodes)

ack → heavy recursion with complex structure

## Observations
sum → produces a large number of nodes (e.g., ~400)

fib / ack → often optimized → fewer nodes (sometimes very small graphs)

---

## Performance Insight

According to research, Arborescent GC is:

~4.5× slower than Mark-Sweep (median case)

However, it provides:

Immediate memory reclamation

Predictable and deterministic behavior

## Key Concept

The GC maintains a reference graph:

Nodes → objects

Edges → pointers

Reachability is maintained using a spanning forest.

When a reference is removed:

drop → marks potentially unreachable nodes
catch → restores reachable nodes
collect → deletes unreachable nodes

---

## Limitations
Single-threaded design

Higher overhead compared to traditional GC

Visualization may become large for complex graphs

---

## Future Improvements
Multithreading support

Hybrid GC (reference counting + graph-based)

Optimization of ranking and adoption strategies

Scalable and filtered visualization
