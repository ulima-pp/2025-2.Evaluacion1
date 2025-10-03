#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>


namespace Fisicas {
    struct Forma {};

    struct Rectangulo : public Forma
    {
        glm::vec2 anchoAlto;
        glm::vec2 centerPosition;
    };

    struct Circulo  : public Forma
    {
        glm::vec2 centerPosition;
        float radio;
    };

    class GestorColisiones
    {
        Colision* m_Colision;
        public:
            GestorColisiones();
            void SetColision(Colision& colision);
            bool Resolver(Forma& forma1, Forma& forma2);
    };

    class Colision
    {
        public:
            virtual bool Resolver(Forma& forma1, Forma& forma2) = 0;
    };

    class ColisionRectangular : public Colision
    {
        public:
            bool Resolver(Forma& forma1, Forma& forma2) override;
    };

    class ColisionCircular : public Colision
    {
        public:
            bool Resolver(Forma& forma1, Forma& forma2) override;
    };
}




