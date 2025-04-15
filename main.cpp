#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "headers/Constants.h"
#include "headers/Objects.h"
#include "headers/Random.h"
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

    float i {20};

    while(i>0)
    {
        boxes.emplace_back(Random::get(10,600),Random::get(10,600),50);
        --i;
    }

    boxes.emplace_back(300,300,50);


    while(window.isOpen())
        {


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
            }

        circle.setFillColor(sf::Color::Green);







        //Render
        window.clear(sf::Color::White);

        //DRAWING
        //window->draw(sprite);
        window.draw(circle);
        for(int i {0}; i<boxes.size();++i)
            {
                window.draw(boxes[i].shape);
            }
        window.display();
    }

    //delete window;

}


