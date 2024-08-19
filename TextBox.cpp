#include "TextBox.hpp"

TextBox::TextBox() {
    editing = false;
    first_edit = false;
    return_clear = false;  
    text.setFont(font);

    setString("");
    setCharacterSize(10); 

    setTextColor(sf::Color::White);
    setBackgroundColor(sf::Color(128, 128, 128));
    rect.setOutlineColor(sf::Color(128, 128, 128));
}

TextBox::TextBox(sf::Vector2f size, bool return_clear) {
    this->size = size;
    rect = sf::RectangleShape(size);
    editing = false;
    first_edit = false;
    this->return_clear = return_clear;
    text.setFont(font);

    setString("");
    setCharacterSize(10); 

    setTextColor(sf::Color::White);
    setBackgroundColor(sf::Color(128, 128, 128));
    rect.setOutlineColor(sf::Color(128, 128, 128));
}

TextBox::TextBox(sf::Vector2f size, std::string textstr, bool return_clear) {
    this->size = size;
    rect = sf::RectangleShape(size);
    editing = false;
    first_edit = false;
    this->return_clear = return_clear;
    text.setFont(font);
    this->setFont("/System/Library/Fonts/monaco.ttf");

    setString(textstr);
    setCharacterSize(10);

    setTextColor(sf::Color::White);
    setBackgroundColor(sf::Color(128, 128, 128));
    rect.setOutlineColor(sf::Color(128, 128, 128));
}

TextBox::TextBox(sf::Vector2f size, std::string textstr, std::string fontstr, bool return_clear) {
    this->size = size;
    rect = sf::RectangleShape(size);
    editing = false;
    first_edit = false;
    this->return_clear = return_clear;
    text.setFont(font);

    setString(textstr);
    setCharacterSize(10); 

    setFont(static_cast<sf::String>(fontstr));

    setTextColor(sf::Color::White);
    setBackgroundColor(sf::Color(128, 128, 128));
    rect.setOutlineColor(sf::Color(128, 128, 128));
}

sf::Vector2f TextBox::getPosition() {
    return position; 
} 

sf::Vector2f TextBox::getSize() {
    return size;
}

sf::Rect<float> TextBox::getGlobalBounds() const {
    return sf::Rect<float>(position, size);
}

void TextBox::setPosition(sf::Vector2f position) {
    this->position = position;
    rect.setPosition(position);

    centerText();
}

void TextBox::setSize(sf::Vector2f size) {
    // -- Sets size of TextBox --
    this->size = size;
    rect.setSize(size);

    centerText();
}

void TextBox::setFont(std::string font) {
    if(!this->font.loadFromFile(font)) {
        std::cout << "Font failed to load\n";
        exit(1);
    }
    centerText();
}

void TextBox::setCharacterSize(int size) {
    text.setCharacterSize(size);
    centerText();
}

void TextBox::setString(sf::String str) {
    text.setString(str);
    centerText();
}

void TextBox::setTextColor(sf::Color color) {
    text.setFillColor(color);
}

void TextBox::setBackgroundColor(sf::Color color) {
    rect.setFillColor(color);
}

void TextBox::ClickEvent(sf::Vector2f mouse_pos) {    
    // Text box click
    if(getGlobalBounds().contains(mouse_pos))  {
        if(!first_edit) {
            setString("");
            first_edit = true;
        }

        if(!editing) {
            editing = true;
            rect.setOutlineThickness(0.8);
        }
    } else { 
        if(editing) {
            editing = false;
            rect.setOutlineThickness(0);
        }
    }
}

void TextBox::TextEnteredEvent(sf::Event event) {   
    if(editing) {
        if(return_clear) {
            if(event.text.unicode != 8 && event.text.unicode != 10) {
                string += event.text.unicode;
            setString(string);
            }
        } else {
            if(event.text.unicode != 8) {
            string += event.text.unicode;
            setString(string);
            }
        }
        
    }
}

void TextBox::KeyPressedEvent(sf::Event event) {
    if(editing) {
        if(event.key.code == sf::Keyboard::Backspace) {
            if(string.getSize() > 0) {
                string.erase(string.getSize() - 1);
                setString(string);
            }
        } 

        if(return_clear) {
            if(event.key.code == sf::Keyboard::Return) {
                if(string.getSize() > 0) {
                    std::cout << static_cast<std::string>(string) << std::endl;
                    string = "";
                    setString(string);
                }
            }
        }
    }
}

void TextBox::centerText() {
    sf::Rect<float> textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(rect.getPosition() + rect.getSize() / 2.0f);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const sf::RenderWindow* window = static_cast<const sf::RenderWindow*>(&target);
    if(window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::Vector2f worldPos = window->mapPixelToCoords(mousePos);

        sf::Rect<float> bounds = getTransform().transformRect(rect.getGlobalBounds());

        if(bounds.contains(worldPos)) {
            target.draw(rect, states);
        } else if(editing) {
            target.draw(rect, states);
        }
    } else {
        std::cout << "Hover detect failed\n";
        exit(1);
    }

    target.draw(text, states);
}