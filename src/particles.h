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
    sf::Vector2f velocity;
    void setCoordinates(const sf::Event &event);
    void setColor();
    void setRadius();

public:
    Particles(const sf::Event &event);
    ~Particles();
    void draw(sf::RenderWindow &window);
    void update();
};

#endif // PARTICLES_H
