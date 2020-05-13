#ifndef __MM_H__
#define __MM_H__

#include <stddef.h>  // size_t

int   mm_init(void);
void *mm_malloc(size_t size);
void *mm_realloc(void *ptr, size_t size);
void  mm_free(void *ptr);

#endif /* __MM_H__ */
