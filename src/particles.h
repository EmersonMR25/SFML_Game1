/**
 * @file particles.h
 * @brief Defines the Particles class for a physics-based particle simulation
 *
 * This header file contains the declaration of the Particles class which manages
 * individual particles in a physics simulation, handling their creation, movement,
 * collision detection, and rendering.
 */

#pragma once
#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "definitions.h"

/**
 * @brief Maximum radius of a particle in pixels
 */
#define _MAX_RADIUS 30

/**
 * @brief Minimum radius of a particle in pixels
 */
#define _MIN_RADIUS 20

/**
 * @brief Minimum RGB color value (0-255)
 */
#define _MIN_RGB 0

/**
 * @brief Maximum RGB color value (0-255)
 */
#define _MAX_RGB 255

/**
 * @brief Maximum mass value for particles
 */
#define _MAX_MASS 100

/**
 * @brief Minimum mass value for particles
 */
#define _MIN_MASS 10

/**
 * @brief Maximum initial velocity component (pixels per frame)
 */
#define _MAX_VELOCITY 1

/**
 * @brief Minimum initial velocity component (pixels per frame)
 */
#define _MIN_VELOCITY -1

/**
 * @class Particles
 * @brief Represents a single particle in the physics simulation
 *
 * The Particles class manages individual particles, handling their physical properties,
 * movement, collision detection, and rendering. Each particle has properties such as
 * position, velocity, mass, and radius.
 */
class Particles
{
private:
    sf::CircleShape _circle; ///< Shape representation of the particle
    sf::Vector2f _velocity;  ///< Current velocity vector of the particle
    float _mass;             ///< Mass of the particle

    /**
     * @brief Sets the initial coordinates of the particle based on mouse input
     * @param event SFML event containing mouse position data
     */
    void setCoordinates(const sf::Event &event);

    /**
     * @brief Assigns a random color to the particle
     */
    void setRandomColor();

    /**
     * @brief Sets a random radius for the particle between _MIN_RADIUS and _MAX_RADIUS
     */
    void setRandomRadius();

    /**
     * @brief Assigns random initial velocity components to the particle
     */
    void setRandomVelocity();

    /**
     * @brief Sets a random mass for the particle between _MIN_MASS and _MAX_MASS
     */
    void setRandomMass();

    /**
     * @brief Checks and handles particle collision with window boundaries
     */
    void checkBounds();

    /**
     * @brief Calculates new velocity after collision with another particle
     * @param other Reference to the particle being collided with
     */
    void calculatePrimeVelocity(Particles &other);

public:
    /**
     * @brief Constructs a new particle
     * @param event SFML event containing initial position data
     */
    Particles(const sf::Event &event);

    /**
     * @brief Destructor for the Particles class
     */
    ~Particles();

    /**
     * @brief Renders the particle to the specified window
     * @param window Reference to the SFML render window
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Updates the particle's position and handles boundary collisions
     */
    void update();

    /**
     * @brief Detects and handles collisions with other particles
     * @param other Reference to another particle to check collision with
     */
    void detectCollision(Particles &other);

    /**
     * @brief Gets the center position of a particle
     * @param obj Reference to the particle whose center position is needed
     * @return Vector containing the center coordinates of the particle
     */
    sf::Vector2f getCenterPosition(const Particles &obj) const;
};

#endif // PARTICLES_H