#pragma once

#ifndef GAME_H
#define GAME_H

#include "definitions.h"
#include <iostream>
#include <vector>
#include "particles.h"
#include <SFML/Graphics.hpp>

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;
    std::vector<Particles> particles;
    void handeEvents();

public:
    Game();
    ~Game();
};

#endif // GAME_H