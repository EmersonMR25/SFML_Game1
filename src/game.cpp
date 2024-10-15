#include "game.h"

Game::Game() : window(sf::VideoMode(_WIDTH, _HEIGHT), "SFML Game")
{
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        handeEvents();
        window.clear();
        window.display();
    }
}

Game::~Game()
{
}

void Game::handeEvents()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
}