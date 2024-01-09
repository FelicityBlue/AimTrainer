
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

enum class Scene {
    MainMenu,
    Difficulty,
    Game
};

class BUTTON {
public:
    sf::RectangleShape button;
    // getters
    sf::Vector2f getSize() {
        return button.getSize();
    }
    sf::Vector2f getPos() {
        return button.getPosition();
    }
    sf::Color getColor() {
        return button.getFillColor();
    }
    // setters
    void setNewSize(sf::Vector2f newSize) {
        button.setSize(newSize);
    }
    void setNewPos(sf::Vector2f newPos) {
        button.setPosition(newPos.x, newPos.y);
    }
    void setNewColor(sf::Color newColor) {
        button.setFillColor(newColor);
    }
    // create
    BUTTON(sf::Color color, sf::Vector2f size, sf::Vector2f pos) {
        button.setFillColor(color);
        button.setPosition(pos.x, pos.y);
        button.setSize(size);
    }
};



class TEXT {
public:
    sf::Text text;

    // getters
    sf::Font getFont() {
        return *text.getFont();
    }
    sf::Vector2f getPos() {
        return text.getPosition();
    }
    sf::Color getColor() {
        return text.getFillColor();
    }
    std::string getString() {
        return text.getString();
    }
    // setters
    void setNewFont(sf::Font& newFont) {
        text.setFont(newFont);
    }
    void setNewPos(sf::Vector2f newPos) {
        text.setPosition(newPos.x, newPos.y);
    }
    void setNewColor(sf::Color newColor) {
        text.setFillColor(newColor);
    }
    void setNewString(std::string newString) {
        text.setString(newString);
    }
    // create
    TEXT(sf::Color color, sf::Font& font, sf::Vector2f pos, std::string string) {

        text.setFillColor(color);
        text.setFont(font);
        text.setPosition(pos.x, pos.y);
        text.setString(string);
    }
};
