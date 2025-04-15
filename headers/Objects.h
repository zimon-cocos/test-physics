#pragma once

struct Box
{
    sf::RectangleShape shape;

    Box(float x, float y, float width)
    {
        shape.setPosition({x,y});
        shape.setSize({width,width});
        shape.setFillColor(sf::Color::Blue);
    }
};
