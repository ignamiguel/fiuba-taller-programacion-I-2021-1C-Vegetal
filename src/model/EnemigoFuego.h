#pragma once
#include "Entidad.h"

class EnemigoFuego : public Entidad
{
public:
    EnemigoFuego(punto_t pos, int direccion, float min, float max);
    void mover();
    dimensiones_t dimensions() const;
private:
    float velX;
    float min, max;
};