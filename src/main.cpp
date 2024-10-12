#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setVerticalSyncEnabled(true);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Vector2f position(500.f, 500.f); // Temporarily at the center of the window
    float xVelocity = 2.f; 
    float yVelocity = 2.f; 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    position = sf::Vector2f(static_cast<float>(event.mouseButton.x - 100.f), static_cast<float>(event.mouseButton.y - 100.f));
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (shape.getFillColor() == sf::Color::Green)
                {
                    shape.setFillColor(sf::Color::Red);
                }
                else
                {
                    shape.setFillColor(sf::Color::Green);
                }
            }
            
        }
        // Check for colision with the window borders
        if (shape.getPosition().x < 0.f || shape.getPosition().x > (1000.f - 200.f)) {
            xVelocity *= -1; // Reverse the direction of the x-axis movement
        } 
        if (shape.getPosition().y < 0.f || shape.getPosition().y > (1000.f - 200.f)) {
            yVelocity *= -1; // Reverse the direction of the y-axis movement
        }
        position.x += xVelocity; // Update the x-coordinate of the shape
        position.y += yVelocity; // Update the y-coordinate of the shape
        
        shape.setPosition(position); // Move the shape to the current mouse position
        
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}