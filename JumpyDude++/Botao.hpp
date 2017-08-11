#ifndef BOTAO_HPP_INCLUDED
#define BOTAO_HPP_INCLUDED

#include "SDLObject.hpp"
#include "Texto.hpp"

class Botao {
public:
    SDLObject* sdlobj;

    SDL_Color corBotao;
    SDL_Rect box;

    SDL_Rect boxTexto;
    Texto* texto;

    static const string fonte;

    Botao(SDLObject* sdl, SDL_Rect dimensao, SDL_Color cor, int textSize, string text, SDL_Color corTexto);
    ~Botao();

    void renderizar();

    bool mouseOver(int mx, int my);
};

#endif // BOTAO_HPP_INCLUDED
