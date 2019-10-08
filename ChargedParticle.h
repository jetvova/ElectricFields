//
// Created by vova on 10/6/19.
//

#ifndef EXPERIMENTS_CHARGEDPARTICLE_H
#define EXPERIMENTS_CHARGEDPARTICLE_H

#include <utility>

class SDL_Renderer;

class ChargedParticle {

public:
    double charge;
    double x;
    double y;

    ChargedParticle(double charge, double x, double y) : charge(charge), x(x), y(y) { }

    void draw(SDL_Renderer* renderer);

    std::pair<double, double> fieldPotential(double cX, double cY);


};


#endif //EXPERIMENTS_CHARGEDPARTICLE_H
