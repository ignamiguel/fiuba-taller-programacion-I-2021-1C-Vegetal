#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Nivel2.h"
#include "Peach.h"
#include "DonkeyKong.h"
#include "Fuego.h"
#include "FireBarrel.h"
#include "DefaultConfig.h"

using namespace std;

Nivel2::Nivel2 (SDL_Renderer* window_renderer, bool useDefaultConfig) {
    this->tickLastBarrel = 0;
    this->renderer = window_renderer;
    this->useDefaultConfig = useDefaultConfig;
}

void Nivel2::loadBackground () {
    this->background_surface = IMG_Load(backgroundImage.c_str());
    if(this->background_surface == NULL) {
        this->background_surface = IMG_Load(DEFAULT_IMAGE.c_str());
    }
    this->background_texture = SDL_CreateTextureFromSurface(this->renderer, this->background_surface);
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, NULL);
}

void Nivel2::updateBackground () {
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, NULL);
}

void Nivel2::loadElements () {
    Peach* girl = new Peach(314, 76, 40, 55);
    this->elements.push_front(girl);

    DonkeyKong* donkey = new DonkeyKong(129, 115, 100, 82);
    this->elements.push_front(donkey);

    Fuego* fire = new Fuego(10, 530, 30, 30);
    this->elements.push_front(fire);

    FireBarrel* barrel = new FireBarrel(10, 560, 30, 30);
    this->elements.push_front(barrel);

    if(this->getDefaultConfigFlag())
    {
        DefaultConfig* defaultConfig = new DefaultConfig(290, 40, 200, 20);
        this->elements.push_front(defaultConfig);
    }
}

void Nivel2::addElement (Entidad* element) {
    this->elements.push_front(element);
}

void Nivel2::updateElements () {
    list<Entidad*>::iterator it;
    for (it = this->elements.begin(); it != this->elements.end(); ++it){
        (*it)->mover();
        (*it)->mostrar(this->renderer);
    }
}


void Nivel2::addBarrel () {
    int posX = rand() % 750 + 10;
    this->barrels.push_back(Barril(posX, 150, 0, 10));
}

void Nivel2::updateBarrels () {
    for (uint i = 0; i < this->barrels.size(); i++) {
        try {
            this->barrels.at(i).mover();
            this->barrels.at(i).mostrar(this->renderer);
        }
        catch (exception& e) {
            this->barrels.erase(this->barrels.begin()+i);
        }
    } 
}
void Nivel2::initialize() {
    this->loadBackground();
    this->loadElements();
}

void Nivel2::updateView () {
    
    if (SDL_GetTicks() - this->tickLastBarrel > 1500) {
        this->tickLastBarrel = SDL_GetTicks();
        this->addBarrel();
    }

    this->updateBackground();
    this->updateElements();
    this->updateBarrels();
}
void Nivel2::setBackground(std::string background) {
    this->backgroundImage = background;
}
