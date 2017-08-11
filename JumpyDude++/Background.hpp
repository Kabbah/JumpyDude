#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include "SDLObject.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

class Background {
private:
    SDLObject* sdlobj; // Objeto SDLObject criado no main

    /* CONSTANTES */
    static const string caminho; // Caminho do arquivo

public:
    SDL_Rect srcRect;
    SDL_Texture* textura;

    Background(SDLObject* sdl);

    bool init();

    ~Background();

    void update();
};

#endif // BACKGROUND_HPP_INCLUDED
