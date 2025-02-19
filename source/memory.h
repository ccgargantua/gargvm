#ifndef MEMORY_H
#define MEMORY_H


#include <stdbool.h>
#include <assert.h>
#include <stdint.h>


#define MEMORY_ERROR_CODE_LOCATION 0


typedef struct
{
    uint32_t *data;
    uint32_t size;
} MemoryModule;


typedef enum
{
    MEMORY_NO_ERROR,
    MEMORY_OUT_OF_BOUNDS,
    MEMORY_RESERVED_SPACE,
} MemoryError;


uint32_t fetch(MemoryModule *module, uint32_t address);
void store(MemoryModule *module, uint32_t address, uint32_t value);

static inline void memory_clear_error(MemoryModule *module)
{
    assert(module);
    assert(module->data);
    module->data[MEMORY_ERROR_CODE_LOCATION] = MEMORY_NO_ERROR;
}

static inline bool memory_has_error(MemoryModule *module)
{
    assert(module);
    assert(module->data);
    return module->data[MEMORY_ERROR_CODE_LOCATION] != MEMORY_NO_ERROR;
}

static inline MemoryError memory_error(MemoryModule *module)
{
    assert(module);
    assert(module->data);
    return module->data[MEMORY_ERROR_CODE_LOCATION];
}

#endif