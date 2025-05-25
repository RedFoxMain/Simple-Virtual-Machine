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
	printCpuInfo(&cpu, PRINT_REGS | PRINT_FLAGS | PRINT_STACK);
}