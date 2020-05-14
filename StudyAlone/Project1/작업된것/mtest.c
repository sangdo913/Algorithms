#define _POSIX_C_SOURCE 200809L

#include "mm.h"
#include "memlib.h"

#include <stdio.h>   // printf, fprintf, sprintf, stderr, EOF, FILE
#include <stdlib.h>  // exit, free, malloc, realloc, free, atoi
#include <string.h>  // memset, strdup (needs _POSIX_C_SOURCE), strncmp
#include <assert.h>  // assert
#include <float.h>   // DBL_MAX
#include <time.h>    // clock_gettime, CLOCK_MONOTONIC
#include <getopt.h>  // getopt, optarg
#include <math.h>    // fmin

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/* error tracking for all traces */
static int errors = 0;
static void trace_error(int tracenum, int opnum, char *msg) {
    errors++;
    printf("ERROR [trace %d, line %d]: %s\n", tracenum, opnum+3, msg);  // 2 header lines
}

/* recorded list of allocated blocks */
typedef struct BlockItem {
    char *lo;
    char *hi;
    struct BlockItem *next;
} BlockItem;

static int add_block(BlockItem **blocks, char *lo, int size, int tracenum, int opnum) {
    char msg[1024];

    if ((unsigned int)lo % 8 != 0) {
        sprintf(msg, "Payload address (%p) not aligned to 8 bytes", lo);
        trace_error(tracenum, opnum, msg);
        return 0;
    }

    assert(size > 0);
    char *hi = lo + size - 1;
    if ((lo < (char *)mem_heap_lo()) || (lo > (char *)mem_heap_hi()) ||
        (hi < (char *)mem_heap_lo()) || (hi > (char *)mem_heap_hi())) {
        sprintf(msg, "Payload (%p:%p) lies outside heap (%p:%p)", lo, hi, mem_heap_lo(), mem_heap_hi());
        trace_error(tracenum, opnum, msg);
        return 0;
    }

    for (BlockItem *p = *blocks;  p != NULL;  p = p->next) {
        if ((lo >= p->lo && lo <= p-> hi) || (hi >= p->lo && hi <= p->hi)) {
            sprintf(msg, "Payload (%p:%p) overlaps another payload (%p:%p)\n", lo, hi, p->lo, p->hi);
            trace_error(tracenum, opnum, msg);
            return 0;
        }
    }

    // add to head of block list
    BlockItem *newBlock = malloc(sizeof(BlockItem));
    if (newBlock == NULL) {
        perror("malloc error in add_block");
        exit(1);
    }
    newBlock->next = *blocks;
    newBlock->lo = lo;
    newBlock->hi = hi;
    *blocks = newBlock;
    return 1;
}

static void remove_block(BlockItem **blocks, char *lo) {
    BlockItem **prev_next_ptr = blocks;
    for (BlockItem *p = *blocks;  p != NULL; p = p->next) {
        if (p->lo == lo) {
            *prev_next_ptr = p->next;
            free(p);
            return;
        }
        prev_next_ptr = &(p->next);
    }
}

static void free_blocks(BlockItem **blocks) {
    BlockItem *p = *blocks;
    while (p != NULL) {
        BlockItem *next = p->next;
        free(p);
        p = next;
    }
    *blocks = NULL;
}

/* trace reading */
typedef struct {
    enum {ALLOC, FREE, REALLOC} type;
    int index;
    int size;
} TraceOp;

typedef struct {
    int num_ids;
    int num_ops;
    TraceOp *ops;
    char **blocks;
    int *block_sizes;
} Trace;

static void free_trace(Trace *trace) {
    free(trace->ops);
    free(trace->blocks);
    free(trace->block_sizes);
    free(trace);
}

static Trace *read_trace(char *filename) {
    FILE *tracefile = fopen(filename, "r");
    if (tracefile == NULL) {
        char msg[1024];
        sprintf(msg, "Could not open %s in read_trace", filename);
        perror(msg);
        exit(1);
    }

    Trace *trace = malloc(sizeof(Trace));
    if (trace == NULL) {
        perror("malloc 1 failed in read_trace");
        exit(1);
    }

    fscanf(tracefile, "%d", &(trace->num_ids));
    if ((trace->blocks = malloc(trace->num_ids * sizeof(char *))) == NULL) {
        perror("malloc 2 failed in read_trace");
        exit(1);
    } else if ((trace->block_sizes = malloc(trace->num_ids * sizeof(int))) == NULL) {
        perror("malloc 3 failed in read_trace");
        exit(1);
    }

    fscanf(tracefile, "%d", &(trace->num_ops));
    if ((trace->ops = malloc(trace->num_ops * sizeof(TraceOp))) == NULL) {
        perror("malloc 4 failed in read_trace");
        exit(1);
    }

    int op_index = 0;
    int max_block_index = 0;
    char op_type[1024];
    while (fscanf(tracefile, "%s", op_type) != EOF) {
        int block_index;
        int block_size;
        switch(op_type[0]) {
            case 'a':
            case 'r':
                trace->ops[op_index].type = (op_type[0] == 'a') ? ALLOC : REALLOC;
                fscanf(tracefile, "%u %u", &block_index, &block_size);
                trace->ops[op_index].index = block_index;
                trace->ops[op_index].size = block_size;
                max_block_index = (block_index > max_block_index) ? block_index : max_block_index;
                break;
            case 'f':
                trace->ops[op_index].type = FREE;
                trace->ops[op_index].size = 0;
                fscanf(tracefile, "%ud", &block_index);
                trace->ops[op_index].index = block_index;
                break;
            default:
                printf("Unknown op type (%s) in %s\n", op_type, filename);
                exit(1);
        }
        op_index++;
    }

    assert(max_block_index == trace->num_ids - 1);
    assert(trace->num_ops == op_index);
    fclose(tracefile);
    return trace;
}

/* solution testing */
typedef void *(*malloc_f)(size_t size);
typedef void *(*realloc_f)(void *ptr, size_t size);
typedef void  (*free_f)(void *ptr);

static int eval_valid(malloc_f test_malloc, realloc_f test_realloc, free_f test_free, Trace *trace, int tracenum) {

    int max_total_size = 0;
    int total_size = 0;
    BlockItem *blocks = NULL;

    for (int i = 0;  i < trace->num_ops;  i++) {
        int index = trace->ops[i].index;
        int size = trace->ops[i].size;
        switch (trace->ops[i].type) {
            case ALLOC: {
                char *p = test_malloc(size);
                if (p == NULL) {
                    trace_error(tracenum, i, "mm_malloc failed.");
                    return 0;
                }

                if (add_block(&blocks, p, size, tracenum, i) == 0)
                    return 0;

                memset(p, index & 0xFF, size);  // for realloc checks
                trace->blocks[index] = p;
                trace->block_sizes[index] = size;
                total_size += size;
                max_total_size = MAX(total_size, max_total_size);
                break;
            }

            case REALLOC: {
                char *oldp = trace->blocks[index];
                char *newp = test_realloc(oldp, size);
                if (newp == NULL) {
                    trace_error(tracenum, i, "mm_realloc failed.");
                    return 0;
                }

                remove_block(&blocks, oldp);
                if (add_block(&blocks, newp, size, tracenum, i) == 0)
                    return 0;

                int old_size = trace->block_sizes[index];
                int preserved_size = MIN(old_size, size);
                for (int j = 0; j < preserved_size; j++) {
                    if (newp[j] != (index & 0xFF)) {
                        trace_error(tracenum, i, "mm_realloc did not preserve data from old block");
                        return 0;
                    }
                }
                memset(newp, index & 0xFF, size); // for new bytes

                trace->blocks[index] = newp;
                trace->block_sizes[index] = size;

                total_size += size - old_size;
                max_total_size = MAX(total_size, max_total_size);
                break;
            }

            case FREE: {
                char *p = trace->blocks[index];
                remove_block(&blocks, p);
                test_free(p);
                total_size -= trace->block_sizes[index];
                break;
            }

            default:
                printf("Nonexistent request type in eval_mm_valid\n");
                exit(1);
        }
    }

    free_blocks(&blocks);
    return max_total_size;
}

static void replay_trace(malloc_f test_malloc, realloc_f test_realloc,
        free_f test_free, Trace *trace) {

    for (int i = 0;  i < trace->num_ops;  i++) {
        switch (trace->ops[i].type) {
            case ALLOC: {
                int index = trace->ops[i].index;
                int size = trace->ops[i].size;
                char *p = test_malloc(size);
                if (p == NULL) {
                    printf("mm_malloc error in eval_mm_speed\n");
                    exit(1);
                }
                trace->blocks[index] = p;
                break;
            }

            case REALLOC: {
                int index = trace->ops[i].index;
                int newsize = trace->ops[i].size;
                char *oldp = trace->blocks[index];
                char *newp = test_realloc(oldp, newsize);
                if (newp == NULL) {
                    printf("test_realloc error in eval_mm_speed\n");
                    exit(1);
                }
                trace->blocks[index] = newp;
                break;
            }

            case FREE: {
                int index = trace->ops[i].index;
                char *block = trace->blocks[index];
                test_free(block);
                break;
            }

            default:
                printf("Nonexistent request type in eval_mm_valid\n");
                exit(1);
        }
    }
}

static double eval_speed(malloc_f test_malloc, realloc_f test_realloc,
        free_f test_free, Trace *trace, int repeat_min, int num_executions) {
    struct timespec t0;
    struct timespec t1;
    double min = DBL_MAX;
    for (int i = 0; i < repeat_min; i++) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (int j = 0; j < num_executions; j++) {
            replay_trace(test_malloc, test_realloc, test_free, trace);
        }
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double elapsed = (t1.tv_sec - t0.tv_sec)*1000.0 + (t1.tv_nsec - t0.tv_nsec)/1000000.0;
        min = fmin(min, elapsed/num_executions);
   }
   return min;
}

/* output printing */
typedef struct {
    int valid;
    double util;
    double ops;
    double ms;
} TraceStats;

typedef struct {
    TraceStats *traces;
    int num_traces;
    double mean_util;
    double total_ops;
    double total_ms;
    double mean_tput;
} Stats;

static void print_results(char* name, Stats *stats) {
    printf("Results for %s malloc:\n", name);
    printf("%5s%7s %5s%8s%10s%8s\n", "trace", " valid", "util", "ops", "ms", "kops/s");
    for (int i = 0; i < stats->num_traces; i++) {
        if (stats->traces[i].valid) {
            printf("%2d%10s%5.0f%%%8.0f%10.2f%8.0f\n",    i, "yes",
                stats->traces[i].util*100.0,
                stats->traces[i].ops,  stats->traces[i].ms,
                stats->traces[i].ops / stats->traces[i].ms);
        } else {
            printf("%2d%10s%6s%8s%10s%8s\n", i, "no", "-", "-", "-", "-");
        }
    }
    if (errors == 0) {
        printf("%12s%5.0f%%%8.0f%10.2f%8.0f\n", "Total       ",
            stats->mean_util*100.0, stats->total_ops, stats->total_ms, stats->mean_tput);
    } else {
        printf("%12s%6s%8s%10s%8s\n", "Total       ", "-", "-", "-", "-");
    }
    printf("\n");
}

static Stats *eval(char *name, malloc_f test_malloc, realloc_f test_realloc, free_f test_free,
        char *traces[], int traces_len, int repeat_min) {

    Stats *stats = calloc(1, sizeof(Stats));
    if (stats == NULL) {
        perror("stats allocation1 failed");
        exit(1);
    }

    stats->traces = calloc(traces_len, sizeof(TraceStats));
    if (stats->traces == NULL) {
        perror("stats allocation2 failed");
        exit(1);
    }

    stats->mean_util = 0.0;
    stats->total_ops = 0.0;
    stats->total_ms = 0.0;
    stats->num_traces = traces_len;
    for (int i = 0; i < traces_len; i++) {
        if (strncmp(name, "mm", 2) == 0) {
            if (i == 0) {
                mem_init();
            }
            mem_reset_brk();
            if (mm_init() < 0) {
                trace_error(i, 0, "mm_init failed.");
                stats->traces[i].valid = 0;
                continue;
            }
        }

        Trace *trace = read_trace(traces[i]);
        stats->traces[i].ops = trace->num_ops;
        stats->total_ops += stats->traces[i].ops;

        int max_total_size = eval_valid(test_malloc, test_realloc, test_free, trace, i);
        stats->traces[i].valid = max_total_size > 0;

        if (stats->traces[i].valid) {
            if (strncmp(name, "mm", 2) == 0) {
                stats->traces[i].util = ((double)max_total_size / mem_heapsize());
                stats->mean_util += stats->traces[i].util;
                mem_reset_brk();
                if (mm_init() < 0) {
                    printf("mm_init failed in eval_speed\n");
                    exit(1);
                }
            }
            stats->traces[i].ms = eval_speed(test_malloc, test_realloc, test_free, trace, repeat_min, 10);
            stats->total_ms += stats->traces[i].ms;
        }

        free_trace(trace);
    }

    stats->mean_util /= traces_len;
    stats->mean_tput = stats->total_ops / stats->total_ms;
    print_results(name, stats);
    return stats;
}

static void usage(void) {
    fprintf(stderr, "Usage: mtest [-h] [-r <reps>] [-f <file>]\nwhere\n");
    fprintf(stderr, "-h         Print program usage.\n");
    fprintf(stderr, "-r <reps>  Repeat measurements <reps> times. (default: 3)\n");
    fprintf(stderr, "-t <trace> Use only <trace> as the trace file.\n");
}

int main(int argc, char **argv) {
    int repeat_min = 3;
    int traces_len = 11;
    char *traces[] = {
        "./traces/amptjp-bal.rep",
        "./traces/cccp-bal.rep",
        "./traces/cp-decl-bal.rep",
        "./traces/expr-bal.rep",
        "./traces/coalescing-bal.rep",
        "./traces/random-bal.rep",
        "./traces/random2-bal.rep",
        "./traces/binary-bal.rep",
        "./traces/binary2-bal.rep",
        "./traces/realloc-bal.rep",
        "./traces/realloc2-bal.rep"
    };

    char c;
    while ((c = getopt(argc, argv, "f:r:h")) != EOF) {
        switch (c) {
            case 'f':
                traces[0] = strdup(optarg);
                traces_len = 1;
                break;
            case 'r':
                repeat_min = atoi(optarg);
                break;
            case 'h':
                usage();
                exit(0);
            default:
                usage();
                exit(1);
        }
    }

    errors = 0;
    Stats *libc_stats = eval("libc", malloc, realloc, free, traces, traces_len, repeat_min);
    errors = 0;
    Stats *mm_stats = eval("mm", mm_malloc, mm_realloc, mm_free, traces, traces_len, repeat_min);

    if (errors != 0) {
        printf("Terminated with %d errors\n", errors);
    } else {
        double util_weight = 0.6;
        double p1 = util_weight * mm_stats->mean_util / 0.95;
        double p2 = (1.0 - util_weight) * fmin(1.0, mm_stats->mean_tput / (0.9 * libc_stats->mean_tput));
        printf("PERFORMANCE INDEX: %.0f (util) + %.0f (thru) = %.0f/100\n", p1*100, p2*100, (p1 + p2)*100.0);
    }

    free(libc_stats);
    free(mm_stats);
    exit(0);
}
