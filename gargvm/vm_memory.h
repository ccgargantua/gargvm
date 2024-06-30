#ifndef VM_MEMORY_H
#define VM_MEMORY_H


#include "definitions.h"


void memory_init(Address data_memory_size, Address instruction_memory_size);
Address memory_get_dmemory_size();
Address memory_get_imemory_size();

uint32_t memory_fetch_word(Address address);
uint32_t memory_store_word(Address address, Word data);


#endif