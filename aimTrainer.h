
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
        return currSize;
    }
    sf::Vector2f getPos() {
        return currPos;
    }
    sf::Color getColor() {
        return currColor;
    }
    // setters
    void setNewSize(sf::Vector2f newSize) {
        currSize = newSize;
        button.setSize(newSize);
    }
    void setNewPos(sf::Vector2f newPos) {
        currPos = newPos;
        button.setPosition(newPos.x, newPos.y);
    }
    void setNewColor(sf::Color newColor) {
        currColor = newColor;
        button.setFillColor(newColor);
    }
    // create
    BUTTON(sf::Color color, sf::Vector2f size, sf::Vector2f pos) : currColor(color), currPos(pos), currSize(size) {
        button.setFillColor(color);
        button.setPosition(pos.x, pos.y);
        button.setSize(size);
    };
private:
    sf::Vector2f currSize;
    sf::Vector2f currPos;
    sf::Color currColor;

};

class TEXT {
public:
    sf::Text text;
    // getters
    sf::Font getFont() {
        return currFont;
    }
    sf::Vector2f getPos() {
        return currPos;
    }
    sf::Color getColor() {
        return currColor;
    }
    std::string getString() {
        return currString;
    }
    // setters
    void setNewFont(sf::Font newFont) {
        currFont = newFont;
        text.setFont(newFont);
    }
    void setNewPos(sf::Vector2f newPos) {
        currPos = newPos;
        text.setPosition(newPos.x, newPos.y);
    }
    void setNewColor(sf::Color newColor) {
        currColor = newColor;
        text.setFillColor(newColor);
    }
    void setNewString(std::string newString) {
        currString = newString;
        text.setString(newString);
    }
    // create
    TEXT(sf::Color color, sf::Font font, sf::Vector2f pos, std::string string) : currColor(color), currPos(pos), currString(string), currFont(font) {
        text.setFillColor(color);
        text.setFont(font);
        text.setPosition(pos.x, pos.y);
        text.setString(string);
    };
    TEXT(sf::Font font, sf::Vector2f pos, std::string string) : currPos(pos), currString(string), currFont(font) {
        text.setFont(font);
        text.setPosition(pos.x, pos.y);
        text.setString(string);
    };
private:
    sf::Font currFont;
    sf::Vector2f currPos;
    std::string currString;
    sf::Color currColor = sf::Color::White;

};

