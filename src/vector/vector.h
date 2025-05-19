#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* SIMPLE DYNAMIC ARRAY */
typedef struct {
	uint32_t* data;
	size_t size;
	size_t capacity;
} vector_t;

vector_t* newVec();
void resize(vector_t* vec);
void append(vector_t* vec, uint32_t value);
void del(vector_t* vec, size_t pos);
void print(vector_t vec);

#endif // !VECTOR_H