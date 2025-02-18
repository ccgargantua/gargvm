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
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        dbg_printf("Cannot open file '%s'\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = (size_t)ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    if (!buffer)
    {
        dbg_printf("Failed to allocate memory to string buffer.\n");
        fclose(file);
        return NULL;
    }

    if (!fread(buffer, 1, file_size, file)) return NULL;
    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char *argv[])
{
    assert(argc == 2);

    CPU *cpu = create_CPU(1024, 0);
    uint32_t memory_data[1024] = {0};
    MemoryModule memory = {memory_data, 1024};

    char *assembly_code = read_file_to_string(argv[1]);
    assert(assembly_code);

    uint32_t *gbc = assemble(assembly_code, strlen(assembly_code));
    assert(gbc);

    CPU_execute_program(cpu, &memory, gbc);

    free(assembly_code);
    free(gbc);
    destroy_CPU(cpu);

    return 0;
}