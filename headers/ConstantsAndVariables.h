#pragma once

uint16_t  width {600};
uint16_t height {600};
int fps {60};
float timeSpeed {1};
float dtSinceSpawn {0};


//physics
//1 pixel, or 1 coordinate point = one meter

constexpr float airDensity {1.204}; // kg/m^3
constexpr float g {9.81}; // m/s^2
