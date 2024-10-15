#pragma once

#ifndef GAME_H
#define GAME_H

#include "definitions.h"

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