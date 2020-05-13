#ifndef __MEMLIB_H__
#define __MEMLIB_H__

#include <stddef.h>  // size_t

void mem_init(void);
void mem_deinit(void);
void *mem_sbrk(int incr);
void mem_reset_brk(void);
void *mem_heap_lo(void);
void *mem_heap_hi(void);
size_t mem_heapsize(void);
size_t mem_pagesize(void);

#endif /* __MEMLIB_H__ */
