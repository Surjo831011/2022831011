#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

bool initSDL(SDL_Window** window, SDL_Renderer** renderer) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Growing Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL) 
    {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void drawSolidCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) 
{
    for (int x = -radius; x <= radius; x++) 
    {
        for (int y = -radius; y <= radius; y++) 
        {
            if (x*x + y*y <= radius*radius) 
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

    SDL_Event event;
    bool running = true;
    int circleRadius = 5; 
    int circleX = WIDTH / 2; 
    int circleY = HEIGHT / 2; 
    int radiusIncrease = 4; 

    while (running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                running = false;
            }
        }


        SDL_SetRenderDrawColor(renderer, 140, 140, 255, 255);
        SDL_RenderClear(renderer);

        
        SDL_SetRenderDrawColor(renderer, 200, 140, 255, 255);
        drawSolidCircle(renderer, circleX, circleY, circleRadius);

        
        SDL_RenderPresent(renderer);

       
        circleRadius += radiusIncrease;

        
        if (circleX + circleRadius >= WIDTH || circleY + circleRadius >= HEIGHT) 
        {
            
            circleRadius = 5;
            circleX = WIDTH / 2;
            circleY = HEIGHT / 2;
        }
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}