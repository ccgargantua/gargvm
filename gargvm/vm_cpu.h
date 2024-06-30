#ifndef VM_CPU_H
#define VM_CPU_H


#include <stdlib.h>
#include "definitions.h"

typedef enum
{
    // Math
    MOV,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    // Memory
    LDW,
    STW,

    NOP,
} Instruction;





#endif