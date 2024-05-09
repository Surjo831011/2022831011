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
    if (*window == NULL) 
    {
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

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) 
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
    int circle_Radius = 5; 
    int circleX = WIDTH / 2; 
    int circleY = HEIGHT / 2; 
    int increase = 5; 

    while (running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                running = false;
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderClear(renderer);

        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        drawCircle(renderer, circleX, circleY, circle_Radius);

        
        SDL_RenderPresent(renderer);

       
        circle_Radius += increase;

        
        if (circleX + circle_Radius >= WIDTH || circleY + circle_Radius >= HEIGHT) 
        {
            
            circle_Radius = 5;
            circleX = WIDTH / 2;
            circleY = HEIGHT / 2;
        }
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}