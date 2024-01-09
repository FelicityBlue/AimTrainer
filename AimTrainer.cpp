
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

// global variables
int windowWidth = 800, windowHeight = 600;

enum class Scene {
    MainMenu,
    Difficulty,
    Game
};

class Button {
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
    void setSize(sf::Vector2f newSize) {
        currSize = newSize;
    }
    void setPos(sf::Vector2f newPos) {
        currPos = newPos;
    }
    void setColor(sf::Color newColor) {
        currColor = newColor;
    }
    // create
    Button (sf::Color color, sf::Vector2f size, sf::Vector2f pos) : currColor(color), currPos(pos), currSize(size) {
        button.setFillColor(color);
        button.setPosition(pos.x, pos.y);
        button.setSize(size);
    };
private:
    sf::Vector2f currSize;
    sf::Vector2f currPos;
    sf::Color currColor;
    
};

// get a random coor inside the window
sf::Vector2f getRandomCoor(int width, int height, float diameter) {
    
    std::random_device rd;  // get seed
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distributionX(1, width - diameter);
    float rand_x = static_cast<float>(distributionX(gen));
    std::uniform_int_distribution<int> distributionY(150, height - diameter);
    float rand_y = static_cast<float>(distributionY(gen));

    return sf::Vector2f(rand_x, rand_y);

}

// Calculate the distance between the coor mouse was clicked & the center of the circle
float calculateDist(sf::Vector2f center, sf::Event::MouseButtonEvent mouse) {
    return sqrt(pow((center.x - mouse.x), 2) + pow((center.y - mouse.y), 2));
}


int main()
{

    
    // create window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Aim Trainer");
    window.setFramerateLimit(60);
    sf::Event e;

    // font
    sf::Color PINK(241, 195, 208);
    sf::Font fontDigitalTech;
    if (!fontDigitalTech.loadFromFile("C:\\Users\\Felicity\\source\\repos\\AimTrainer\\digit_tech\\DigitTech9-Regular.ttf")) {
        return -1;
    }

    float radius = 20.f;
    float diameter = 2 * radius;
    float d = 0.0;
    int total = 0, hit = 0;

    // initialization
    Scene currScene = Scene::Game;

    sf::Vector2f oldPos = getRandomCoor(windowWidth, windowHeight, diameter);
    sf::Vector2f newPos;
    
    // targets
    sf::CircleShape cir;
    cir.setFillColor(PINK);
    cir.setPosition(oldPos);
    cir.setRadius(radius);

    // get position & set position are for the top left corner
    sf::Vector2f targetCen = sf::Vector2f(cir.getPosition().x + radius, cir.getPosition().y + radius);

    // texts
    // score
    sf::Text scoreText;
    scoreText.setFont(fontDigitalTech);
    scoreText.setPosition(windowWidth / 2 - 60, 15);
    std::string score = " " + std::to_string(hit) + " / " + std::to_string(total);
    scoreText.setString(score);



    while (window.isOpen()) {
        // while there are still events happening
        while (window.pollEvent(e)) { 
             if (currScene == Scene::Game) {
                
                switch (e.type) {
                    // mouse pressed
                case sf::Event::MouseButtonPressed:
                    if (e.mouseButton.button == sf::Mouse::Left) {
                        total++;
                        // get coor of clicked place
                        std::cout << "Left Mouse Button is pressed at x: " << e.mouseButton.x <<
                            " y: " << e.mouseButton.y << std::endl;
                        d = calculateDist(targetCen, e.mouseButton);
                        std::cout << "Distance to center: " << d << std::endl;
                        if (d <= radius) {
                            std::cout << "\nInside the circle\n";
                            hit++;

                            // make sure the new pos is not overlapping with old one
                            while (!(
                                (newPos.x < (oldPos.x - diameter) || (newPos.x > (oldPos.x + diameter)))
                                ))
                            {
                                newPos = getRandomCoor(windowWidth, windowHeight, diameter);
                                std::cout << "\nNew center is x: " << targetCen.x << " y: " << targetCen.y << std::endl;
                            }

                            cir.setPosition(newPos);
                            oldPos = newPos;
                            newPos = getRandomCoor(windowWidth, windowHeight, diameter);
                            targetCen = sf::Vector2f(cir.getPosition().x + radius, cir.getPosition().y + radius);

                        }

                        // update the text
                        score = " " + std::to_string(hit) + " / " + std::to_string(total);
                        scoreText.setString(score);
                    }
                    break;
                case sf::Event::KeyPressed:
                    // return to main menu
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        currScene = Scene::MainMenu;
                    }
                    break;
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                // other events
                default:
                    break;
                }
            }

             // render
             window.clear(sf::Color::Black);
             
             switch (currScene) {

             case Scene::Game:
                 window.draw(scoreText);
                 window.draw(cir);
                 break;
             default:
                 break;
             }
            
            window.display();

        }
    }

}
