#include "memlib.h"

#include <stdio.h>   // fprintf
#include <stdlib.h>  // malloc, free, exit
#include <unistd.h>  // _SC_PAGESIZE
#include <errno.h>   // ENOMEM

#define MAX_HEAP (40*(1<<20))  /* 40 MB */

static char *mem_start_brk;
static char *mem_brk;
static char *mem_max_addr;

void mem_init(void) {
    if ((mem_start_brk = (char *)malloc(MAX_HEAP)) == NULL) {
        fprintf(stderr, "mem_init_vm: malloc error\n");
        exit(1);
    }

    mem_max_addr = mem_start_brk + MAX_HEAP;
    mem_brk = mem_start_brk;
}

void mem_deinit(void) {
    free(mem_start_brk);
}

void mem_reset_brk() {
    mem_brk = mem_start_brk;
}

void *mem_sbrk(int incr) {
    char *old_brk = mem_brk;
    if (incr < 0 || (mem_brk + incr) > mem_max_addr) {
        errno = ENOMEM;
        fprintf(stderr, "ERROR: mem_sbrk failed. Ran out of memory...\n");
        return (void *)-1;
    }

    mem_brk += incr;
    return (void *)old_brk;
}

void *mem_heap_lo() {
    return (void *)mem_start_brk;  // first heap byte
}

void *mem_heap_hi() {
    return (void *)(mem_brk - 1);  // last heap byte
}

size_t mem_heapsize() {
    return (size_t)(mem_brk - mem_start_brk);
}

size_t mem_pagesize() {
    return (size_t)sysconf(_SC_PAGESIZE);
}
