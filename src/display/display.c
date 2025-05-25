#include "display.h"

// Initialize display
bool initDisplay(display_t* display) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("Cannot init SDL!\n");
        return false;
    }
    if (!SDL_CreateWindowAndRenderer("CPU Running", DISPLAY_W * 10, DISPLAY_H * 10, 0, &display->wnd , &display->renderer)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION, 
            "Couldn't create window and renderer: %s", 
            SDL_GetError()
        );
        return false;
    }
    memset(display->display, false, DISPLAY_SIZE);
    return true;
}

// Destroy window and render
void destroyDisplay(display_t* display) {
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->wnd);
    SDL_Quit();
}

// Clear window
void clearDisplay(display_t* display) {
    SDL_SetRenderDrawColor(display->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(display->renderer);
}