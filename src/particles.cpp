#include "particles.h"

Particles::Particles(sf::RenderWindow &window, const sf::Event &event)
{
    circle.setFillColor(this->getColor());
    circle.setRadius(this->getRadius());
    circle.setPosition(this->getPosition(event));
    window.draw(this->circle);
} // Particles::Particles()

Particles::~Particles()
{
} // Particles::~Particles()

sf::Vector2f Particles::getPosition(const sf::Event &event)
{
    return sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
} // Particles::getPosition()

float Particles::getRadius()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<float> dist(5.0f, 20.0f);
    return dist(rng);
} // Particles::getRadius()

sf::Color Particles::getColor()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, 255);
    return sf::Color(dist(rng), dist(rng), dist(rng));
} // Particles::getColor()
