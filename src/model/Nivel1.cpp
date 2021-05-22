#include "Nivel1.h"
#include "Fuego.h"
#include "PlataformaMovil.h"
#include "Peach.h"
#include "DonkeyKong.h"
#include "Polea.h"
#include "../utils/ Constants.hpp"

using namespace std;

Nivel1::Nivel1(SDL_Renderer* renderer) {
    this->compVista = new ComponenteVistaNivel1(renderer, rutaImagen);
}

void Nivel1::actualizarNivel() {
    std::list<Entidad*>::iterator it;
    for (it = objetos.begin(); it != objetos.end(); ++it) (*it)->mover();
}

void Nivel1::actualizarVista(Uint32 frames) {
    compVista->mostrar(&objetos, frames);
}

void Nivel1::agregarObjeto(Entidad* objeto) {
    objetos.push_front(objeto);
}

list<Entidad*>* Nivel1::getObjetos() {
    return &objetos;
}

void Nivel1::setFondo(std::string rutaImagen) {
    compVista->setFondo(rutaImagen);
}

void Nivel1::inicializarObjetos(SDL_Renderer* renderer) {
    agregarObjeto(new PlataformaMovil(0, 0, renderer));
    agregarObjeto(new PlataformaMovil(1, 0, renderer));
    agregarObjeto(new PlataformaMovil(2, 0, renderer));

    agregarObjeto(new PlataformaMovil(0, 1, renderer));
    agregarObjeto(new PlataformaMovil(1, 1, renderer));
    agregarObjeto(new PlataformaMovil(2, 1, renderer));

    agregarObjeto(new PlataformaMovil(0, 2, renderer));
    agregarObjeto(new PlataformaMovil(1, 2, renderer));
    agregarObjeto(new PlataformaMovil(2, 2, renderer));

    agregarObjeto(new PlataformaMovil(0, 3, renderer));
    agregarObjeto(new PlataformaMovil(1, 3, renderer));
    agregarObjeto(new PlataformaMovil(2, 3, renderer));

    agregarObjeto(new Fuego(N1_POSX_FUEGO1, N1_POSY_FUEGO, 1, renderer));
    agregarObjeto(new Fuego(N1_POSX_FUEGO2, N1_POSY_FUEGO, 1, renderer));
    agregarObjeto(new Fuego(N1_POSX_FUEGO3, N1_POSY_FUEGO, 1, renderer));
    agregarObjeto(new Fuego(N1_POSX_FUEGO4, N1_POSY_FUEGO, 1, renderer));

    agregarObjeto(new Polea(N1_POSX1_POLEA, N1_POSY1_POLEA, 0, renderer));
    agregarObjeto(new Polea(N1_POSX2_POLEA, N1_POSY1_POLEA, 1, renderer));
    agregarObjeto(new Polea(N1_POSX1_POLEA, N1_POSY2_POLEA, 0, renderer));
    agregarObjeto(new Polea(N1_POSX2_POLEA, N1_POSY2_POLEA, 1, renderer));

    agregarObjeto(new Peach(renderer));
    agregarObjeto(new DonkeyKong(renderer));
}