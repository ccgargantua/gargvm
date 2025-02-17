#ifndef ASSEMBLER_H
#define ASSEMBLER_H


#include <stddef.h>
#include <assert.h>
#include <stdint.h>


uint32_t *assemble(char *code, size_t code_size);


#endif