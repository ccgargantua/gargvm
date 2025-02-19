#include "cpu.h"


#include <stdlib.h>
#include <stdio.h>


#include "debug.h"


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


typedef enum
{
    CPU_NO_ERROR,

    CPU_OUT_OF_STACK_BOUNDS,
    CPU_BAD_OPERATION,
} CPUError;


static CPUError push(CPU *cpu, uint32_t arg)
{
    assert(cpu);
    assert(cpu->stack && cpu->stack_pointer);
    if (cpu->stack + cpu->stack_size == cpu->stack_pointer)
    {
        dbg_printf("Attempted push past stack limit.\n");
        return CPU_OUT_OF_STACK_BOUNDS;
    }
    *(cpu->stack_pointer++) = arg;

    return CPU_NO_ERROR;
}

static CPUError pop(CPU *cpu, uint32_t *dest)
{
    assert(cpu);
    assert(cpu->stack && cpu->stack_pointer);
    if (cpu->stack == cpu->stack_pointer)
    {
        dbg_printf("Attempted to pop from empty stack.\n");
        return CPU_OUT_OF_STACK_BOUNDS;
    }
    *dest = *(--cpu->stack_pointer);
    return CPU_NO_ERROR;
}

static CPUError add(CPU *cpu)
{
    assert(cpu);
    assert(cpu->stack && cpu->stack_pointer);

    uint32_t v1, v2;

    CPUError e = pop(cpu, &v1);
    if (e != CPU_NO_ERROR) return e;

    e = pop(cpu, &v2);
    if (e != CPU_NO_ERROR) return e;

    return push(cpu, v1 + v2);
}

static CPUError subtract(CPU *cpu)
{
    assert(cpu);
    assert(cpu->stack && cpu->stack_pointer);

    uint32_t v1, v2;

    CPUError e = pop(cpu, &v1);
    if (e != CPU_NO_ERROR) return e;

    e = pop(cpu, &v2);
    if (e != CPU_NO_ERROR) return e;

    return push(cpu, v2 - v1);
}

static CPUError multiply(CPU *cpu)
{
    assert(cpu);
    assert(cpu->stack && cpu->stack_pointer);

    uint32_t v1, v2;

    CPUError e = pop(cpu, &v1);
    if (e != CPU_NO_ERROR) return e;

    e = pop(cpu, &v2);
    if (e != CPU_NO_ERROR) return e;

    return push(cpu, v1 * v2);
}

static CPUError divide(CPU *cpu)
{
    assert(cpu);
    assert(cpu->stack && cpu->stack_pointer);

    uint32_t v1, v2;

    CPUError e = pop(cpu, &v1);
    if (e != CPU_NO_ERROR) return e;

    e = pop(cpu, &v2);
    if (e != CPU_NO_ERROR) return e;

    if (v1 == 0) return CPU_BAD_OPERATION;

    return push(cpu, v2/v1);
}

bool CPU_execute_program(CPU *cpu, MemoryModule *module,  uint32_t *program)
{
    assert(cpu);
    assert(cpu->stack && cpu->stack_pointer);
    assert(module && module->data);
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
            {
                uint32_t dummy;
                (void)pop(cpu, &dummy);
            }
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
            {
                uint32_t v = 0; // Temp UB fix
                pop(cpu, &v);
                store(module, *++program, v);
            }
            break;
        default:
            return false;
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
