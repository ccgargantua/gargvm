#include "memory.h"


#include <stdio.h>

uint32_t fetch(MemoryModule* module, uint32_t address)
{
    assert(module);
    assert(module->data);
    if (address >= module->size)
        module->data[MEMORY_ERROR_CODE_LOCATION] = OUT_OF_BOUNDS;
    else if (address == MEMORY_ERROR_CODE_LOCATION)
        module->data[MEMORY_ERROR_CODE_LOCATION] = RESERVED_SPACE;

    if (module->data[MEMORY_ERROR_CODE_LOCATION] != NO_ERROR)
        return module->data[MEMORY_ERROR_CODE_LOCATION];

    return module->data[address];
}
void store(MemoryModule *module, uint32_t address, uint32_t value)
{
    assert(module);
    assert(module->data);
    if (address >= module->size)
        module->data[MEMORY_ERROR_CODE_LOCATION] = OUT_OF_BOUNDS;
    else if (address == MEMORY_ERROR_CODE_LOCATION)
        module->data[MEMORY_ERROR_CODE_LOCATION] = RESERVED_SPACE;
    module->data[address] = value;
}