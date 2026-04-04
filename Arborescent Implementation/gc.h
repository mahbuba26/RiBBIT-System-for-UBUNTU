#ifndef GC_H
#define GC_H

typedef struct Node {
    int id;
    int rank;
    int falling;
    int anchor;
    struct Node* parent;
} Node;

void gc_init(void);
void gc_drop(void);
void gc_catch(void);
void gc_collect(void);
void gc_print_stats(void);
void gc_allocate(void);
//void gc_export_dot(const char* filename);
void gc_export_dot(const char* filename, int sample_count);
#endif