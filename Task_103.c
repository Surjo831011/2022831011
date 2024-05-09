#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 720
#define HEIGHT 720
#define RADIUS 30
#define CIRCLE_RADIUS 20
#define SPEED 2


bool initSDL(SDL_Window** window, SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL initialization is failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Circle Collision", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,SDL_WINDOW_SHOWN);
   
    if (*window == NULL)
    {
        printf("Window creation is failed: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL)
    {
        printf("Renderer creation is failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void circle1(SDL_Renderer* renderer, int circleX, int circleY, int circleRadius)
{
    for (int x = -circleRadius; x <= circleRadius; x++)
    {
        for (int y = -circleRadius; y <= circleRadius; y++)
        {
            if (x * x + y * y <= circleRadius * circleRadius)
            {
                SDL_RenderDrawPoint(renderer, circleX + x, circleY + y);
            }
        }
    }
}

void circle2(SDL_Renderer* renderer, int centerX, int centerY)
{
    circle1(renderer, centerX, centerY, CIRCLE_RADIUS);
}

bool checkCollision(int circle1X, int circle1Y, int circle1Radius, int circle2X, int circle2Y, int circle2Radius)
{
    int dx = circle2X - circle1X;
    int dy = circle2Y - circle1Y;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSumSquared = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);
    return distanceSquared <= radiusSumSquared;
}

void move(SDL_Event event, int* currentPositionX, int* currentPositionY)
{
    if (event.key.keysym.sym == SDLK_UP)
    {
        *currentPositionY -= 7;
    }
    else if (event.key.keysym.sym == SDLK_DOWN)
    {
        *currentPositionY += 7;
    }
    else if (event.key.keysym.sym == SDLK_LEFT)
    {
        *currentPositionX -= 7;
    }
    else if (event.key.keysym.sym == SDLK_RIGHT)
    {
        *currentPositionX += 7;
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

    int x1 = -RADIUS;
    int y1= HEIGHT / 2;
    int x2 = WIDTH / 2;
    int y2 = 0;

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
                move(event, &x2, &y2);
            }
        }

        x1+= SPEED;
        if (x1 > WIDTH + RADIUS)
        {
            x1 = -RADIUS;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (checkCollision(x1 ,y1, RADIUS, x2, y2, CIRCLE_RADIUS))
        {
            
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
            circle1(renderer, x1 , y1, RADIUS);
            circle2(renderer, x2, y2);
        }
        else
        {
            
            SDL_SetRenderDrawColor(renderer, 200, 180, 180, 255);
            circle1(renderer,x1, y1, RADIUS);

            SDL_SetRenderDrawColor(renderer, 200, 180, 100, 255);
            circle2(renderer, x2, y2);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



