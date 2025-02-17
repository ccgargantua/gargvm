#include "cpu.h"


#include <stdlib.h>
#include <stdio.h>


CPU * create_CPU(uint32_t stack_size, uint32_t cache_size)
{
    CPU *cpu = malloc(sizeof(CPU));
    assert(cpu);

    cpu->stack_size = stack_size;
    cpu->cache_size = cache_size;

    cpu->stack = malloc(sizeof(uint32_t) * stack_size);
    cpu->stack_pointer = cpu->stack;
    cpu->data_cache = malloc(sizeof(uint32_t) * cache_size);

    assert(cpu->stack);
    assert(cpu->data_cache);

    return cpu;
}

static void push(CPU *cpu, uint32_t arg)
{
    assert(cpu);
    *(cpu->stack_pointer++) = arg;
}

static uint32_t pop(CPU *cpu)
{
    assert(cpu);
    return *(--cpu->stack_pointer);
}

static void add(CPU *cpu)
{
    assert(cpu);
    push(cpu, pop(cpu) + pop(cpu));
}

static void subtract(CPU *cpu)
{
    assert(cpu);
    uint32_t temp = pop(cpu);
    push(cpu, pop(cpu) - temp);
}

static void multiply(CPU *cpu)
{
    assert(cpu);
    push(cpu, pop(cpu) * pop(cpu));
}

static void divide(CPU *cpu)
{
    assert(cpu);
    uint32_t temp = pop(cpu);
    push(cpu, temp / pop(cpu));
}

bool CPU_execute_program(CPU *cpu, MemoryModule *module,  uint32_t *program)
{
    assert(cpu);
    assert(module);
    assert(program);

    while (*program != PROGRAM_END)
    {
        switch(*program)
        {
        case PROGRAM_END:
            return true;
        case PSH:
            push(cpu, *(++program));
            break;
        case POP:
            (void)pop(cpu);
            break;
        case ADD:
            add(cpu);
            break;
        case SUB:
            subtract(cpu);
            break;
        case MUL:
            multiply(cpu);
            break;
        case DIV:
            divide(cpu);
            break;
        case FWD:
            push(cpu, fetch(module, *++program));
            break;
        case SWD:
            store(module, *++program, pop(cpu));
            break;
        default:
            assert(0);
        }

        if (memory_has_error(module))
            break;

        program++;
    }
    return false;
}


void destroy_CPU(CPU *cpu)
{
    if (cpu)
    {
        if (cpu->stack)
            free(cpu->stack);

        if (cpu->data_cache)
            free(cpu->data_cache);
        free(cpu);
    }
}
