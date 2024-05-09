#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 640
#define HEIGHT 480
#define RADIUS 100

bool initSDL(SDL_Window** window, SDL_Renderer** renderer) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Circle_Draw", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) 
    {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) 
    {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void drawing(SDL_Renderer* renderer, int centerX, int centerY, int radius) 
{
    for (int x = -radius; x <= radius; x++) 
    {
        for (int y = -radius; y <= radius; y++) 
        {
            if (x * x + y * y <= radius * radius) 
            {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

int main(int argc, char* argv[]) 
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initSDL(&window, &renderer)) 
    {
        return 1;
    }

    bool game_running = true;
    SDL_Event event;

    while (game_running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                game_running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0 ,0 , 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0,255,255);
        drawing(renderer, WIDTH / 2, HEIGHT / 2, RADIUS);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}