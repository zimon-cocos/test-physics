#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "headers/ConstantsAndVariables.h"
#include "headers/Objects.h"
#include "headers/Random.h"
#include "headers/Functions.h"
#include <vector>


int main()

{
    int score {};
    sf::RenderWindow window (sf::VideoMode({width,height}),"Tutorial");
    window.setFramerateLimit(fps);


    sf::CircleShape circle(30.0f);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition({300.0f,300.0f});


    std::vector<Box> boxes;

    sf::Clock clock;
    float dt {0};

    while(window.isOpen())
        {
        sf::Time timeElapsed = clock.getElapsedTime();
        dt = timeElapsed.asSeconds()*timeSpeed;
        dtSinceSpawn +=dt;

        while(const std::optional event = window.pollEvent()){

        if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        else if(const auto*keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }


        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {

                auto mousePos = sf::Mouse::getPosition(window);
                auto transMousePos = window.mapPixelToCoords(mousePos);
                if(dtSinceSpawn>0.2)
                {
                    boxes.emplace_back(transMousePos.x,transMousePos.y,20.0f);
                    boxes.back().terminalV = getTerminalVelocity(boxes.back());
                    std::cout << "Terminal velocity of object is " << boxes.back().terminalV << '\n';
                    dtSinceSpawn = 0;
                }

            }

        circle.setFillColor(sf::Color::Green);
        if(boxes.size()>0)
        {
            if(boxes.back().velocity<boxes.back().terminalV)
            {
                boxes.back().velocity = getFallVelocity(boxes.back(),dt);

            }
            std::cout << "The velocity of the box is: " << boxes.back().velocity << '\n';

            boxes.back().shape.move({0.0f,1.0f*boxes.back().velocity});
        }






        //Render
        window.clear(sf::Color::White);

        //DRAWING
        //window->draw(sprite);
        clock.restart();
        window.draw(circle);
        for(int i {0}; i<boxes.size();++i)
            {
                window.draw(boxes[i].shape);
            }
        window.display();
    }

    //delete window;

}


