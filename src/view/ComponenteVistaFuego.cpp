#include <string>
#include "ComponenteVistaFuego.h"
#include "../utils/window.hpp"
#include "../logger.h"

const std::string IMG_FUEGO = "res/Fuego.png";
#define TIEMPO_POR_FRAME 3
#define CANT_FRAMES 4

SDL_Texture* ComponenteVistaFuego::texture = NULL;
int ComponenteVistaFuego::tiempo, ComponenteVistaFuego::totalFuegos, ComponenteVistaFuego::fueActualizado = 0;

ComponenteVistaFuego::ComponenteVistaFuego(int x, int y, double resize, SDL_Renderer* renderer) {
    if (texture == NULL) {
        this->renderer = renderer;
        SDL_Surface* surface = IMG_Load("res/Fuego.png");
        if (surface == NULL) {
            logger::Logger::getInstance().logError("Image not found: " + IMG_FUEGO);
            logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        rectSrc.y = 0;
        rectSrc.w = ANCHO_FUEGO;
        rectSrc.h = ALTO_FUEGO;
    }

    rectDst.x = round(x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);
    rectDst.w = round(resize * ANCHO_FUEGO * ANCHO_PANTALLA / ANCHO_NIVEL);
    rectDst.h = round(resize * ALTO_FUEGO * ALTO_PANTALLA / ALTO_NIVEL);

    totalFuegos++;
}

void ComponenteVistaFuego::mostrar(Uint32 frames) {
    tiempo = (tiempo + (!fueActualizado) * frames) % (TIEMPO_POR_FRAME * CANT_FRAMES);
    rectSrc.x = (tiempo / TIEMPO_POR_FRAME) * SPRITE_INDEX;
    fueActualizado = (fueActualizado + 1) % totalFuegos;

    SDL_RenderCopy(renderer, texture, &rectSrc, &rectDst);
}