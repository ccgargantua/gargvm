#include "garena.h"


#include <stdlib.h>
#include <stdalign.h>
#include <stddef.h>
#include <assert.h>


// Primarily used for assertions of bounds
static inline ptrdiff_t ptr_diff(void *p1, void *p2)
{
    return (char *)p1 - (char *)p2;
}


// Internal allocation/deallocation
static void * (*alloc)(size_t size) = malloc;
static void (*dealloc)(void *)      = free;


void garena_set_alloc( void * (*allocator)(size_t size) )
{
    assert(allocator);
    alloc = allocator;
}

void garena_set_dealloc( void (*deallocator)(void *))
{
    assert(deallocator);
    dealloc = deallocator;
}


// this should typically be platform's word alignment
static unsigned int default_alignment = alignof(max_align_t);

void garena_set_default_alignment(unsigned int align)
{
    assert(
        align
        && (align & (align - 1)) == 0 );
    default_alignment = align;
}


Arena *arena_create(size_t size)
{
    assert(size > 0);

    Arena *arena = alloc(sizeof(Arena));
    assert(arena);

    arena->begin = alloc(size);
    assert(arena->begin);

    arena->end = arena->begin + size;

    return arena;
}


void *arena_alloc(Arena *arena, size_t size)
{
    return arena_alloc_aligned(arena, size, default_alignment);
}


void *arena_alloc_aligned(Arena *arena, size_t size, unsigned int align)
{
    assert(arena);
    assert(
        align
        && (align & (align - 1)) == 0 );

    ptrdiff_t available = ptr_diff(arena->end, arena->begin);
    assert(available >= 0);

    ptrdiff_t padding   = (ptrdiff_t)arena->end & (align - 1);

    assert(size <= PTRDIFF_MAX);
    assert((ptrdiff_t)size <= available - padding);

    // Now allocate it from the arena
    arena->end -= (ptrdiff_t)size + padding;
    return arena->end;
}


void arena_destroy(Arena *arena)
{
    assert(arena);
    dealloc(arena->begin);
    dealloc(arena);
}
