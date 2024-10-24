#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    // Initialize random seed
    setRadius();
    setCoordinates(event);
    setColor();
    velocity = sf::Vector2f(1.0f, 0.0f);
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
    // Move the particle according to its velocity
    circle.move(velocity);
}