#pragma once

#include "Entidad.h"
#include "../utils/estadoMario.h"
#include "mario/MarioState.h"

#define SPACE 128
#define UP 8
#define DOWN 4
#define LEFT 2
#define RIGHT 1

class MarioState;

class Mario : public Entidad 
{
    public: 
        Mario();
        void setStartPos(float x, float y);
        void mover();
        void setEstado(char controls);
        estadoMario_t getEstado();

    private:
        MarioState* state;
        // float velX;
        float velEnSuelo;
        // float velY;
        char estado;
        char estadoEnSuelo;

        // void trepar(char up, char down); TODO
        void correr(char left, char right);
        void saltar(char jump);
};