#include "vector.h"

/* FOR DYNAMIC ARRAY */
vector_t* newVec() {
	vector_t* vector = (vector_t*)malloc(sizeof(vector_t));
	vector->size = 0;
	vector->capacity = 2 * sizeof(uint32_t);
	vector->data = (uint32_t*)malloc(vector->capacity * sizeof(uint32_t));
	return vector;
}

// Resize vector if size >= capacity
void resize(vector_t* vec) {
	vec->capacity *= 2;
	vec->data = realloc(vec->data, vec->capacity * sizeof(uint32_t));
}

// Append new element
void append(vector_t* vec, uint32_t value) {
	if (vec->size >= vec->capacity / sizeof(uint32_t)) resize(vec);
	vec->data[vec->size++] = value;
}

// Delete element by index
void del(vector_t* vec, size_t pos) {
	for (size_t i = pos; i < vec->size; ++i)
		vec->data[pos] = vec->data[i + 1];
	--vec->size;
}

void print(vector_t vec) {
	for (size_t i = 0; i < vec.size; ++i) {
		printf("%i ", vec.data[i]);
	}
}