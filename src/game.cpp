#include "game.h"

Game::Game()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode(_WIDTH, _HEIGHT), "Ellastic Collision Simulator", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    while (window.isOpen())
    {
        handleEvents();
        window.clear();

        for (auto &particle : particles)
        {
            particle.update();
        }
        // Collision detection between particles
        for (size_t i = 0; i < particles.size(); ++i)
        {
            for (size_t j = i + 1; j < particles.size(); ++j)
            {
                particles[i].detectCollision(particles[j]);
            }
        }
        // Draw particles after updating and checking collisions
        for (auto &particle : particles)
        {
            particle.draw(window);
        }
        window.display();
    }
} // Game::Game()

Game::~Game()
{
} // Game::~Game()

void Game::handleEvents()
{
    while (window.pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            window.close();
        if (this->event.type == sf::Event::KeyPressed)
        {
            if (this->event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }
        if (this->event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // emplace_back will create a new Particle based on the constructor arguments
                particles.emplace_back(this->event);
            }
        }
    }
} // Game::handleEvents()