#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    setCoordinates(event);
    this->circle.setRadius(20);
    this->circle.setFillColor(sf::Color::Red);
}

Particles::~Particles() {}

void Particles::draw(sf::RenderWindow &window)
{
    window.draw(this->circle);
}

void Particles::setCoordinates(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        std::cout << "the right button was pressed" << std::endl;
        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
        this->circle.setPosition(static_cast<float>(event.mouseButton.x - 20.0f), static_cast<float>(event.mouseButton.y - 20.f));
    }
}