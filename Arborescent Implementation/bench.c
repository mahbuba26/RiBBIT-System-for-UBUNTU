#include <stdio.h>
#include <time.h>
#include "bench.h"
#include "gc.h"

static long fib(int n) {
    //gc_allocate();  // optional if you want per-recursive node
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

static long calc(int i, long sum) {
    if (i < 1) return sum;
    return calc(i - 1, sum + i);
}

static long ack(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ack(m - 1, 1);
    return ack(m - 1, ack(m, n - 1));
}

#define PRINT_HEADER(title) \
printf("\n================ %s =================\n", title);

void run_fib_benchmark(void) {
    PRINT_HEADER("Fib Benchmark");
    clock_t start = clock();

    long r = 0;
    for (int i = 0; i < 1; i++) {
        r = fib(35);
        gc_allocate();
    }

    clock_t end = clock();
    double t = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[BENCH] fib result: %ld\n", r);
    printf("[TIME] fib: %.4f sec\n", t);

    gc_print_stats();
}

void run_sum_benchmark(void) {
    PRINT_HEADER("Sum Benchmark");
    clock_t start = clock();

    long r = 0;
    for (int i = 0; i < 2500; i++) {
        r = calc(10000, 0);
        gc_allocate();
    }

    clock_t end = clock();
    double t = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[BENCH] sum result: %ld\n", r);
    printf("[TIME] sum: %.4f sec\n", t);

    gc_print_stats();
}

void run_ack_benchmark(void) {
    PRINT_HEADER("Ack Benchmark");
    clock_t start = clock();

    long r = 0;
    for (int i = 0; i < 2; i++) {
        r = ack(3, 9);
        gc_allocate();
    }

    clock_t end = clock();
    double t = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[BENCH] ack result: %ld\n", r);
    printf("[TIME] ack: %.4f sec\n", t);

    gc_print_stats();
}