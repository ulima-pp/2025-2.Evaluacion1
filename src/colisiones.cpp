#include "colisiones.h"

Fisicas::GestorColisiones::GestorColisiones()
    :m_Colision(nullptr)
{}

void Fisicas::GestorColisiones::SetColision(Colision& colision)
{
    m_Colision = &colision;
}

bool Fisicas::GestorColisiones::Resolver(Forma& forma1, Forma& forma2)
{
    return m_Colision->Resolver(forma1, forma2);
}

bool Fisicas::ColisionRectangular::Resolver(Forma& forma1, Forma& forma2)
{
    Rectangulo& r1 = (Rectangulo&)forma1;
    Rectangulo& r2 = (Rectangulo&)forma2;

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

bool Fisicas::ColisionCircular::Resolver(Forma& forma1, Forma& forma2)
{
    Circulo& r1 = (Circulo&)forma1;
    Circulo& r2 = (Circulo&)forma2;

    auto distancia = glm::distance(r1.centerPosition, r2.centerPosition);
    return distancia <= (r1.radio + r2. radio);
}
