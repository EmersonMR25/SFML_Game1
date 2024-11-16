#include "particles.h"

Particles::Particles(const sf::Event &event)
{
    setRandomRadius();
    setCoordinates(event);
    setRandomColor();
    setRandomMass();
    setRandomVelocity();
    setRandomVelocity();
} // Particles::Particles()

Particles::~Particles() {} // Particles::~Particles()

void Particles::draw(sf::RenderWindow &window)
{
    window.draw(this->_circle);
} // Particles::draw()

void Particles::setCoordinates(const sf::Event &event)
{
    std::cout << "The mouse button was pressed" << std::endl;
    std::cout << "Mouse x: " << event.mouseButton.x << std::endl;
    std::cout << "Mouse y: " << event.mouseButton.y << std::endl;

    float radius = _circle.getRadius();
    float xCoordinates = std::clamp(static_cast<float>(event.mouseButton.x), radius, static_cast<float>(_WIDTH) - radius);
    float yCoordinates = std::clamp(static_cast<float>(event.mouseButton.y), radius, static_cast<float>(_HEIGHT) - radius);

    this->_circle.setPosition(xCoordinates - radius, yCoordinates - radius);
} // Particles::setCoordinates()

void Particles::setRandomRadius()
{
    srand(time(0));
    this->_circle.setRadius(static_cast<float>(_MIN_RADIUS + (rand() % (_MAX_RADIUS - _MIN_RADIUS + 1))));
} // Particles::setRandomRadius()

void Particles::setRandomColor()
{
    srand(time(0));
    this->_circle.setFillColor(sf::Color(static_cast<float>(_MIN_RGB + (rand() % (_MAX_RGB - _MIN_RGB + 1))),
                                         static_cast<float>(_MIN_RGB + (rand() % (_MAX_RGB - _MIN_RGB + 1))),
                                         static_cast<float>(_MIN_RGB + (rand() % (_MAX_RGB - _MIN_RGB + 1)))));
} // Particles::setRandomColor()

void Particles::setRandomMass()
{
    srand(time(0));
    this->_mass = static_cast<float>(_MIN_MASS + (rand() % (_MAX_MASS - _MIN_MASS + 1)));
} // Particles::setRandomMass()

void Particles::setRandomVelocity()
{
    srand(time(0));
    this->_velocity = sf::Vector2f(static_cast<float>(_MIN_VELOCITY + (rand() % (_MAX_VELOCITY - _MIN_VELOCITY + 1))),
                                   static_cast<float>(_MIN_VELOCITY + (rand() % (_MAX_VELOCITY - _MIN_VELOCITY + 1))));
} // Particles::setRandomVelocity()

void Particles::update()
{
    checkBounds();
    _circle.move(_velocity);
} // Particles::update()

void Particles::checkBounds()
{
    if (_circle.getPosition().x < 0 || _circle.getPosition().x + (2 * _circle.getRadius()) > _WIDTH)
    {
        _velocity.x *= -1;
    }
    if (_circle.getPosition().y < 0 || _circle.getPosition().y + (2 * _circle.getRadius()) > _HEIGHT)
    {
        _velocity.y *= -1;
    }
} // Particles::checkBounds()

void Particles::detectCollision(Particles &other)
{
    this->calculatePrimeVelocity(other);
} // Particles::detectCollision()

/**
 * @brief Calculates and applies velocity changes for two colliding particles in a 2D elastic collision simulation
 *
 * This function implements elastic collision physics between two circular particles in 2D space.
 * It handles both the collision detection and resolution, including:
 * 1. Overlap prevention (particle separation)
 * 2. Velocity calculation using conservation of momentum and energy
 * 3. Application of resulting velocities to both particles
 *
 * The calculation follows these steps:
 * 1. Calculate impact vector between particle centers
 * 2. Check for collision using radii sum
 * 3. Resolve particle overlap if detected
 * 4. Calculate new velocities using elastic collision formulas
 *
 * Physical Principles:
 * - Conserves total momentum and kinetic energy (elastic collision)
 * - Uses impulse-based collision resolution
 * - Accounts for different particle masses
 *
 * Mathematical Formula Used:
 * v1' = v1 + (2*m2/(m1+m2)) * <v2-v1,n>/<n,n> * n
 * v2' = v2 - (2*m1/(m1+m2)) * <v2-v1,n>/<n,n> * n
 * where:
 * - v1, v2 are initial velocities
 * - v1', v2' are final velocities
 * - m1, m2 are masses
 * - n is the normal vector (impact direction)
 * - <,> denotes dot product
 *
 * @param other Reference to the other particle involved in the collision
 *
 * @note This function modifies both the current particle's and the other particle's:
 *       - Position (to resolve overlap)
 *       - Velocity (to apply collision physics)
 *
 * @warning The function assumes:
 *          - Particles are perfectly circular
 *          - Collisions are perfectly elastic
 *          - No external forces during collision
 *          - Valid mass values (non-zero, positive)
 */
void Particles::calculatePrimeVelocity(Particles &other)
{
    sf::Vector2f impactVector = getCenterPosition(other) - getCenterPosition(*this);
    float distance = std::sqrt(impactVector.x * impactVector.x + impactVector.y * impactVector.y);

    if (distance < _circle.getRadius() + other._circle.getRadius())
    {
        // Push the particles out so that they are not overlapping
        float overlap = distance - (_circle.getRadius() + other._circle.getRadius());
        sf::Vector2f dir = impactVector;
        dir.x /= distance;
        dir.y /= distance;
        dir *= overlap * 0.5f;
        _circle.move(dir);
        other._circle.move(-dir);

        // Correct the distance
        distance = _circle.getRadius() + other._circle.getRadius();
        impactVector.x /= distance;
        impactVector.y /= distance;
        impactVector *= distance;

        float mSum = _mass + other._mass;
        sf::Vector2f vDiff = other._velocity - _velocity;

        // Particle A (this)
        float num = vDiff.x * impactVector.x + vDiff.y * impactVector.y;
        float den = mSum * distance * distance;
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
} // Particles::calculatePrimeVelocity()

sf::Vector2f Particles::getCenterPosition(const Particles &obj) const
{
    return sf::Vector2f(obj._circle.getPosition().x + obj._circle.getRadius(),
                        obj._circle.getPosition().y + obj._circle.getRadius());
} // Particles::getCenterPosition()