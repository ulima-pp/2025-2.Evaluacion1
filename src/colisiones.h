#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>


namespace Fisicas {
    struct Forma {
        glm::vec2 centerPosition;
        glm::vec2 anchoAlto;
    };

    struct Rectangulo : public Forma
    {};

    struct Circulo  : public Forma
    {
        float radio;
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

    class GestorColisiones
    {
        Colision* m_Colision;
        public:
            GestorColisiones();
            void SetColision(Colision& colision);
            bool Resolver(Forma& forma1, Forma& forma2);
    };    
}




