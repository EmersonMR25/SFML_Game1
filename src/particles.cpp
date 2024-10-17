#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    setCoordinates(event);
    setRadius();
    this->circle.setFillColor(sf::Color::Red);
}

Particles::~Particles() {}

void Particles::draw(sf::RenderWindow &window)
{
    window.draw(this->circle);
}

void Particles::setCoordinates(const sf::Event &event)
{
    // check if LM is pressed bc in Mac both of them are connected
    std::cout << "the right button was pressed" << std::endl;
    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
    this->circle.setPosition(static_cast<float>(event.mouseButton.x - 20.0f), static_cast<float>(event.mouseButton.y - 20.f));
}

void Particles::setRadius()
{
    // Create a random device and seed the random engine
    std::random_device rd;  // Non-deterministic random device (used to seed the generator)
    std::mt19937 gen(rd()); // Mersenne Twister engine initialized with seed

    // Define a uniform integer distribution from 20 to 50
    std::uniform_int_distribution<> distr(20, 50);
    this->circle.setRadius(static_cast<float>(distr(gen)));
}