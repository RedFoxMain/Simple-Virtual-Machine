#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../vector/vector.h"
#include "../display/display.h"

#define PRINT_MEM   0b0001
#define PRINT_REGS  0b1000
#define PRINT_FLAGS 0b0100
#define PRINT_STACK 0b0010

#define PROGRAM_ADDRESS 0x200
#define MEM_SIZE 4 * 1024
#define REG_COUNT 8
#define STACK_DEPTH 32

#define GET_NNN_BITS(value) (value >> 8)
#define GET_NN_BITS(value) (value >> 4)

typedef enum {
	HALT, MOV,
	ADD, SUB, MUL, DIV, INC, DEC,
	AND, OR, XOR, SHIFT,
	JMP, STK, CMP, SCALL
};

/*
* R0 - Register for math
* R1 - Register for math
* R2 - Register for math
* R3 - Register for math
* R4 - X
* R5 - Y
* R6 - Counter
* R7 - SYSCALL operation
*/
typedef enum {
	R0, R1, R2, R3, R4, R5, R6, R7
};

// VM flags
typedef struct {
	bool e;
	bool o;
	bool z;
	bool l;
} flags_t;

// Parse instruction
typedef struct {
	uint32_t op_code;
	uint32_t nnnn;
	uint16_t nnn;
	uint8_t nn;
	uint8_t n;
} instruction_t;

// CPU
typedef struct {
	uint32_t memory[MEM_SIZE];
	uint8_t stack[STACK_DEPTH];
	int p_st;
	uint8_t regs[REG_COUNT];

	bool is_running;
	bool is_printing;
	uint32_t pc;
	flags_t flag;
	instruction_t instr;
	size_t program_size;

	display_t display;
} cpu_t;

// Main methods
vector_t* readFromFile(const char* file_name);
void loadProgram(cpu_t* cpu, vector_t* vec);
void initCPU(cpu_t* cpu);
void fetch(cpu_t* cpu);
void decode(cpu_t* cpu);
void clearFlags(cpu_t* cpu);
void updateFlags(cpu_t* cpu);

// Stack methods
void push(cpu_t* cpu, uint8_t value);
uint8_t pop(cpu_t* cpu);

// Debug methods
void printCpuInfo(cpu_t* cpu, uint8_t mode);
void printRegs(cpu_t* cpu);
void printFlags(cpu_t* cpu);
void printStack(cpu_t* cpu);
void printMemory(cpu_t* cpu);
#endif // !CPU_H