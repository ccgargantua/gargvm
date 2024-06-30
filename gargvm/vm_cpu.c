#include "vm_cpu.h"


static struct CPU
{
    CPURegister registers[32];
    Address instruction_pointer;
}


Instruction cpu_execute_next_instruction();