#pragma once

#ifndef GAME_H
#define GAME_H

#include "definitions.h"
#include <SFML/Graphics.hpp>

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;
    void handeEvents();

public:
    Game();
    ~Game();
};

#endif // GAME_H