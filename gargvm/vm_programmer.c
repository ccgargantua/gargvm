#include <string.h>

#include "vm_programmer.h"


Instruction *programmer_assemble(char filename[256])
{
    ASSERT_NONNULL( fopen(filename, "r") );
    ASSERT(strnlen(filename, 256) <= 256,
           "Filename exceeds 256");

    Instruction instructions[];
}


void programmer_flash(Instruction *instructions, Address size)
{

}