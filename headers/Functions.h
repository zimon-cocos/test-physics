#pragma once

float getTerminalVelocity(Box& box)
{
    return sqrt((2*box.mass*g)/(airDensity*box.crossArea*box.Cd));
}

float getFallVelocity(Box& box,float dt)
{
    return box.velocity + g*dt;
}
