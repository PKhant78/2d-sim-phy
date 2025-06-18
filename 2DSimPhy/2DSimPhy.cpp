#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

typedef unsigned int uint_32t;

int main()
{
    sf::RenderWindow window;
    uint_32t width = 800;
    uint_32t height = 600;
    window.create(sf::VideoMode({ width,height }), "My window");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setOrigin({ 50.f, 50.f });

    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x < width && mousePos.y >= 0 && mousePos.y < height)
            {
                shape.setPosition(static_cast<sf::Vector2f>(mousePos));
                window.draw(shape);
               
            }
           
        }
        window.display();
    }
}
 

