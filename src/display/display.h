#include <stdbool.h>
#include "SDL3/SDL.h"

#define DISPLAY_W 64
#define DISPLAY_H 32
#define DISPLAY_SIZE DISPLAY_W*DISPLAY_H

typedef struct {
	bool display[DISPLAY_W * DISPLAY_H];
	SDL_Window* wnd;
	SDL_Renderer* renderer;
} display_t;

bool initDisplay(display_t* display);
void destroyDisplay(display_t* display);
void clearDisplay(display_t* display);