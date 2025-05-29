#include <stdio.h>
#include "cpu/cpu.h"

int main(int argc, char* argv[]) {
	// Init CPU
	cpu_t cpu = {0};
	initCPU(&cpu);
	loadProgram(&cpu, readFromFile(argv[1]));
	while (cpu.is_running) {
	    decode(&cpu);
	}
	if(!strcmp(argv[2], "-rfs"))
		printCpuInfo(&cpu, PRINT_REGS | PRINT_FLAGS | PRINT_STACK);
	if (!strcmp(argv[2], "-m"))
		printCpuInfo(&cpu, PRINT_MEM);
	if (!strcmp(argv[2], "-all"))
		printCpuInfo(&cpu, PRINT_MEM | PRINT_REGS | PRINT_FLAGS | PRINT_STACK);
}