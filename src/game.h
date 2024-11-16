/**
 * @file game.h
 * @brief Defines the Game class for managing the particle simulation system
 *
 * This header file contains the declaration of the Game class which handles
 * the main window, event processing, and particle system management for
 * the physics simulation.
 */

#pragma once
#ifndef GAME_H
#define GAME_H

#include "definitions.h"
#include <iostream>
#include <vector>
#include "particles.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/**
 * @class Game
 * @brief Controls the main simulation environment and particle system
 *
 * The Game class manages the simulation window, processes user input events,
 * and coordinates the particle system. It serves as the main controller
 * for the entire application.
 */
class Game
{
private:
    sf::RenderWindow window;          ///< Main rendering window for the simulation
    sf::Event event;                  ///< Event handler for user input and window events
    std::vector<Particles> particles; ///< Container for all active particles

    /**
     * @brief Processes window and user input events
     */
    void handleEvents();

public:
    /**
     * @brief Constructs the game environment and initializes systems
     */
    Game();

    /**
     * @brief Destructor for cleaning up game resources
     */
    ~Game();
};

#endif // GAME_H