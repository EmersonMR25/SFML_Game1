#pragma once

#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "definitions.h"

#define _MAX_RADIUS 30
#define _MIN_RADIUS 20
#define _MIN_RGB 0
#define _MAX_RGB 255
#define _MAX_MASS 100
#define _MIN_MASS 10
#define _MAX_VELOCITY 5
#define _MIN_VELOCITY -5

class Particles
{
private:
    sf::CircleShape _circle;
    sf::Vector2f _velocity;
    float _mass;
    void setCoordinates(const sf::Event &event);
    void setRandomColor();
    void setRandomRadius();
    void setRandomVelocity();
    void setRandomMass();
    void checkBounds();
    void calculatePrimeVelocity(Particles &other);

public:
    Particles(const sf::Event &event);
    ~Particles();
    void draw(sf::RenderWindow &window);
    void update();
    void detectCollision(Particles &other);
};

#endif // PARTICLES_H
