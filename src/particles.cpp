#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    // Initialize random seed
    setRandomRadius();
    setCoordinates(event);
    setRandomColor();
    this->_mass = 0;
    this->_velocity = sf::Vector2f(1.0f, 1.0f);
    this->_centerPostion = sf::Vector2f(_circle.getPosition().x + _circle.getRadius(),
                                        _circle.getPosition().y + _circle.getRadius());
}

Particles::~Particles() {}

void Particles::draw(sf::RenderWindow &window)
{
    window.draw(this->_circle);
}

void Particles::setCoordinates(const sf::Event &event)
{
    std::cout << "The mouse button was pressed" << std::endl;
    std::cout << "Mouse x: " << event.mouseButton.x << std::endl;
    std::cout << "Mouse y: " << event.mouseButton.y << std::endl;
    float yCoordinates = event.mouseButton.y;
    float xCoordinates = event.mouseButton.x;
    if (xCoordinates - _circle.getRadius() < 0)
    {
        xCoordinates = 0.0f + _circle.getRadius();
    }
    if (xCoordinates + _circle.getRadius() > _WIDTH)
    {
        xCoordinates = _WIDTH - _circle.getRadius();
    }
    if (yCoordinates - _circle.getRadius() < 0)
    {
        yCoordinates = 0.0f + _circle.getRadius();
    }
    if (yCoordinates + _circle.getRadius() > _HEIGHT)
    {
        yCoordinates = _HEIGHT - _circle.getRadius();
    }
    this->_circle.setPosition(xCoordinates - _circle.getRadius(), yCoordinates - _circle.getRadius());
}

void Particles::setRandomRadius()
{
    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> distr(_MIN_RADIUS, _MAX_RADIUS);
    this->_circle.setRadius(static_cast<float>(distr(gen)));
}

void Particles::setRandomColor()
{
    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> distr(_MIN_RGB, _MAX_RGB);
    this->_circle.setFillColor(sf::Color(distr(gen), distr(gen), distr(gen)));
}

void Particles::update()
{
    // Check the bounds of the particle relative to the screen
    checkBounds();
    // Move the particle according to its velocity
    _circle.move(_velocity);
}

void Particles::checkBounds()
{
    // Check the bounds of the particle relative to the screen
    if (_circle.getPosition().x < 0 || _circle.getPosition().x + (2 * _circle.getRadius()) > _WIDTH)
    {
        _velocity.x *= -1;
    }
    if (_circle.getPosition().y < 0 || _circle.getPosition().y + (2 * _circle.getRadius()) > _HEIGHT)
    {
        _velocity.y *= -1;
    }
}