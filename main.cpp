#include <random>
#include <iostream>
#include <thread>
#include <unistd.h>
#include "SDL.h"
#include "Utils.h"
#include "ChargedParticle.h"
#include <algorithm>

using namespace std;


enum displayMode {
    GRID = 0, RANDOMSAMPLING = 1, COLOR = 2
};


int main() {

    int mode = GRID;

    std::vector<ChargedParticle> particleList = {
        ChargedParticle(1000000, 220, 240),
        ChargedParticle(-1000000, 420, 240),
    };


    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(5, 19); // distribution in range [1, 6]




    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(1240, 880, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                for (ChargedParticle &p : particleList) {
                    p.draw(renderer);
                }

                int step = (mode == COLOR) ? 4 : 17;

                for (int x = 0; x < 1240; x = x + ((mode == RANDOMSAMPLING) ? dist(rng) : step))  {
                    for (int y = 0; y < 880; y = y + ((mode == RANDOMSAMPLING) ? dist(rng) : step)) {

                        double totalX = 0, totalY = 0;

                        for (ChargedParticle &p : particleList) {
                            auto [dx,dy] = p.fieldPotential(x, y);
                            totalX += dx;
                            totalY += dy;
                        }


                        double r = sqrt(totalX * totalX + totalY * totalY);
                        double shortR = min(r, (mode == COLOR) ? 127 : 40.0);

                        double dX = totalX / r * shortR;
                        double dY = totalY / r * shortR;

                        if (mode == COLOR) {
                            SDL_SetRenderDrawColor(renderer, 127 + dX, 0, 127 + dY, SDL_ALPHA_OPAQUE);

                            SDL_Rect rect = {x, y, step, step};

                            SDL_RenderFillRect(renderer, &rect);
                        } else {
                            drawVector(renderer, x, y, dX, dY);
                        }
                    }
                }



                SDL_RenderPresent(renderer);


                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT:
                            done = SDL_TRUE;
                            break;
                        case SDL_MOUSEMOTION:
                            particleList[0].x = event.motion.x;
                            particleList[0].y = event.motion.y;
                            break;
                        case SDL_KEYDOWN:
                            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {mode = (mode + 1) % 3;}
                                
                            break;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}

