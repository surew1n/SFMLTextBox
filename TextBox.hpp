#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

class TextBox : public sf::Drawable, public sf::Transformable {
public:
    TextBox();
    TextBox(sf::Vector2f size, bool return_clear = false);
    TextBox(sf::Vector2f size, std::string textstr, bool return_clear = false);
    TextBox(sf::Vector2f size, std::string textstr, std::string fontstr, bool return_clear = false);

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    std::string getString();
    sf::Rect<float> getGlobalBounds() const;

    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setFont(std::string font);
    void setCharacterSize(int size);
    void setString(sf::String str);

    void setTextColor(sf::Color color);
    void setBackgroundColor(sf::Color color);

    void ClickEvent(sf::Vector2f mouse_pos);
    void TextEnteredEvent(sf::Event event);
    void KeyPressedEvent(sf::Event event);

    void centerText();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Font font;
    sf::String string;
    sf::Text text;
    sf::RectangleShape rect;

    sf::Vector2f size;
    sf::Vector2f position;

    bool editing;
    bool first_edit;

    bool return_clear;
};