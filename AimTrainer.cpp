#include "aimTrainer.h"

// global variables
int windowWidth = 800, windowHeight = 600, FRAMERATE = 60;
sf::Color PINK(241, 195, 208);

// get a random coor inside the window
sf::Vector2f getRandomCoor(int width, int height, float diameter) {
    std::random_device rd;  // get seed
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distributionX(0, width - diameter);
    float rand_x = static_cast<float>(distributionX(gen));
    std::uniform_int_distribution<int> distributionY(150, height - diameter);
    float rand_y = static_cast<float>(distributionY(gen));
    return sf::Vector2f(rand_x, rand_y);
}

// Calculate the distance between the coor mouse was clicked & the center of the circle
float calculateDist(sf::Vector2f center, sf::Event::MouseButtonEvent mouse) {
    return sqrt(pow((center.x - mouse.x), 2) + pow((center.y - mouse.y), 2));
}

// check if the button is clicked
bool clicked(sf::Vector2f pos, sf::Vector2f size, sf::Event::MouseButtonEvent mouse) {
    return ((mouse.x >= pos.x) && (mouse.x <= (pos.x + size.x)) &&
        (mouse.y >= pos.y) && (mouse.y <= (pos.y + size.y)));
}

int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Aim Trainer");
    window.setFramerateLimit(FRAMERATE);


    // font
    sf::Font font8Bits;
    if (!font8Bits.loadFromFile("C:\\Users\\Felicity\\source\\repos\\AimTrainer\\8-bit-operator\\8bitOperatorPlus8-Regular.ttf")) {
        return -1;
    }

    float radius = 20.f;
    float d = 0.0;
    int total = 0, hit = 0;

    // initialization
    sf::Event event;
    Scene currScene = Scene::MainMenu;

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
    std::string score = " " + std::to_string(hit) + " / " + std::to_string(total);
    TEXT scoreText = TEXT(PINK, font8Bits, sf::Vector2f(windowWidth / 2 - 60, 15), score); // score
    TEXT mmText = TEXT(sf::Color::White, font8Bits, sf::Vector2f(windowWidth / 2 - 80, 100), "Main Menu"); // Main Menu
    TEXT playText = TEXT(sf::Color::White, font8Bits, sf::Vector2f(windowWidth / 2 - 35, windowHeight / 2 - 55 ), "Play"); // Play
    TEXT diffText = TEXT(sf::Color::White, font8Bits, sf::Vector2f(windowWidth / 2 - 75, windowHeight / 2 + 30), "Difficulty"); // Difficulty
    TEXT easyText = TEXT(sf::Color::White, font8Bits, sf::Vector2f(windowWidth / 2 - 40, windowHeight / 2 - 80), "Easy"); // Easy
    TEXT hardText = TEXT(sf::Color::White, font8Bits, sf::Vector2f(windowWidth / 2 - 40, windowHeight / 2 + 15), "Hard"); // Hard

    // buttons
    BUTTON playButton = BUTTON(PINK, sf::Vector2f(300, 70), sf::Vector2f(windowWidth/2 - 150, windowHeight / 2 - 70));
    BUTTON diffButton = BUTTON(PINK, sf::Vector2f(300, 70), sf::Vector2f(windowWidth/2 - 150, windowHeight / 2 + 20));
    BUTTON easyButton = BUTTON(PINK, sf::Vector2f(300, 75), sf::Vector2f(windowWidth/2 - 150, windowHeight / 2 - 100 ));
    BUTTON hardButton = BUTTON(PINK, sf::Vector2f(300, 75), sf::Vector2f(windowWidth/2 - 150, windowHeight / 2 ));

    while (window.isOpen())
    {
        // while there are still events happening
        while (window.pollEvent(event))
        {
            switch (event.type) {
                // mouse pressed
            case sf::Event::MouseButtonPressed:
                switch (currScene) {
                case Scene::MainMenu:
                    std::cout << "In main menu\n";
                    switch (event.type) {
                        // window closed
                    case sf::Event::Closed:
                        window.close();
                        break;
                        // key pressed
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            // get coor of clicked place
                            std::cout << "Left Mouse Button is pressed at x: " << event.mouseButton.x <<
                                " y: " << event.mouseButton.y << std::endl;
                            if (clicked(diffButton.getPos(), diffButton.getSize(), event.mouseButton)) {
                                std::cout << "Difficulty Button Clicked\n";
                                currScene = Scene::Difficulty;
                            }
                            else if (clicked(playButton.getPos(), playButton.getSize(), event.mouseButton)) {
                                std::cout << "Play Button Clicked\n";
                                currScene = Scene::Game;
                            }
                        }
                        break;
                    default:
                        break;
                    }
                    break;

                case Scene::Difficulty:
                    switch (event.type) {
                        // window closed
                    case sf::Event::Closed:
                        window.close();
                        break;
                        // HERE:: go back to main menu after a click
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {

                            if (clicked(easyButton.getPos(), easyButton.getSize(), event.mouseButton)) {

                                radius = 40.f;
                                cir.setRadius(radius);
                                cir.setPosition(newTargetPos);
                                oldTargetPos = newTargetPos;
                                newTargetPos = getRandomCoor(windowWidth, windowHeight, 2 * radius);
                                targetCen = sf::Vector2f(cir.getPosition().x + radius, cir.getPosition().y + radius);
                            }
                            else if (clicked(hardButton.getPos(), hardButton.getSize(), event.mouseButton)) {

                                radius = 20.f;
                                cir.setRadius(radius);
                                cir.setPosition(newTargetPos);
                                oldTargetPos = newTargetPos;
                                newTargetPos = getRandomCoor(windowWidth, windowHeight, 2 * radius);
                                targetCen = sf::Vector2f(cir.getPosition().x + radius, cir.getPosition().y + radius);
                            }


                        }
                        currScene = Scene::MainMenu;
                        break;

                    default:
                        break;
                    }
                    break;
                case Scene::Game:
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
                                (newTargetPos.x < (oldTargetPos.x - radius * 2) || (newTargetPos.x > (oldTargetPos.x + radius * 2)))
                                ))
                            {
                                newTargetPos = getRandomCoor(windowWidth, windowHeight, radius * 2);
                                std::cout << "\nNew center is x: " << targetCen.x << " y: " << targetCen.y << std::endl;
                            }

                            cir.setPosition(newTargetPos);
                            oldTargetPos = newTargetPos;
                            newTargetPos = getRandomCoor(windowWidth, windowHeight, radius * 2);
                            targetCen = sf::Vector2f(cir.getPosition().x + radius, cir.getPosition().y + radius);

                        }

                        // update the text
                        score = " " + std::to_string(hit) + " / " + std::to_string(total);
                        scoreText.setNewString(score);
                    }
                    break;
                default:
                    break;
                }
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
        case Scene::MainMenu:
            window.draw(mmText.text);
            window.draw(playButton.button);
            window.draw(diffButton.button);
            window.draw(diffText.text);
            window.draw(playText.text);
            break;
        case Scene::Difficulty:
            window.draw(easyButton.button);
            window.draw(hardButton.button);
            window.draw(easyText.text);
            window.draw(hardText.text);
            break;
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
