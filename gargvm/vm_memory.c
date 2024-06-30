#include <stdlib.h>

#include "vm_assert.h"
#include "vm_memory.h"


struct MemoryModule
{
    Byte *data, *end;
};


static struct MemoryModule data_memory        = {NULL, NULL};
static struct MemoryModule instruction_memory = {NULL, NULL};


void memory_init(Address data_memory_size, Address instruction_memory_size)
{
    data_memory.data = calloc(sizeof(Address), data_memory_size);
    data_memory.end = data_memory.data + data_memory_size;

    instruction_memory.data = calloc(sizeof(Address), instruction_memory_size);
    instruction_memory.end = data_memory.data + data_memory_size;
}


Address memory_get_dmemory_size()
{
    return data_memory.end - data_memory.data;
}


Address memory_get_imemory_size()
{
    return instruction_memory.end - instruction_memory.data;
}


Word memory_fetch_word(Address address)
{
    return data_memory.data[address];
}


Word memory_store_word(Address address, Word data)
{
    Word old = data_memory.data[address];
    data_memory.data[address] = data;
    return old;
}


__attribute__((destructor))
static void memory_destroy()
{
    free(data_memory.data);
    free(instruction_memory.data);
}