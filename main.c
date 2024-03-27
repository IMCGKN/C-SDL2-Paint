#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 800, 600);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Uint32 pixels[800 * 600];

    bool mouseDown = false;
    
    Uint32 color = 1;

    memset(pixels, 255, 800 * 600 * sizeof(Uint32));

    SDL_Event e;
    bool close = false;
    while(close == false)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                close = true;
            if(e.type == SDL_KEYUP)
            {
                if(e.key.keysym.sym == SDLK_b)
                {
                    color = 0xFFF;
                }
                if(e.key.keysym.sym == SDLK_r)
                {
                    color = -0xFFFF;
                }
                if(e.key.keysym.sym == SDLK_g)
                {
                    color = 0x9000;
                }
                if(e.key.keysym.sym == SDLK_d)
                {
                    color = 256;
                }
                if(e.key.keysym.sym == SDLK_w)
                {
                    color = 0xFFFFFF;
                }
            }
            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    close = true;
                    break;
                case SDLK_q:
                    memset(pixels, 255, 800 * 600 * sizeof(Uint32));
                    break;
                }
            }
            if(e.type == SDL_MOUSEBUTTONUP)
            {
                if(e.button.button == SDL_BUTTON_LEFT)
                    mouseDown = false;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_LEFT)
                    mouseDown = true;
            }
            if(e.type == SDL_MOUSEMOTION)
            {
                if(mouseDown == true)
                {
                    int mouseX = e.motion.x;
                    int mouseY = e.motion.y;
                    for(int i = 0; i < 60; i++)
                    {
                        pixels[mouseY * 800 + mouseX - i] = color;
                        pixels[mouseY * 800 + mouseX + i] = color;
                    }
                }
            }
        }

        SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}