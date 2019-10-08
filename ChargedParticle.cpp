//
// Created by vova on 10/6/19.
//

#include "ChargedParticle.h"
#include "SDL.h"
#include "Utils.h"

void ChargedParticle::draw(SDL_Renderer *renderer) {

    drawCircle(renderer, x, y, 10);
    SDL_RenderDrawLine(renderer, x-5, y, x+5, y);

    if ( charge > 0 ) {
        SDL_RenderDrawLine(renderer, x, y + 5, x , y - 5);
    }

}

std::pair<double, double> ChargedParticle::fieldPotential(double cX, double cY) {

    double dX = cX - x;
    double dY = cY - y;
    double r = sqrt(dX*dX + dY*dY);
    return { dX / r * charge / r / r, dY / r * charge / r / r };
}
