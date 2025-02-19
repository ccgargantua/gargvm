#include <stdio.h>
#include <stdlib.h>


// So, we will see a lot of unsafe string functions here...
// I, personally, think a certain level of reliance on
// assumptions is absolutely fine. For example, a strcmp or
// scanf on a null-chcecked strtok return pointer
#include <string.h>
#include <stdint.h>

#include "cpu.h"
#include "memory.h"
#include "assembler.h"
#include "debug.h"

char *read_file_to_string(const char *filename) {
    char *buffer = NULL;

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        dbg_printf("Cannot open file '%s'\n", filename);
        goto file_open_failure;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = (size_t)ftell(file);
    rewind(file);

    buffer = malloc(file_size + 1);
    assert(buffer);

    if (!fread(buffer, 1, file_size, file))
    {
        dbg_printf("Opened file but failed to read it\n");
        goto file_read_failure;
    }
    buffer[file_size] = '\0';

    file_read_failure:
    fclose(file);
    file_open_failure:
    return buffer;
}

int main(int argc, char *argv[])
{
    int return_code = 1;
    assert(argc == 2);

    CPU *cpu = create_CPU(1024, 0);
    if (!cpu)
        goto processor_allocation_failure;

    uint32_t memory_data[1024] = {0};
    MemoryModule memory = {memory_data, 1024};

    char *assembly_code = read_file_to_string(argv[1]);
    if (!assembly_code)
        goto file_read_failure;

    uint32_t *gbc = assemble(assembly_code, strlen(assembly_code));
    if (!gbc)
        goto assembly_failure;

    CPU_execute_program(cpu, &memory, gbc);

    return_code = 0;

    free(gbc);
    assembly_failure:
    free(assembly_code);
    file_read_failure:
    destroy_CPU(cpu);
    processor_allocation_failure:

    return return_code;
}