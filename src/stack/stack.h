#ifndef STACK_H
#define STACK_H

#include "../vector/vector.h"

typedef struct {
	vector_t* stack_data;
} stack_t;

void initStack(stack_t* stack);
void push(stack_t* stack, uint32_t value);
uint32_t pop(stack_t* stack);
#endif // !STACK_H