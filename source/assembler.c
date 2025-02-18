#include "assembler.h"
#include "cpu.h"
#include "debug.h"

#include <stdio.h>

#define DELIMITERS ",; \t\n"

#define PROGRAM_CHARACTER_LIMIT ( 64u * 1024u )
#define PROGRAM_SIZE_LIMIT      ( PROGRAM_CHARACTER_LIMIT / sizeof(uint32_t) )

// So, we will see a lot of unsafe string functions here...
// I, personally, think a certain level of reliance on
// assumptions is absolutely fine. For example, a strcmp or
// scanf on a null-chcecked strtok return pointer
#include <string.h>

#define strequ(s1, s2) (strcmp(s1,s2) == 0)

uint32_t *assemble(char *code, size_t code_size)
{
    if (code_size == 0 || code_size > PROGRAM_CHARACTER_LIMIT)
    {
        dbg_printf("Invalid code size %llu must be in range (0, %llu\n]", code_size, PROGRAM_CHARACTER_LIMIT);
        return NULL;
    }
    uint32_t gbc[PROGRAM_SIZE_LIMIT] = {0};
    size_t gbc_size = 0;

    char *peeked = strtok(code, DELIMITERS);
    while (peeked)
    {
        if (strequ(peeked, "push"))
        {
            gbc[gbc_size++] = PSH;
            peeked = strtok(NULL, DELIMITERS);
            if (!peeked)
            {
                dbg_printf("Next token is NULL\n");
                return NULL;
            }

            uint32_t arg;
            if (sscanf(peeked, "%u", &arg) <= 0)
            {
                dbg_printf("Invalid next token for instruction PUSH '%s'\n", peeked);
                return NULL;
            }
            gbc[gbc_size++] = arg;
        }
        else if (strequ(peeked, "pop"))
        {
            gbc[gbc_size++] = POP;
            peeked = strtok(NULL, DELIMITERS);
            if (!peeked)
            {
                dbg_printf("Next token is NULL\n");
                return NULL;
            }

            uint32_t arg;
            if (sscanf(peeked, "%u", &arg) <= 0)
            {
                dbg_printf("Invalid next token for instruction POP '%s'\n", peeked);
                return NULL;
            }
            gbc[gbc_size++] = arg;
        }
        else if (strequ(peeked, "add"))
            gbc[gbc_size++] = ADD;
        else if (strequ(peeked, "sub"))
            gbc[gbc_size++] = SUB;
        else if (strequ(peeked, "mul"))
            gbc[gbc_size++] = MUL;
        else if (strequ(peeked, "div"))
            gbc[gbc_size++] = DIV;
        else if (strequ(peeked, "fwd"))
        {

            gbc[gbc_size++] = FWD;
            peeked = strtok(NULL, DELIMITERS);
            if (!peeked)
            {
                dbg_printf("Next token is NULL\n");
                return NULL;
            }

            uint32_t arg;
            if (sscanf(peeked, "%u", &arg) <= 0)
            {
                dbg_printf("Invalid next token for instruction FWD '%s'\n", peeked);
                return NULL;
            }
            gbc[gbc_size++] = arg;
        }
        else if (strequ(peeked, "swd"))
        {
            gbc[gbc_size++] = SWD;
            peeked = strtok(NULL, DELIMITERS);
            if (!peeked)
            {
                dbg_printf("Next token is NULL\n");
                return NULL;
            }

            uint32_t arg;
            if (sscanf(peeked, "%u", &arg) <= 0)
            {
                dbg_printf("Invalid next token for instruction SWD '%s'\n", peeked);
                return NULL;
            }
            gbc[gbc_size++] = arg;
        }
        else
        {
            dbg_printf("Invalid instruction '%u\n'", *peeked);
            return NULL;
        }

        peeked = strtok(NULL, DELIMITERS);
    }

    gbc[gbc_size++] = PROGRAM_END;

    uint32_t *program_code = calloc(sizeof(uint32_t), gbc_size);
    if (!program_code)
    {
        dbg_printf("Allocation for program code failed.\n");
        return NULL;
    }
    memcpy(program_code, gbc, sizeof(uint32_t) * gbc_size);
    assert(program_code);

    return program_code;
}