#include "colisiones.h"

bool ColisionRectangular(const Rectangulo &r1, const Rectangulo &r2)
{
    const float r1Left = r1.centerPosition.x - (r1.anchoAlto.x / 2.f);
    const float r1Right = r1.centerPosition.x + (r1.anchoAlto.x / 2.f);
    const float r1Top = r1.centerPosition.y - (r1.anchoAlto.y / 2.f);
    const float r1Bottom = r1.centerPosition.y + (r1.anchoAlto.y / 2.f);

    const float r2Left = r2.centerPosition.x - (r2.anchoAlto.x / 2.f);
    const float r2Right = r2.centerPosition.x + (r2.anchoAlto.x / 2.f);
    const float r2Top = r2.centerPosition.y - (r2.anchoAlto.y / 2.f);
    const float r2Bottom = r2.centerPosition.y + (r2.anchoAlto.y / 2.f);

    return !(r1Left > r2Right || r1Right < r2Left || r1Bottom < r2Top || r1Top > r2Bottom);
}