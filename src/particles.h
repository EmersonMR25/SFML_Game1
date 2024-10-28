#pragma once

#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include "definitions.h"

#define _MAX_RADIUS 50.0f
#define _MIN_RADIUS 20.0f
#define _MIN_RGB 0.0f
#define _MAX_RGB 255.0f
#define _GRAVITY_ACCELERATION 9.8f // Constant acceleration

class Particles
{
private:
    sf::CircleShape _circle;
    sf::Vector2f _velocity;
    float _weight;
    void setCoordinates(const sf::Event &event);
    void setRandomColor();
    void setRandomRadius();

public:
    Particles(const sf::Event &event);
    ~Particles();
    void draw(sf::RenderWindow &window);
    void update();
};

#endif // PARTICLES_H
