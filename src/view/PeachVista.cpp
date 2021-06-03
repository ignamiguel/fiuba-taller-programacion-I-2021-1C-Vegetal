#include <string>
#include <SDL2/SDL_image.h>
#include "PeachVista.h"
#include "../logger.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

const std::string IMG_PEACH = "res/Peach.png";

SDL_Texture *PeachVista::texture = NULL;

PeachVista::PeachVista(SDL_Renderer* renderer)
: EntidadEstaticaVista() {
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load(IMG_PEACH.c_str());
    if (surface == NULL) {
        logger::Logger::getInstance().logError("Image not found: " + IMG_PEACH);
        logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
        surface = IMG_Load(IMG_DEFAULT.c_str());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    rect.x = round(PEACH_POSX * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rect.y = round(PEACH_POSY * ALTO_PANTALLA / (float)ALTO_NIVEL);
    rect.w = round(PEACH_ANCHO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rect.h = round(PEACH_ALTO * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void PeachVista::mostrar() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}