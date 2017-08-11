#include "Botao.hpp"

const string Botao::fonte = "data/arial.ttf";

Botao::Botao(SDLObject* sdl, SDL_Rect dimensao, SDL_Color cor, int textSize, string text, SDL_Color corTexto) {
    sdlobj = sdl;

    box = dimensao;

    texto = new Texto(sdlobj, fonte, textSize, text, corTexto);

    boxTexto.x = box.x + (box.w - texto->getComprimento())/2;
    boxTexto.y = box.y + (box.h - texto->getAltura())/2;
    boxTexto.w = texto->getComprimento();
    boxTexto.h = texto->getAltura();

    corBotao = cor;
}

Botao::~Botao() {
    delete texto;
}

void Botao::renderizar() {
    SDL_SetRenderDrawColor(sdlobj->renderer, corBotao.r, corBotao.g, corBotao.b, 0xFF);
    SDL_RenderFillRect(sdlobj->renderer, &box);
    SDL_RenderCopy(sdlobj->renderer, texto->textura, NULL, &boxTexto);
}

bool Botao::mouseOver(int mx, int my) {
    if((mx >= box.x && mx <= box.x + box.w) && (my >= box.y && my <= box.y + box.h)) {
        return true;
    }
    return false;
}
