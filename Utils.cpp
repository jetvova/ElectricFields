//
// Created by vova on 10/6/19.
//

#include "Utils.h"
#include "SDL.h"


void drawCircle(SDL_Renderer * renderer, int centreX, int centreY, int radius) {
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}



void drawVector(SDL_Renderer *renderer, int startX, int startY, int dX, int dY) {
    SDL_RenderDrawLine(renderer, startX, startY, startX + dX, startY + dY);
    double r = sqrt(dX*dX + dY*dY);
//    if (r >= 4) {
//        drawCircle(renderer, startX, startY, 2);
//    }
}
