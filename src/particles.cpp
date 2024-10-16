#include "particles.h"

Particles::Particles(float x, float y)
{
    circle.setRadius(20);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(x, y);
}

Particles::~Particles() {}

void Particles::draw(sf::RenderWindow &window)
{
    window.draw(circle);
}
