#ifndef VM_PROGRAMMER_H
#define VM_PROGRAMMER_H


#include <stdio.h>

#include "vm_assert.h"
#include "definitions.h"
#include "memory.h"


#define PROGRAMMER_LINE_BUFFER_SIZE 81


Instruction *programmer_assemble(char filename[256]);
void programmer_flash(Instruction *instructions, Address size);


#endif