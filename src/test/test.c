#include <stdio.h>
#include <stdbool.h>
#include "../cpu/cpu.h"

bool compare(uint8_t* arr1, uint8_t* arr2) {
	for (int i = 0; i < 5; ++i) {
		if (arr1[i] != arr2[i]) {
			return false;
		}
	}
	return true;
}

cpu_t* runCpu(const char* file_name) {
	// Init CPU
	cpu_t cpu = { 0 };
	initCPU(&cpu);
	loadProgram(&cpu, readFromFile(file_name));
	while (cpu.is_running) {
		decode(&cpu);
	}
	//printCpuInfo(&cpu, PRINT_REGS);
	return &cpu;
}

/* TEST FUNCTIONS */
void testMovOp(cpu_t* cpu, uint8_t* result) {
	if (compare(cpu->regs, result)) { printf("Mov op test passed!\n"); return; }
	printf("Mov op test not passed!\n");
}

void testAddOp(cpu_t* cpu, uint8_t* result) {
	if (compare(cpu->regs, result)) { printf("Add op test passed!\n"); return; }
	printf("Add op test not passed!\n");
}

void testSubOp(cpu_t* cpu, uint8_t* result) {
	if (compare(cpu->regs, result)) { printf("Sub op test passed!\n"); return; }
	printf("Sub op test not passed!\n");
}

void testMulOp(cpu_t* cpu, uint8_t* result) {
	if (compare(cpu->regs, result)) { printf("Mul op test passed!\n"); return; }
	printf("Mul op test not passed!\n");
}

void testDivOp(cpu_t* cpu, uint8_t* result) {
	if (compare(cpu->regs, result)) { printf("Div op test passed!\n"); return; }
	printf("Div op test not passed!\n");
}

void testIncOp(cpu_t* cpu, uint8_t* result) {
	if (compare(cpu->regs, result)) { printf("Inc op test passed!\n"); return; }
	printf("Inc op test not passed!\n");
}

void testDecOp(cpu_t* cpu, uint8_t* result) {
	if (compare(cpu->regs, result)) { printf("Dec op test passed!\n"); return; }
	printf("Dec op test not passed!\n");
}

/* MAIN METHODS */
void testMathCases() {
	printf("START TESTING MATH OPS\n");

	uint8_t add_reg_test[] = { 1, 2, 3, 0, 0, 0 };
	testAddOp(runCpu("../../../src/test/programs/add_reg.txt"), add_reg_test);

	uint8_t add_value_test[] = { 0, 10, 25, 0, 0, 35 };
	testAddOp(runCpu("../../../src/test/programs/add_value.txt"), add_value_test);

	uint8_t sub_reg_test[] = { 5, 2, 3, 0, 0, 0 };
	testSubOp(runCpu("../../../src/test/programs/sub_reg.txt"), sub_reg_test);

	uint8_t sub_value_test[] = { 0, 10, 25, 0, 0, 15 };
	testSubOp(runCpu("../../../src/test/programs/sub_value.txt"), sub_value_test);

	uint8_t mul_reg_test[] = { 5, 2, 10, 0, 0, 0 };
	testMulOp(runCpu("../../../src/test/programs/mul_reg.txt"), mul_reg_test);

	uint8_t mul_value_test[] = { 0, 10, 25, 0, 0, 250 };
	testMulOp(runCpu("../../../src/test/programs/mul_value.txt"), mul_value_test);

	uint8_t div_reg_test[] = { 10, 2, 5, 0, 0, 0 };
	testDivOp(runCpu("../../../src/test/programs/div_reg.txt"), div_reg_test);

	uint8_t div_value_test[] = { 0, 250, 10, 0, 0, 25 };
	testDivOp(runCpu("../../../src/test/programs/div_value.txt"), div_value_test);

	uint8_t inc_test[] = { 1, 0, 0, 0, 0, 0 };
	testIncOp(runCpu("../../../src/test/programs/inc.txt"), inc_test);

	uint8_t dec_test[] = { 2, 1, 0, 0, 0, 0 };
	testDecOp(runCpu("../../../src/test/programs/dec.txt"), dec_test);

	printf("END TESTING MATH OPS\n");
}

void testLogicCases() {
	printf("START TESTING LOGIC OPS\n");
	printf("END TESTING LOGIC OPS\n");
}

/* MAIN */
int main(int argc, char* argv[]) {
	testMathCases();
}