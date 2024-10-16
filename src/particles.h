#pragma once

#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "definitions.h"

class Particles
{
private:
    sf::CircleShape circle;

public:
    Particles(float x, float y);
    ~Particles();
    void draw(sf::RenderWindow &window);
};

#endif // PARTICLES_H