#pragma once
#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/ComponenteVistaNivel1.h"
#include "Entidad.h"
#include "NivelBase.h"

class Nivel1 : public NivelBase 
{
    public:
        std::string rutaImagen = "res/default.png";

        Nivel1(SDL_Renderer* renderer, bool useDefaultConfig);
        void actualizarNivel();
        void agregarObjeto(Entidad* objeto);
        void setFondo(std::string rutaImagen);
        void inicializarObjetos();
        std::list<Entidad*>* getObjetos();

    private:
        ComponenteVistaNivel1* compVista = NULL;
        std::list<Entidad*> objetos;

        void actualizarVista();
        void actualizarPosicionesObjetos();
};