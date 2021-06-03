#pragma once

#include <SDL2/SDL.h>
#include "../utils/punto.h"

class MarioVista
{
    public:
        MarioVista(SDL_Renderer *renderer);
        void mostrar(punto_t pos, char estado);
        void setColor(int color);
        ~MarioVista();

    private:
        static SDL_Renderer *renderer;
        static SDL_Texture *texture;
        SDL_Rect srcRect;
        static SDL_Rect dstRect;
        SDL_RendererFlip flip;
        int tiempo;
        static int totalJugadores;

        void updateReposo();
        void updateCorriendo(int nextX);
        void updateSaltando(int nextX);
        void updateTrepando();
};