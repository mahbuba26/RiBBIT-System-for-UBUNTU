#include "gc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NODES 200000

static Node nodes[MAX_NODES];
static int node_count = 0;

static int allocation_count = 0;
static int threshold = 50000;

void gc_init(void) {
    node_count = 0;
    allocation_count = 0;
    srand(time(NULL));
    printf("[GC] init\n");
}

// ---------------- GC ALLOCATION ----------------
void gc_allocate(void) {
    if (node_count >= MAX_NODES) return;

    Node* n = &nodes[node_count];
    n->id = node_count;
    n->rank = rand() % 10;
    n->falling = 0;
    n->anchor = 0;

    // Random parent for realistic edges
    if (node_count > 0 && (rand() % 2 == 0)) {
        int p = rand() % node_count;
        n->parent = &nodes[p];
    } else {
        n->parent = NULL; // root node
    }

    node_count++;
    allocation_count++;

    if (allocation_count >= threshold) {
        printf("\n[GC Triggered at %d allocations]\n", allocation_count);

        gc_drop();
        gc_catch();
        gc_collect();

        allocation_count = 0;
    }
}

// ---------------- GC PHASES ----------------
void gc_drop(void) {
    //printf("[GC] Drop phase\n");
    printf("\n[GC] ================ Drop Phase ================");
    for (int i = 0; i < node_count; i++) {
        // Falling decision
        if (nodes[i].rank < 3)
            nodes[i].falling = 1;

        // Adoption optimization
        if (nodes[i].falling && nodes[i].parent != NULL) {
            if (nodes[i].parent->rank < nodes[i].rank) {
                nodes[i].falling = 0; // adoption
            }
        }
    }
}

void gc_catch(void) {
    //printf("[GC] Catch phase\n");
    printf("\n[GC] ================ Catch Phase ================");
    for (int i = 0; i < node_count; i++) {
        // Anchor nodes
        if (!nodes[i].falling && nodes[i].rank > 7)
            nodes[i].anchor = 1;

        // Caught nodes
        if (nodes[i].falling && nodes[i].anchor)
            nodes[i].falling = 0;

        // Reranking optimization
        if (nodes[i].anchor && nodes[i].rank > 5)
            nodes[i].rank--;
    }
}

void gc_collect(void) {
    //printf("[GC] Collect phase\n");
    printf("\n[GC] ================ Collect Phase ================");
    for (int i = 0; i < node_count; i++) {
        if (nodes[i].falling)
            nodes[i].parent = NULL; // simulate deletion
    }
}

// ---------------- STATS ----------------
void gc_print_stats(void) {
    int falling = 0, edges = 0;

    for (int i = 0; i < node_count; i++) {
        if (nodes[i].falling) falling++;
        if (nodes[i].parent != NULL) edges++;
    }

    printf("\n[GC STATS]\n");
    printf("Total nodes: %d\n", node_count);
    printf("Edges: %d\n", edges);
    printf("Falling nodes: %d\n", falling);
}

// ---------------- DOT EXPORT ----------------
/*void gc_export_dot(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "digraph GC {\n");

    for (int i = 0; i < node_count; i++) {
        // color based on status
        if (nodes[i].falling)
            fprintf(f, "node%d [label=\"%d\" color=red];\n", nodes[i].id, nodes[i].rank);
        else if (nodes[i].anchor)
            fprintf(f, "node%d [label=\"%d\" color=green];\n", nodes[i].id, nodes[i].rank);
        else
            fprintf(f, "node%d [label=\"%d\"];\n", nodes[i].id, nodes[i].rank);

        if (nodes[i].parent != NULL)
            fprintf(f, "node%d -> node%d;\n", nodes[i].parent->id, nodes[i].id);
    }

    fprintf(f, "}\n");
    fclose(f);
    printf("[GC] DOT exported to %s\n", filename);
}



void gc_export_dot(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "digraph GC {\n");
    fprintf(f, "  node [shape=circle, style=filled, fontcolor=white];\n");

    for (int i = 0; i < node_count; i++) {
        const char* color = "lightgray";  // normal
        if (nodes[i].falling) color = "red";
        else if (nodes[i].anchor) color = "green";

        fprintf(f, "  N%d [label=\"%d\", fillcolor=%s];\n",
                nodes[i].id, nodes[i].rank, color);
    }

    for (int i = 0; i < node_count; i++) {
        if (nodes[i].parent != NULL) {
            fprintf(f, "  N%d -> N%d;\n", nodes[i].id, nodes[i].parent->id);
        }
    }

    fprintf(f, "}\n");
    fclose(f);

    printf("[GC] DOT exported to %s\n", filename);
}
*/

void gc_export_dot(const char* filename, int sample_count) {
    FILE* f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "digraph GC {\n");
    fprintf(f, "  node [shape=circle, style=filled, fontcolor=white];\n");

    // sample_count er cheye beshi node thakle limit kore dekhao
    int count = (sample_count < node_count) ? sample_count : node_count;

    for (int i = 0; i < count; i++) {
        const char* color = "lightgray";  // normal
        if (nodes[i].falling) color = "red";
        else if (nodes[i].anchor) color = "green";

        fprintf(f, "  N%d [label=\"%d\", fillcolor=%s];\n",
                nodes[i].id, nodes[i].rank, color);
    }

    for (int i = 0; i < count; i++) {
        if (nodes[i].parent != NULL) {
            fprintf(f, "  N%d -> N%d;\n", nodes[i].id, nodes[i].parent->id);
        }
    }

    fprintf(f, "}\n");
    fclose(f);

    printf("[GC] DOT exported to %s (showing %d nodes)\n", filename, count);
}