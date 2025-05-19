#include <stdio.h>
#include "cpu/cpu.h"
#include "stack/stack.h"

int main(int argc, char* argv[]) {
	// Init CPU
	cpu_t cpu = {0};
    display_t display = {0};
    if (initDisplay(&display)) {
        initCPU(&cpu);
        loadProgram(&cpu, readFromFile(argv[1]));
        while (cpu.is_running) {
            decode(&cpu);
        }
       /* while (display.is_running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) display.is_running = false;
            }
            decode(&cpu);
            clearDisplay(&display);
            SDL_RenderPresent(display.renderer);
        }
        destroyDisplay(&display);*/
    }
	printCpuInfo(&cpu, PRINT_REGS | PRINT_FLAGS);
}