#include "aimTrainer.h"

// global variables
int windowWidth = 800, windowHeight = 600, FRAMERATE = 60;
sf::Color PINK(241, 195, 208);

// get a random coor inside the window
sf::Vector2f getRandomCoor(int width, int height, float diameter) {
    std::random_device rd;  // get seed
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distributionX(1, width - diameter);
    float rand_x = static_cast<float>(distributionX(gen));
    std::uniform_int_distribution<int> distributionY(500, height - diameter);
    float rand_y = static_cast<float>(distributionY(gen));
    return sf::Vector2f(rand_x, rand_y);
}

// Calculate the distance between the coor mouse was clicked & the center of the circle
float calculateDist(sf::Vector2f center, sf::Event::MouseButtonEvent mouse) {
    return sqrt(pow((center.x - mouse.x), 2) + pow((center.y - mouse.y), 2));
}

// check if the button is clicked
bool clicked(sf::Vector2f pos, sf::Vector2f size, sf::Event::MouseButtonEvent mouse) {
    // position is at right left
    return ((mouse.x >= pos.x) && (mouse.x <= (pos.x + size.x)) &&
        (mouse.y >= pos.y) && (mouse.y <= (pos.y + size.y)));

}

int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Aim Trainer");
    window.setFramerateLimit(FRAMERATE);
    

    // font
    sf::Font fontDigitalTech;
    if (!fontDigitalTech.loadFromFile("C:\\Users\\Felicity\\source\\repos\\AimTrainer\\digit_tech\\DigitTech9-Regular.ttf")) {
        return -1;
    }

    float radius = 20.f;
    float d = 0.0;
    int total = 0, hit = 0;

    // initialization
    sf::Event event;
    Scene currScene = Scene::Game;

    sf::Vector2f oldTargetPos = getRandomCoor(windowWidth, windowHeight, radius * 2);
    sf::Vector2f newTargetPos;
    
    // targets
    sf::CircleShape cir;
    cir.setFillColor(PINK);
    cir.setPosition(oldTargetPos);
    cir.setRadius(radius);

    // get position & set position are for the top left corner
    sf::Vector2f targetCen = sf::Vector2f(cir.getPosition().x + radius, cir.getPosition().y + radius);

    // texts
    // score
    std::string score = " " + std::to_string(hit) + " / " + std::to_string(total);
    TEXT scoreText = TEXT(PINK,fontDigitalTech, sf::Vector2f(windowWidth / 2 - 60, 15), score);


    float buttonCenX = windowWidth / 2 - 100;
    // buttons
    BUTTON playButton = BUTTON(PINK, sf::Vector2f(300, 70), sf::Vector2f(buttonCenX, windowHeight / 2));
    BUTTON diffButton = BUTTON(PINK, sf::Vector2f(300, 70), sf::Vector2f(buttonCenX, windowHeight / 2 + 100));
    BUTTON easyButton = BUTTON(PINK, sf::Vector2f(150, 75), sf::Vector2f(buttonCenX, windowHeight / 2));
    BUTTON hardButton = BUTTON(PINK, sf::Vector2f(150, 75), sf::Vector2f(buttonCenX, windowHeight / 2 + 100));

    while (window.isOpen()) {
        std::cout << "window opened" << std::endl;
        // while there are still events happening
        while (window.pollEvent(event)) { 
             if (currScene == Scene::Game) {
                
                switch (event.type) {
                    // mouse pressed
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        total++;
                        // get coor of clicked place
                        std::cout << "Left Mouse Button is pressed at x: " << event.mouseButton.x <<
                            " y: " << event.mouseButton.y << std::endl;
                        d = calculateDist(targetCen, event.mouseButton);
                        std::cout << "Distance to center: " << d << std::endl;
                        if (d <= radius) {
                            std::cout << "\nInside the circle\n";
                            hit++;

                            // make sure the new pos is not overlapping with old one
                            while (!(
                                (newTargetPos.x < (oldTargetPos.x - radius* 2) || (newTargetPos.x > (oldTargetPos.x + radius* 2)))
                                ))
                            {
                                newTargetPos = getRandomCoor(windowWidth, windowHeight, radius* 2);
                                std::cout << "\nNew center is x: " << targetCen.x << " y: " << targetCen.y << std::endl;
                            }

                            cir.setPosition(newTargetPos);
                            oldTargetPos = newTargetPos;
                            newTargetPos = getRandomCoor(windowWidth, windowHeight, radius * 2);
                            targetCen = sf::Vector2f(cir.getPosition().x + radius, cir.getPosition().y + radius);

                        }

                        // update the text
                        score = " " + std::to_string(hit) + " / " + std::to_string(total);
                        // scoreText.setNewString(score);
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
                 
                 window.draw(cir);
                 window.draw(scoreText.text);

                 break;
             default:
                 break;
             }
            
            window.display();

        }
    }

}
