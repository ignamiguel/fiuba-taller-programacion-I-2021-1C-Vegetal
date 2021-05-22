#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "model/Entidad.h"
#include "model/Nivel1.h"
#include "model/Nivel2.h"
#include "model/Barril.h"
#include "model/Fuego.h"
#include "model/PlataformaMovil.h"
#include "model/EnemigoFuego.h"
#include "model/Peach.h"
#include "model/Mario.hpp"
#include "model/DonkeyKong.h"
#include "configuration.hpp"
#include "logger.h"
#include "utils/window.hpp"
#include "utils/ Constants.hpp"
#include "controller/MarioController.h"

const std::string NOMBRE_JUEGO = "Donkey Kong 2 Jumpman Returns";

int main(void)
{
    auto configuration = configuration::Configuration("archivo.json");
    auto log_level = configuration.getLogLevel();
    logger::Logger::getInstance().setDebugLevel(log_level);

    logger::Logger::getInstance().logNewGame();

    // TODO: Handle errors...
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(NOMBRE_JUEGO.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                                ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_Init(SDL_INIT_VIDEO);
    bool terminarPrograma = false;

    SDL_Event event;

    Nivel1 n1(renderer);
    Nivel2 n2(renderer);

    Mario mario(N1_MARIO_POS_X, N1_MARIO_POS_Y,
                MARIO_ANCHO, MARIO_ALTO);
    n1.agregarObjeto(&mario);

    logger::Logger::getInstance().logInformation("Log level = " + log_level);

    auto enemies = configuration.getEnemies();
    for (auto enemy: enemies) {
        if(enemy.getType().compare("Fuego") == 0) {
            for(unsigned int i = 0; i < enemy.getQuantity(); i++) {
                int posX = rand() % (ANCHO_PANTALLA - 32);
                int posY = rand() % (ALTO_PANTALLA - 32);
                int numRandom = (rand() % 2);
                int velX;
                if(numRandom == 0)
                    velX = -1;
                else
                    velX = 1;
                n1.agregarObjeto(new EnemigoFuego(posX, posY, velX, renderer));
            }
        }
        logger::Logger::getInstance().logDebug("Enemy type: " + enemy.getType());
        logger::Logger::getInstance().logDebug("Enemy quantity: " + std::to_string(enemy.getQuantity()));
    }
    
    auto stages = configuration.getStages();
    for (unsigned int i = 0; i < stages.size(); ++i) {
        if(i == 0) 
        {
            logger::Logger::getInstance().logDebug("Stage 1 background img: " + stages[i].getBackgrounds()[0]);
            n1.setFondo(stages[i].getBackgrounds()[0]);
        }
        else if(i == 1) {
            logger::Logger::getInstance().logDebug("Stage 2 background img: " + stages[i].getBackgrounds()[0]);
            n2.setBackground(stages[i].getBackgrounds()[0]);
        }
    }

    n1.inicializarObjetos(renderer);
    // http://gameprogrammingpatterns.com/game-loop.html#play-catch-up
    Uint32 previous, current, elapsed, lag, frames;
    previous = SDL_GetTicks();
    lag = 0;
    while(!terminarPrograma) {
        current = SDL_GetTicks();
        elapsed = current - previous;
        previous = current;
        lag += elapsed;

        // Handle event
        while(SDL_PollEvent(&event)) {
            terminarPrograma = (event.type == SDL_QUIT);
            
            // Cambio de nivel
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_TAB) {
                logger::Logger::getInstance().logInformation("End of Level 1");
                goto nivel2;
            }

            // Handle input for Mario
            marioController.handleEvent(&event);
        }

        // Update Model
        frames = 0;
        while (lag >= MS_PER_UPDATE) {
            n1.actualizarNivel();
            lag -= MS_PER_UPDATE;
            frames++;
        }

        // Update View and render
        if (frames) {
            SDL_RenderClear(renderer);
            n1.actualizarVista(frames);
            SDL_RenderPresent(renderer);
        }
    }

    nivel2:
    n2.addElement(&mario);
    n2.initialize();
    SDL_RenderClear(renderer);
    logger::Logger::getInstance().logInformation("Level 2 starts");
        
    mario = Mario(N2_MARIO_POS_X, 
                  N2_MARIO_POS_Y,
                  MARIO_ANCHO,
                  MARIO_ALTO);
    
    previous = SDL_GetTicks();
    lag = 0;
    while(!terminarPrograma) {
        while( SDL_PollEvent(&event) != 0 ) {
            terminarPrograma = (event.type == SDL_QUIT);

            if( event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_TAB) {
                logger::Logger::getInstance().logInformation("End of Level 2");
                goto fin;
            }

            // Handle input for mario
            mario.handleEvent( event );
        }

        int inicio = SDL_GetTicks();

        SDL_RenderClear(renderer);
        n2.updateView();
        SDL_RenderPresent(renderer);

        int fin = SDL_GetTicks();
        if((fin - inicio) < 1000/FRAMES_POR_SEG)
        SDL_Delay((1000/FRAMES_POR_SEG) - (fin - inicio));
    };

    fin:
    logger::Logger::getInstance().logInformation("Game over");

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
} 
