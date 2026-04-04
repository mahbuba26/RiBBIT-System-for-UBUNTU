/*#include "gc.h"
#include "bench.h"

int main(void) {
    gc_init();

    run_fib_benchmark();
    run_sum_benchmark();
    run_ack_benchmark();

    gc_drop();
    gc_catch();
    gc_collect();
    gc_print_stats();

    // Export DOT for visualization
    gc_export_dot("graph.dot");

    return 0;
}*/

#include "gc.h"
#include "bench.h"
#include <time.h>
#include <stdio.h>

int main(void) {
    clock_t start, end;
    double time_taken;

    // ----------------- Fib -----------------
    gc_init();
    gc_export_dot("graph_fib_init.svg",22);

    start = clock();
    run_fib_benchmark();
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[TIME] fib: %.4f sec\n", time_taken);

    gc_drop();
    gc_export_dot("graph_fib_drop.svg", 22);
    gc_catch();
    gc_export_dot("graph_fib_catch.svg", 22);
    gc_collect();
    gc_export_dot("graph_fib_collect.svg", 22);
    gc_print_stats();

    // ----------------- Sum -----------------
    gc_init();
    gc_export_dot("graph_sum_init.svg", 22);

    start = clock();
    run_sum_benchmark();
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[TIME] sum: %.4f sec\n", time_taken);

    gc_drop();
    gc_export_dot("graph_sum_drop.svg", 22);
    gc_catch();
    gc_export_dot("graph_sum_catch.svg", 22);
    gc_collect();
    gc_export_dot("graph_sum_collect.svg", 22);
    gc_print_stats();

    // ----------------- Ack -----------------
    gc_init();
    gc_export_dot("graph_ack_init.svg", 22);

    start = clock();
    run_ack_benchmark();
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[TIME] ack: %.4f sec\n", time_taken);

    gc_drop();
    gc_export_dot("graph_ack_drop.svg", 22);
    gc_catch();
    gc_export_dot("graph_ack_catch.svg", 22);
    gc_collect();
    gc_export_dot("graph_ack_collect.svg", 22);
    gc_print_stats();

    return 0;
}