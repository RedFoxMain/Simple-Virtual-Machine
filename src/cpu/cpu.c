#include "cpu.h"

// Read program from file
vector_t* readFromFile(const char* file_name) {
	vector_t* program = newVec();
	FILE* fp = fopen(file_name, "r");
	if (!fp) {
		if (!strlen(file_name)) file_name = "null";
		printf("Cannot find file (%s)\n", file_name);
		exit(1);
	}
	uint32_t value;
	while (!feof(fp)) {
		fscanf(fp, "%X", &value);
		append(program, value);
	}
	/*print(*program);*/
	return program;
}

// Load program to CPU memory
void loadProgram(cpu_t* cpu, vector_t* vec) {
	cpu->program_size = vec->size;
	for (size_t i = 0; i < vec->size; ++i)
		cpu->memory[PROGRAM_ADDRESS + i] = vec->data[i];
}

// Init CPU
void initCPU(cpu_t* cpu) {
	cpu->is_running = true;
	cpu->is_printing = false;
	cpu->program_size = 0;

	// Init memory
	memset(cpu->memory, 0, MEM_SIZE);
	memset(cpu->regs, 0, REG_COUNT);
	initStack(&cpu->stack);
	cpu->pc = PROGRAM_ADDRESS;

	// Init instruction bits
	cpu->instr.op_code = 0;
	cpu->instr.nnnn = 0;
	cpu->instr.nnn = 0;
	cpu->instr.nn = 0;
	cpu->instr.n = 0;

	// Set flags
	clearFlags(cpu);
}

// Clear CPU flags
void clearFlags(cpu_t* cpu) {
	cpu->flag.e = false;
	cpu->flag.o = false;
	cpu->flag.z = true;
	cpu->flag.l = false;
}

// Parse command
void fetch(cpu_t* cpu) {
	cpu->instr.op_code = cpu->memory[cpu->pc++];
	cpu->instr.nnnn = (cpu->instr.op_code >> 12) & 0x0F;
	cpu->instr.nnn = cpu->instr.op_code & (0xFFF >> 2);
	cpu->instr.nn = cpu->instr.op_code;
	cpu->instr.n = cpu->instr.op_code & (0xF >> 1);
}

// Decode command
void decode(cpu_t* cpu) {
	fetch(cpu);
	switch (cpu->instr.op_code >> 16) {
		case HALT:
			if(cpu->instr.nnnn == 0) cpu->is_running = false; // HALT
			if(cpu->instr.nnnn == 1) clearFlags(cpu);		  // CLRF
			if (cpu->instr.nnnn == 2) {}					  // DRW
			break;
		case MOV:
			/*
			* mov reg, value
			* mov reg1, reg2
			*/
			if (cpu->instr.nnnn == 0) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] = cpu->instr.nn;
			if (cpu->instr.nnnn == 1) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] = cpu->regs[GET_NN_BITS(cpu->instr.nn)];
			updateFlags(cpu);
			break;
		case ADD:
			/*
			* add reg, value
			* add reg1, reg2
			*/
			if(cpu->instr.nnnn == 0) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] += cpu->instr.nn;
			if(cpu->instr.nnnn == 1) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] += cpu->regs[GET_NN_BITS(cpu->instr.nn)];
			updateFlags(cpu);
			break;
		case SUB:
			/*
			* sub reg, value
			* sub reg1, reg2
			*/
			if (cpu->instr.nnnn == 0) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] -= cpu->instr.nn;
			if (cpu->instr.nnnn == 1) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] -= cpu->regs[GET_NN_BITS(cpu->instr.nn)];
			updateFlags(cpu);
			break;
		case MUL:
			/*
			* mul reg, value
			* mul reg1, reg2
			*/
			if (cpu->instr.nnnn == 0) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] *= cpu->instr.nn;
			if (cpu->instr.nnnn == 1) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] *= cpu->regs[GET_NN_BITS(cpu->instr.nn)];
			updateFlags(cpu);
			break;
		case DIV:
			/*
			* div reg, value
			* div reg1, reg2
			*/
			if (cpu->instr.nnnn == 0) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] /= cpu->instr.nn;
			if (cpu->instr.nnnn == 1) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] /= cpu->regs[GET_NN_BITS(cpu->instr.nn)];
			updateFlags(cpu);
			break;
		case INC:
			// inc reg
			++cpu->regs[GET_NNN_BITS(cpu->instr.nnn)];
			updateFlags(cpu);
			break;
		case DEC:
			// dec reg
			--cpu->regs[GET_NNN_BITS(cpu->instr.nnn)];
			updateFlags(cpu);
			break;
		case AND:
			/*
			* and reg, value
			* and reg1, reg2
			*/
			if (cpu->instr.nnnn == 0) cpu->flag.l = cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] && cpu->instr.nn;
			if (cpu->instr.nnnn == 1) cpu->flag.l = cpu->regs[GET_NN_BITS(cpu->instr.nn)] && cpu->regs[cpu->instr.n];
			break;
		case OR:
			/*
			* or reg, value
			* or reg1, reg2
			*/
			if (cpu->instr.nnnn == 0) cpu->flag.l = cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] || cpu->instr.nn;
			if (cpu->instr.nnnn == 1) cpu->flag.l = cpu->regs[GET_NN_BITS(cpu->instr.nn)] || cpu->regs[cpu->instr.n];
			break;
		case XOR:
			/*
			* xor reg, value
			* xor reg1, reg2
			*/
			if (cpu->instr.nnnn == 0) cpu->flag.l = cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] ^ cpu->instr.nn;
			if (cpu->instr.nnnn == 1) cpu->flag.l = cpu->regs[GET_NN_BITS(cpu->instr.nn)] ^ cpu->regs[cpu->instr.n];
			break;
		case JMP:
			switch (cpu->instr.nnnn) {
				case 0: // jmp addr
					cpu->pc = cpu->instr.nnn;
					break;
				case 1: // je addr
					if(cpu->flag.e) cpu->pc = cpu->instr.nnn;
					break;
				case 2: // jne addr
					if (!cpu->flag.e) cpu->pc = cpu->instr.nnn;
					break;
				case 3: // jo addr
					if (cpu->flag.o) cpu->pc = cpu->instr.nnn;
					break;
				case 4: // jno addr
					if (!cpu->flag.o) cpu->pc = cpu->instr.nnn;
					break;
				case 5: // jz addr
					if (cpu->flag.z) cpu->pc = cpu->instr.nnn;
					break;
				case 6: // jnz addr
					if (!cpu->flag.z) cpu->pc = cpu->instr.nnn;
					break;
				case 7: // jl addr
					if (cpu->flag.l) cpu->pc = cpu->instr.nnn;
					break;
				case 8: // jnl addr
					if (!cpu->flag.l) cpu->pc = cpu->instr.nnn;
					break;
			}
			clearFlags(cpu);
			break;
		case SHIFT:
			/*
			* shl reg, n
			* shr reg, n
			*/
			if (cpu->instr.nnnn == 0) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] <<= GET_NN_BITS(cpu->instr.nn);
			if (cpu->instr.nnnn == 1) cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] >>= GET_NN_BITS(cpu->instr.nn);
			updateFlags(cpu);
			break;
		case CMP:
			/*
			* cmp reg, value
			* cmp reg1, reg2
			*/
			if (cpu->instr.nnnn == 0) cpu->flag.e = cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] == cpu->instr.nn;
			if (cpu->instr.nnnn == 1) cpu->flag.e = cpu->regs[GET_NNN_BITS(cpu->instr.nnn)] == cpu->regs[GET_NN_BITS(cpu->instr.nn)];
			break;
		case STK:
			/* 
			* push [ reg | value ]
			* pop reg
			*/
			if (cpu->instr.nnnn == 0) {}
			if (cpu->instr.nnnn == 1) {}
			if (cpu->instr.nnnn == 2) {}
			break;
		case SCALL:
			/* 
			*  scall 0 - print
			*/
			if (cpu->regs[R7] == 0) {
				cpu->is_printing = true;
				printf("%c", cpu->regs[R0]);
			}
			break;
	}
}

void printCpuInfo(cpu_t* cpu, uint8_t mode) {
	if (cpu->is_printing) printf("\n");
	if (mode & PRINT_MEM) printMemory(cpu);
	if (mode & PRINT_REGS) printRegs(cpu);
	if (mode & PRINT_STACK) printStack(cpu);
	if (mode & PRINT_FLAGS) printFlags(cpu);
	cpu->is_printing = false;
}

// Print all registers
void printRegs(cpu_t* cpu) {
	printf("===REGS===\n");
	for (size_t i = 0; i < REG_COUNT; i++)
		printf("R[%i] = %03i\n", i, cpu->regs[i]);
	printf("==========\n");
}

// Print CPU flags
void printFlags(cpu_t* cpu) {
	printf("FLAGS: Equal(e)=%i Zero(z)=%i Overflow(o)=%i Logic(l)=%i\n", cpu->flag.e, cpu->flag.z, cpu->flag.o, cpu->flag.l);
}

// Print stack
void printStack(cpu_t* cpu) {
	printf("STACK: ");
	for (size_t i = 0; i < cpu->stack.stack_data->size; ++i)
		printf("%03i ", cpu->stack.stack_data->data[i]);
	printf("\n");
}

// Print memory
void printMemory(cpu_t* cpu) {
	printf("=======MEMORY=======\n");
	for (uint32_t i = PROGRAM_ADDRESS; i < PROGRAM_ADDRESS + cpu->program_size; ++i)
		printf("mem[0x%02X] = 0x%05X\n", i, cpu->memory[i]);
	printf("====================\n");
}

// Update flags
void updateFlags(cpu_t* cpu) {
	uint8_t reg = cpu->regs[GET_NNN_BITS(cpu->instr.nnn)];
	cpu->flag.z = (!reg) ? true : false;
	cpu->flag.o = ((UINT8_MAX - reg) == 255);
	cpu->flag.e = false;
	cpu->flag.l = false;
}