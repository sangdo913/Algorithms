#include "mm.h"      // prototypes of functions implemented in this file

#include "memlib.h"  // mem_sbrk -- to extend the heap
#include <string.h>  // memcpy -- to copy regions of memory

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

/**
 * A block header uses 4 bytes for:
 * - a block size, multiple of 8 (so, the last 3 bits are always 0's)
 * - an allocated bit (stored as LSB, since the last 3 bits are needed)
 *
 * A block footer has the same format.
 * Check Figure 9.48(a) in the textbook.
 */
typedef int BlockHeader;

/**
 * Read the size field from a block header (or footer).
 *
 * @param bp address of the block header (or footer)
 * @return size in bytes
 */
static int get_size(BlockHeader *bp) {
    return (*bp) & ~7;  // discard last 3 bits
}

/**
 * Read the allocated bit from a block header (or footer).
 *
 * @param bp address of the block header (or footer)
 * @return allocated bit (either 0 or 1)
 */
static int get_allocated(BlockHeader *bp) {
    return (*bp) & 1;   // get last bit
}

/**
 * Write the size and allocated bit of a given block inside its header.
 *
 * @param bp address of the block header
 * @param size size in bytes (must be a multiple of 8)
 * @param allocated either 0 or 1
 */
static void set_header(BlockHeader *bp, int size, int allocated) {
    *bp = size | allocated;
}

/**
 * Write the size and allocated bit of a given block inside its footer.
 *
 * @param bp address of the block header
 * @param size size in bytes (must be a multiple of 8)
 * @param allocated either 0 or 1
 */
static void set_footer(BlockHeader *bp, int size, int allocated) {
    char *footer_addr = (char *)bp + get_size(bp) - 4;
    // the footer has the same format as the header
    set_header((BlockHeader *)footer_addr, size, allocated);
}

/**
 * Find the payload starting address given the address of a block header.
 *
 * The block header is 4 bytes, so the payload starts after 4 bytes.
 *
 * @param bp address of the block header
 * @return address of the payload for this block
 */
static char *get_payload_addr(BlockHeader *bp) {
    return (char *)(bp + 1);
}

/**
 * Find the header address of the previous block on the heap.
 *
 * @param bp address of a block header
 * @return address of the header of the previous block
 */
static BlockHeader *get_prev(BlockHeader *bp) {
    // move back by 4 bytes to find the footer of the previous block
    BlockHeader *previous_footer = bp - 1;
    int previous_size = get_size(previous_footer);
    char *previous_addr = (char *)bp - previous_size;
    return (BlockHeader *)previous_addr;
}

/**
 * Find the header address of the next block on the heap.
 *
 * @param bp address of a block header
 * @return address of the header of the next block
 */
static BlockHeader *get_next(BlockHeader *bp) {
    int this_size = get_size(bp);
    char *next_addr = bp + this_size;  // TODO: to implement, look at get_prev
    return (BlockHeader *)next_addr;
}

/**
 * In addition to the block header with size/allocated bit, a free block has
 * pointers to the headers of the previous and next blocks on the free list.
 *
 * Pointers use 4 bytes because this project is compiled with -m32.
 * Check Figure 9.48(b) in the textbook.
 */
typedef struct {
    BlockHeader header;
    BlockHeader *prev_free;
    BlockHeader *next_free;
} FreeBlockHeader;

/**
 * Find the header address of the previous **free** block on the **free list**.
 *
 * @param bp address of a block header (it must be a free block)
 * @return address of the header of the previous free block on the list
 */
static BlockHeader *get_prev_free(BlockHeader *bp) {
    FreeBlockHeader *fp = (FreeBlockHeader *)bp;
    return fp->prev_free;
}

/**
 * Find the header address of the next **free** block on the **free list**.
 *
 * @param bp address of a block header (it must be a free block)
 * @return address of the header of the next free block on the list
 */
static BlockHeader *get_next_free(BlockHeader *bp) {
    FreeBlockHeader *fp = (FreeBlockHeader *)bp;
    return fp->next_free;
}

/**
 * Set the pointer to the previous **free** block.
 *
 * @param bp address of a free block header
 * @param prev address of the header of the previous free block (to be set)
 */
static void set_prev_free(BlockHeader *bp, BlockHeader *prev) {
    FreeBlockHeader *fp = (FreeBlockHeader *)bp;
    fp->prev_free = prev;
}

/**
 * Set the pointer to the next **free** block.
 *
 * @param bp address of a free block header
 * @param next address of the header of the next free block (to be set)
 */
static void set_next_free(BlockHeader *bp, BlockHeader *next) {
    FreeBlockHeader *fp = (FreeBlockHeader *)bp;
    fp->next_free = next;
}

/* Pointer to the header of the first block on the heap */
static BlockHeader *heap_blocks;

/* Pointers to the headers of the first and last blocks on the free list */
static BlockHeader *free_headp;
static BlockHeader *free_tailp;

/**
 * Add a block at the beginning of the free list.
 *
 * @param bp address of the header of the block to add
 */
static void free_list_prepend(BlockHeader *bp) {
    // TODO: implement
}

/**
 * Add a block at the end of the free list.
 *
 * @param bp address of the header of the block to add
 */
static void free_list_append(BlockHeader *bp) {
    // TODO: implement
}

/**
 * Remove a block from the free list.
 *
 * @param bp address of the header of the block to remove
 */
static void free_list_remove(BlockHeader *bp) {
    // TODO: implement
}

/**
 * Mark a block as free, coalesce with contiguous free blocks on the heap, add
 * the coalesced block to the free list.
 *
 * @param bp address of the block to mark as free
 * @return the address of the coalesced block
 */
static BlockHeader *free_coalesce(BlockHeader *bp) {

    // mark block as free
    int size = get_size(bp);
    set_header(bp, size, 0);
    set_footer(bp, size, 0);

    // check whether contiguous blocks are allocated
    int prev_alloc = get_allocated(get_prev(bp));
    int next_alloc = get_allocated(get_next(bp));

    if (prev_alloc && next_alloc) {
        // TODO: add bp to free list
        return bp;

    } else if (prev_alloc && !next_alloc) {
        // TODO: remove next block from free list
        // TODO: add bp to free list
        // TODO: coalesce with next block
        return bp;

    } else if (!prev_alloc && next_alloc) {
        // TODO: coalesce with previous block
        return get_prev(bp);

    } else {
        // TODO: remove next block from free list
        // TODO: coalesce with previous and next block
        return get_prev(bp);
    }
}

/**
 * Extend the heap with a free block of `size` bytes (multiple of 8).
 *
 * @param size number of bytes to allocate (a multiple of 8)
 * @return pointer to the header of the new free block
 */
static BlockHeader *extend_heap(int size) {

    // bp points to the beginning of the new block
    char *bp = mem_sbrk(size);
    if ((long)bp == -1)
        return NULL;

    // write header over old epilogue, then the footer
    BlockHeader *old_epilogue = (BlockHeader *)bp - 1;
    set_header(old_epilogue, size, 0);
    set_footer(old_epilogue, size, 0);

    // write new epilogue
    set_header(get_next(old_epilogue), 0, 1);

    // merge new block with previous one if possible
    return free_coalesce(old_epilogue);
}

int mm_init(void) {

    // init list of free blocks
    free_headp = NULL;
    free_tailp = NULL;

    // create empty heap of 4 x 4-byte words
    char *new_region = mem_sbrk(16);
    if ((long)new_region == -1)
        return -1;

    heap_blocks = (BlockHeader *)new_region;
    set_header(heap_blocks, 0, 0);      // skip 4 bytes for alignment
    set_header(heap_blocks + 1, 8, 1);  // allocate a block of 8 bytes as prologue
    set_footer(heap_blocks + 1, 8, 1);
    set_header(heap_blocks + 3, 0, 1);  // epilogue
    heap_blocks += 1;                   // point to the prologue header

    // TODO: extend heap with an initial heap size
    return 0;
}

void mm_free(void *bp) {
    // TODO: move back 4 bytes to find the block header, then free block
}

/**
 * Find a free block with size greater or equal to `size`.
 *
 * @param size minimum size of the free block
 * @return pointer to the header of a free block or `NULL` if free blocks are
 *         all smaller than `size`.
 */
static BlockHeader *find_fit(int size) {
    // TODO: implement
    return NULL;
}

/**
 * Allocate a block of `size` bytes inside the given free block `bp`.
 *
 * @param bp pointer to the header of a free block of at least `size` bytes
 * @param size bytes to assign as an allocated block (multiple of 8)
 * @return pointer to the header of the allocated block
 */
static BlockHeader *place(BlockHeader *bp, int size) {
    // TODO: if current size is greater, use part and add rest to free list
    // TODO: return pointer to header of allocated block
    return NULL;
}

/**
 * Compute the required block size (including space for header/footer) from the
 * requested payload size.
 *
 * @param payload_size requested payload size
 * @return a block size including header/footer that is a multiple of 8
 */
static int required_block_size(int payload_size) {
    payload_size += 8;                    // add 8 for for header/footer
    return ((payload_size + 7) / 8) * 8;  // round up to multiple of 8
}

void *mm_malloc(size_t size) {
    // ignore spurious requests
    if (size == 0)
        return NULL;

    int required_size = required_block_size(size);

    // TODO: find a free block or extend heap
    // TODO: allocate and return pointer to payload
    return NULL;
}

void *mm_realloc(void *ptr, size_t size) {

    if (ptr == NULL) {
        // equivalent to malloc
        return mm_malloc(size);

    } else if (size == 0) {
        // equivalent to free
        mm_free(ptr);
        return NULL;

    } else {
        // TODO: reallocate, reusing current block if possible
        // TODO: copy data over new block with memcpy
        // TODO: return pointer to payload of new block

        // TODO: remove this naive implementation
        void *new_ptr = mm_malloc(size);
        memcpy(new_ptr, ptr, MIN(size, (unsigned)get_size(ptr) - 8));
        mm_free(ptr);
        return new_ptr;
    }
}
