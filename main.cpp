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
    sf::RenderWindow window (sf::VideoMode({width,height}),"Tutorial");
    window.setFramerateLimit(fps);

    std::vector<Box> boxes;

    sf::Clock clock;
    float dt {0};

    sf::RectangleShape floor;
    floor.setSize({600.0f,30.0f});
    floor.setPosition({0.0f,550.0f});
    floor.setFillColor(sf::Color::Red);

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
                    boxes.emplace_back(transMousePos.x,transMousePos.y,30.0f);
                    boxes.back().boxId = boxId;
                    ++boxId;
                    boxes.back().terminalV = getTerminalVelocity(boxes.back());
                    std::cout << "Terminal velocity of object is " << boxes.back().terminalV << '\n';
                    std::cout << "Id is " << boxes.back().boxId << '\n';
                    dtSinceSpawn = 0;
                }

            }

        for(auto& boxi : boxes)
        {
            if(!boxi.onFloor)
            {
                if(floor.getGlobalBounds().findIntersection(boxi.shape.getGlobalBounds()))
                {
                    boxi.terminalV = 0;
                    boxi.velocity = 0;
                    boxi.onFloor = true;
                }


                if(boxi.velocity<boxi.terminalV)
                {
                    boxi.velocity = getFallVelocity(boxi,dt);
                }
                boxi.shape.move({0.0f,1.0f*boxi.velocity});
            }
        }



        for(int i {0}; i<boxes.size();++i)
            {
                for(int j {0}; j<boxes.size();++j)
                {

                    if(boxes[i].shape.getGlobalBounds().findIntersection(boxes[j].shape.getGlobalBounds()) && boxes[i].boxId != boxes[j].boxId)
                    {
                        if(boxes[i].onFloor || boxes[j].onFloor)
                        {
                            boxes[i].terminalV = 0;
                            boxes[i].velocity = 0;
                            boxes[j].terminalV = 0;
                            boxes[j].velocity = 0;

                            boxes[i].onFloor = true;
                            boxes[j].onFloor = true;


                            boxes[i].isStatic = true;
                            boxes[j].isStatic = true;


                        }
                    }
                }
            }

        //Render
        window.clear(sf::Color::White);

        //DRAWING
        clock.restart();
        for(auto& box : boxes) window.draw(box.shape);
        window.draw(floor);
        window.display();
    }
}


