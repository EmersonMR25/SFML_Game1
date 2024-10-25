#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    // Initialize random seed
    setRadius();
    setCoordinates(event);
    setColor();
    weight = static_cast<float>(circle.getRadius()) / 100.0f;       // Weight is proportional to the radius
    velocity = sf::Vector2f(0.0f, (weight * GRAVITY_ACCELERATION)); // Velocity
}

Particles::~Particles() {}

void Particles::draw(sf::RenderWindow &window)
{
    window.draw(this->circle);
}

void Particles::setCoordinates(const sf::Event &event)
{
    // Check if the left mouse button is pressed
    std::cout << "The mouse button was pressed" << std::endl;
    std::cout << "Mouse x: " << event.mouseButton.x << std::endl;
    std::cout << "Mouse y: " << event.mouseButton.y << std::endl;
    this->circle.setPosition(static_cast<float>(event.mouseButton.x - circle.getRadius()),
                             static_cast<float>(event.mouseButton.y - circle.getRadius()));
}

void Particles::setRadius()
{
    // Random device and generator as class members
    std::random_device rd;  // Non-deterministic random device (used to seed the generator)
    std::mt19937 gen(rd()); // Mersenne Twister engine (initialized in the constructor)

    // Define a uniform integer distribution from 20 to 50
    std::uniform_int_distribution<> distr(20, 50);
    this->circle.setRadius(static_cast<float>(distr(gen)));
}

void Particles::setColor()
{
    // Random device and generator as class members
    std::random_device rd;  // Non-deterministic random device (used to seed the generator)
    std::mt19937 gen(rd()); // Mersenne Twister engine (initialized in the constructor)

    // Define a uniform integer distribution from 0 to 255 for RGB values
    std::uniform_int_distribution<> distr(0, 255);
    this->circle.setFillColor(sf::Color(distr(gen), distr(gen), distr(gen)));
}

void Particles::update()
{
    // Check the bounds of the particle relative to the screen
    if (circle.getPosition().x < 0 || circle.getPosition().x + (2 * circle.getRadius()) > _WIDTH)
    {
        velocity.x *= -1;
    }
    if (circle.getPosition().y < 0 || circle.getPosition().y + (2 * circle.getRadius()) > _HEIGHT)
    {
        velocity.y *= -1;
    }
    velocity.y += GRAVITY_ACCELERATION * 1.0f;
    // Move the particle according to its velocity
    circle.move(velocity * 1.0f);
}