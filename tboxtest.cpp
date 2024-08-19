#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Window");
    
    TextBox tbox = TextBox(sf::Vector2f(400, 120), "Clears on return", true);
    tbox.setPosition(sf::Vector2f(100, 50));

    tbox.setCharacterSize(20);
    tbox.setBackgroundColor(sf::Color(128, 128, 128, 100));
    tbox.setTextColor(sf::Color::White);

    TextBox tbox2(sf::Vector2f(100,60), "Other text", false);
    tbox2.setPosition(sf::Vector2f(200, 300));

    sf::Vector2i mouse_pos;
    sf::Vector2f translated_pos;

    // Main loop that continues until the window is closed
    while(window.isOpen())
    {
        // Process events
        sf::Event event;

        while(window.pollEvent(event))
        {
            
            switch(event.type) {
                // Click
                case sf::Event::MouseButtonPressed: {
                    mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
                    translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
                    tbox.ClickEvent(translated_pos);
                    tbox2.ClickEvent(translated_pos);

                    break;
                }

                // Text typed
                case sf::Event::TextEntered: {
                    tbox.TextEnteredEvent(event);
                    tbox2.TextEnteredEvent(event);

                    break;
                }

                case sf::Event::KeyPressed: {
                    tbox.KeyPressedEvent(event);
                    tbox2.KeyPressedEvent(event);

                    break;
                }

                // Close window
                case sf::Event::Closed: {
                    window.close();

                    break;
                }

                case sf::Event::Resized: {
                    sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());
                    window.setSize(static_cast<sf::Vector2u>(size));
                    sf::View view = sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y));
                    window.setView(view);

                    break;
                }          

                // Default, we dont process other events
                default: {
                    break;
                }
            }
        }

        // Clear previous frame, draw current frame, display window output
        window.clear();
        window.draw(tbox);
        window.draw(tbox2);
        window.display();
    }

    return 0;
}