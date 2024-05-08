#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 720
#define HEIGHT 720
#define RADIUS 30
#define SPEED 2
#define CIRCLE_radius 20

bool initSDL(SDL_Window** window, SDL_Renderer** renderer) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Circle Collision", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
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

void drawSolidCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) 
{
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

void drawControlledCircle(SDL_Renderer* renderer, int x, int y) 
{
    drawSolidCircle(renderer, x, y, CIRCLE_radius);
}

bool checkCollision(int x1, int y1, int x2, int y2, int radius1, int radius2) 
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSumSquared = (radius1 + radius2) * (radius1 + radius2);
    return distanceSquared <= radiusSumSquared;
}

int main(int argc, char* argv[]) 
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initSDL(&window, &renderer)) 
    {
        return 1;
    }

    int circleX = -RADIUS;
    int circleY = HEIGHT / 2;
    int controlledCircleX = WIDTH / 2;
    int controlledCircleY = 0;

    bool running = true;
    SDL_Event event;

    while (running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) 
            {
                if (event.key.keysym.sym == SDLK_UP) 
            {
                controlledCircleY -= 10;

            }
            else if (event.key.keysym.sym == SDLK_DOWN) 
            {
                controlledCircleY += 10;
            }
            else if (event.key.keysym.sym == SDLK_LEFT) 
            {
                controlledCircleX -= 10;
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) 
            {
                controlledCircleX += 10;
            }

            }
        }

        
        circleX += SPEED;
        if (circleX > WIDTH + RADIUS) 
        {
            circleX = -RADIUS;
        }

        SDL_SetRenderDrawColor(renderer, 200, 0, 255, 255);
        SDL_RenderClear(renderer);

        
        SDL_SetRenderDrawColor(renderer, 200, 180, 180, 255);
        drawSolidCircle(renderer, circleX, circleY, RADIUS);

        SDL_SetRenderDrawColor(renderer, 200, 180, 100, 255);
        drawControlledCircle(renderer, controlledCircleX, controlledCircleY);

        
        if (checkCollision(circleX, circleY, controlledCircleX, controlledCircleY, RADIUS, CIRCLE_radius)) 
        {
            
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, circleX - RADIUS, circleY, circleX + RADIUS, circleY);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}