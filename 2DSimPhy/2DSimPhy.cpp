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
    std::vector<sf::CircleShape> circles;
    const float gravity = 9.81f;
    float dt = 0.016f;
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool falling = false;

    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    //position of the mouse
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    //check if mouse is out of bounds
                    if (mousePos.x >= 0 && mousePos.x < width && mousePos.y >= 0 && mousePos.y < height)
                    {
                        //Make the shape
                        sf::CircleShape shape(50.f);
                        shape.setFillColor(sf::Color(100, 250, 50));
                        shape.setOrigin({ 50.f, 50.f });

                        //draw
                        shape.setPosition(static_cast<sf::Vector2f>(mousePos));
                        window.draw(shape);
                        circles.push_back(shape);
                        std::cout << "Placed!" << std::endl;
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                falling = true;
            }
        }


        if (falling == true && !circles.empty()) {
            position = circles[0].getPosition();

            if (position.y + circles[0].getRadius() < height) {
                velocity.y += gravity * dt;          
                position.y += velocity.y * dt;        
            }

            circles[0].setPosition(position);
        }

        window.clear(sf::Color::Black);

        //keep showing placed shapes
        for (const auto& circle : circles)
            window.draw(circle);
       
        // show shape while hovering
        sf::CircleShape hover(50.f);
        hover.setFillColor(sf::Color(100, 250, 50));
        hover.setOrigin({ 50.f, 50.f });

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        //draw
        hover.setPosition(static_cast<sf::Vector2f>(mousePos));
        window.draw(hover);

        window.display();
    }
   
}
