#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    setRandomRadius();
    setCoordinates(event);
    setRandomColor();
    setRandomMass();
    setRandomVelocity();
    setRandomVelocity();
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

    float radius = _circle.getRadius();
    float xCoordinates = std::clamp(static_cast<float>(event.mouseButton.x), radius, static_cast<float>(_WIDTH) - radius);
    float yCoordinates = std::clamp(static_cast<float>(event.mouseButton.y), radius, static_cast<float>(_HEIGHT) - radius);

    this->_circle.setPosition(xCoordinates - radius, yCoordinates - radius);
}

void Particles::setRandomRadius()
{
    srand(time(0));
    this->_circle.setRadius(static_cast<float>(_MIN_RADIUS + (rand() % (_MAX_RADIUS - _MIN_RADIUS + 1))));
}

void Particles::setRandomColor()
{
    srand(time(0));
    this->_circle.setFillColor(sf::Color(static_cast<float>(_MIN_RGB + (rand() % (_MAX_RGB - _MIN_RGB + 1))),
                                         static_cast<float>(_MIN_RGB + (rand() % (_MAX_RGB - _MIN_RGB + 1))),
                                         static_cast<float>(_MIN_RGB + (rand() % (_MAX_RGB - _MIN_RGB + 1)))));
}

void Particles::setRandomMass()
{
    srand(time(0));
    this->_mass = static_cast<float>(_MIN_MASS + (rand() % (_MAX_MASS - _MIN_MASS + 1)));
}

void Particles::setRandomVelocity()
{
    srand(time(0));
    this->_velocity = sf::Vector2f(static_cast<float>(_MIN_VELOCITY + (rand() % (_MAX_VELOCITY - _MIN_VELOCITY + 1))),
                                   static_cast<float>(_MIN_VELOCITY + (rand() % (_MAX_VELOCITY - _MIN_VELOCITY + 1))));
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

// void Particles::detectCollision(Particles &other)
//{
//     // Calculate the distance between the two particles
//     sf::Vector2f deltaPos = other._centerPosition - this->_centerPosition;
//     float distance = sqrt(deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y);
//
//     // Check if the particles are close enough to collide
//     if (distance < 5 + (_circle.getRadius() + other._circle.getRadius()))
//     {
//         // Update the velocities of both particles
//         this->calculatePrimeVelocity(other);
//         other.calculatePrimeVelocity(*this); // Update the other particle as well
//     }
// }
//
// void Particles::calculatePrimeVelocity(Particles &other)
//{
//     // Calculate the difference in position and velocity
//     sf::Vector2f deltaPos = other._centerPosition - this->_centerPosition;
//     sf::Vector2f deltaVel = other._velocity - this->_velocity;
//
//     // Calculate the distance squared to avoid division by zero
//     float distanceSquared = deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y;
//     if (distanceSquared == 0.0f)
//         return;
//
//     // Scalar calculation for velocity update
//     float massFactor = (2 * other._mass) / (this->_mass + other._mass);
//     float dotProduct = (deltaVel.x * deltaPos.x + deltaVel.y * deltaPos.y);
//     float scalar = massFactor * (dotProduct / distanceSquared);
//
//     // Update the velocities for elastic collision
//     this->_velocity += scalar * deltaPos;
// }
