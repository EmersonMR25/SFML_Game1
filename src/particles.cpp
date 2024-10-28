#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    // Initialize random seed
    setRandomRadius();
    setCoordinates(event);
    setRandomColor();
    this->_weight;
    this->_velocity;
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
    this->_circle.setPosition(static_cast<float>(event.mouseButton.x - _circle.getRadius()),
                              static_cast<float>(event.mouseButton.y - _circle.getRadius()));
}

void Particles::setRandomRadius()
{
    // Random device and generator as class members
    std::random_device rd;  // Non-deterministic random device (used to seed the generator)
    std::mt19937 gen(rd()); // Mersenne Twister engine (initialized in the constructor)
    std::uniform_int_distribution<> distr(_MIN_RADIUS, _MAX_RADIUS);
    this->_circle.setRadius(static_cast<float>(distr(gen)));
}

void Particles::setRandomColor()
{
    // Random device and generator as class members
    std::random_device rd;  // Non-deterministic random device (used to seed the generator)
    std::mt19937 gen(rd()); // Mersenne Twister engine (initialized in the constructor)
    std::uniform_int_distribution<> distr(_MIN_RGB, _MAX_RGB);
    this->_circle.setFillColor(sf::Color(distr(gen), distr(gen), distr(gen)));
}

void Particles::update()
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
    _velocity.y += _GRAVITY_ACCELERATION * 1.0f;
    // Move the particle according to its velocity
    _circle.move(_velocity * 1.0f);
}