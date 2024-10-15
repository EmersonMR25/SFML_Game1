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

private:
    sf::Vector2f getPosition(const sf::Event &event);
    float getRadius();    // Randomly chooses the radius between 5 and 20
    sf::Color getColor(); // Randomly chooses a color from a predefined list

public:
    Particles(sf::RenderWindow &window, const sf::Event &event);
    ~Particles();
};

#endif // PARTICLES_H