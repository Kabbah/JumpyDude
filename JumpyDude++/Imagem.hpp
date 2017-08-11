#ifndef IMAGEM_HPP_INCLUDED
#define IMAGEM_HPP_INCLUDED

#include "SDLObject.hpp"

class Imagem {
private:
    SDLObject* sdlobj;

public:
    SDL_Rect box;
    SDL_Texture* textura;

    Imagem(SDLObject* sdl, string caminho);

    ~Imagem();

    void setCorner(int posx, int posy);

    void renderizar();
};

#endif // IMAGEM_HPP_INCLUDED
