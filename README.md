This project implements a custom Arborescent Garbage Collector (GC) in C, inspired by dynamic graph-based memory management techniques.

Unlike traditional collectors (e.g., Mark-and-Sweep), this GC:

Tracks object relationships as a reference graph
Maintains a spanning forest
Performs immediate cycle collection
Supports phase-wise visualization using Graphviz (DOT)

The system also includes benchmark programs (fib, sum, ack) to evaluate GC behavior and performance.

⚙️ Features

✅ Custom memory management (no malloc/free directly)
✅ Graph-based reachability tracking
✅ Immediate garbage collection (no deferred cycles)
✅ GC phases:

init
drop
catch
collect

✅ DOT visualization export
✅ Benchmark integration:

Fibonacci
Summation
Ackermann
🧩 Project Structure
GC-Arborescent/
│── main.c        # Entry point
│── gc.c          # Garbage collector implementation
│── gc.h
│── bench.c       # Benchmark logic (fib, sum, ack)
│── bench.h
│── CMakeLists.txt
🚀 How to Build
mkdir build
cd build
cmake ..
make

or (CLion auto-build works too)

▶️ How to Run
./GC_Arborescent
📊 Visualization (Graphviz)

This project exports GC state as DOT/SVG files.

Example code:
gc_init();
gc_export_dot("graph_init.svg");

gc_drop();
gc_export_dot("graph_drop.svg");

gc_catch();
gc_export_dot("graph_catch.svg");

gc_collect();
gc_export_dot("graph_collect.svg");
🖼️ How to View Graph

Install Graphviz:

sudo apt install graphviz

Generate image:

dot -Tsvg graph_init.svg -o output.svg
xdg-open output.svg
🎨 Node Color Meaning
Color	Meaning
🟢 Green	Root / Anchor node
🔴 Red	Falling (candidate GC)
⚪ Gray	Normal node
🧪 Benchmarks

The system includes:

fib → recursive allocation (deep tree)
sum → iterative allocation (many nodes)
ack → heavy recursion

📌 Observation:

sum → large node count (e.g., 400)
fib/ack → often optimized → fewer nodes (sometimes 1)
📈 Performance Insight

According to research, Arborescent GC:

~4.5× slower than Mark-Sweep (median)
but provides:
immediate memory reclamation
predictable behavior
🔬 Key Concept

The GC maintains a reference graph:

Nodes = objects
Edges = pointers

Reachability is tracked via a spanning forest

When an edge is removed:

drop → mark potentially unreachable nodes
catch → recover reachable ones
collect → delete unreachable nodes
⚠️ Limitations
Single-threaded design
Higher overhead than traditional GC
Visualization can become large (graph scaling issues)
🔮 Future Improvements
Multithreading support
Hybrid GC (ref-count + graph)
Optimization of ranking & adoption
Better visualization filtering
👩‍💻 Author

Mahbuba Habib
CSE Student | Systems & Research Enthusiast
