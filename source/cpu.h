#ifndef CPU_H
#define CPU_H


#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "memory.h"


#define PROGRAM_END 0U
#define PSH         1U
#define POP         2U
#define ADD         3U
#define SUB         4U
#define MUL         5U
#define DIV         6U
#define FWD         7U
#define SWD         8U

typedef struct
{
    uint32_t *stack;
    uint32_t *stack_pointer;
    uint32_t *data_cache;

    uint32_t stack_size;
    uint32_t cache_size;
} CPU;


CPU * create_CPU(uint32_t stack_size, uint32_t cache_size);
bool CPU_execute_program(CPU *cpu, MemoryModule *memory,  uint32_t *program);
void destroy_CPU(CPU *cpu);


#endif