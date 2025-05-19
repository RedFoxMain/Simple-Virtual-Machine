#include "stack.h"

void initStack(stack_t* stack) {
	stack->stack_data = newVec();
}

void push(stack_t* stack, uint32_t value) {
	append(stack->stack_data, value);
}

uint32_t pop(stack_t* stack) {
	uint32_t value = stack->stack_data->data[stack->stack_data->size];
	del(stack->stack_data, stack->stack_data->size);
	return value;
}
