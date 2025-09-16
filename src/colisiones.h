#pragma once

#include <glm/vec2.hpp>

struct Rectangulo
{
    glm::vec2 anchoAlto;
    glm::vec2 centerPosition;
};

bool ColisionRectangular(const Rectangulo& r1, const Rectangulo& r2);
