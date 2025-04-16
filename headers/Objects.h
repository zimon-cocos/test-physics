#pragma once

struct Box
{
    sf::RectangleShape shape;
    float crossArea {0}; //square meters, cross sectional area of cube which is actually a square
    float Cd {1.05}; //drag coefficient
    float mass {5};//kg
    float velocity {0};//m/s
    float terminalV {0};


    Box(float x, float y, float width)
    {
        shape.setPosition({x,y});
        shape.setSize({width,width});
        shape.setFillColor(sf::Color::Blue);
        crossArea = width*width;
    }
};
