#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    // Initialize random seed
    setRandomRadius();
    setCoordinates(event);
    setRandomColor();
    this->_mass = 50.0f;
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
    this->_centerPostion = sf::Vector2f(_circle.getPosition().x + _circle.getRadius(),
                                        _circle.getPosition().y + _circle.getRadius());
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

void Particles::detectCollision(const Particles &other)
{
    // Calculate the distance between the two particles
    float xDistance = abs(_centerPostion.x - other._centerPostion.x);
    float yDistance = abs(_centerPostion.y - other._centerPostion.y);
    // Calculate the distance between // i.r hypotenuse
    float hypotenuseDistance = sqrt(xDistance * xDistance + yDistance * yDistance);
    // Check if the particles are close enough to collide
    if (hypotenuseDistance < (_circle.getRadius() + other._circle.getRadius()))
    {
        calculatePrimeVelocity(other);
    }
}

void Particles::calculatePrimeVelocity(const Particles &other)
{
    // Calculate the difference in position and velocity
    sf::Vector2f deltaPos = other._circle.getPosition() - _circle.getPosition();
    sf::Vector2f deltaVel = other._velocity - _velocity;

    // Calculate the distance squared between the two particles (|x2 - x1|^2)
    float distanceSquared = deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y;

    // Check if distance squared is not zero to avoid division by zero
    if (distanceSquared == 0.0f)
        return;

    // Calculate the scalar part of the formula (2 * m2 / (m1 + m2)) * ((v2 - v1) • (x2 - x1)) / |x2 - x1|^2
    float massFactor = (2 * other._mass) / (_mass + other._mass);
    float dotProduct = (deltaVel.x * deltaPos.x + deltaVel.y * deltaPos.y);
    float scalar = massFactor * (dotProduct / distanceSquared);

    // Update the velocity components (v1')
    _velocity.x += scalar * deltaPos.x;
    _velocity.y += scalar * deltaPos.y;
}