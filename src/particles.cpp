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

void Particles::detectCollision(Particles &other)
{

    // Calculate the distance between the two particles
    sf::Vector2f deltaPos = getCenterPosition(*this) - getCenterPosition(other);
    float distance = sqrt(deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y);

    // Check if the particles are close enough to collide
    if (distance < (_circle.getRadius() + other._circle.getRadius()))
    {
        // Update the velocities of both particles
        this->calculatePrimeVelocity(other);
    }
}

void Particles::calculatePrimeVelocity(Particles &other)
{
    sf::Vector2f impactVector = getCenterPosition(other) - getCenterPosition(*this);
    float d = std::sqrt(impactVector.x * impactVector.x + impactVector.y * impactVector.y);

    if (d < _circle.getRadius() + other._circle.getRadius())
    {
        // Push the particles out so that they are not overlapping
        float overlap = d - (_circle.getRadius() + other._circle.getRadius());
        sf::Vector2f dir = impactVector;
        dir.x /= d;
        dir.y /= d;
        dir *= overlap * 0.5f;
        _circle.move(dir);
        other._circle.move(-dir);

        // Correct the distance
        d = _circle.getRadius() + other._circle.getRadius();
        impactVector.x /= d;
        impactVector.y /= d;
        impactVector *= d;

        float mSum = _mass + other._mass;
        sf::Vector2f vDiff = other._velocity - _velocity;

        // Particle A (this)
        float num = vDiff.x * impactVector.x + vDiff.y * impactVector.y;
        float den = mSum * d * d;
        sf::Vector2f deltaVA = impactVector;
        deltaVA.x *= 2.0f * other._mass * num / den;
        deltaVA.y *= 2.0f * other._mass * num / den;
        _velocity += deltaVA;

        // Particle B (other)
        sf::Vector2f deltaVB = impactVector;
        deltaVB.x *= -2.0f * _mass * num / den;
        deltaVB.y *= -2.0f * _mass * num / den;
        other._velocity += deltaVB;
    }
}

sf::Vector2f Particles::getCenterPosition(const Particles &obj) const
{
    return sf::Vector2f(obj._circle.getPosition().x + obj._circle.getRadius(),
                        obj._circle.getPosition().y + obj._circle.getRadius());
}