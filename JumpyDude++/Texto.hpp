#ifndef TEXTO_HPP_INCLUDED
#define TEXTO_HPP_INCLUDED

#include "SDLObject.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Texto {
private:
    SDL_Rect box;
    SDLObject* sdlobj;
    TTF_Font* fonte;

public:
    SDL_Texture* textura;

    Texto(SDLObject* sdl, string arquivo, int textSize, string texto, SDL_Color cor);
    ~Texto();

    void alterText(string texto, SDL_Color cor);

    int getAltura();
    int getComprimento();
};

#endif // TEXTO_HPP_INCLUDED
