#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Vector2 position(100.f, 100.f); // Temporarily at the center of the window

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
        shape.setPosition(position); // Move the shape to the current mouse position

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}