#include "game.h"

Game::Game() : window(sf::VideoMode(_WIDTH, _HEIGHT), "Gravity Simulator")
{
    this->window.setFramerateLimit(60);
    while (window.isOpen())
    {
        handeEvents();
        window.clear();
        for (auto particle : particles)
        {
            particle.draw(window);
        }
        window.display();
    }
}

Game::~Game()
{
}

void Game::handeEvents()
{
    while (window.pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            window.close();
        if (this->event.type == sf::Event::KeyPressed)
        {
            if (this->event.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
}