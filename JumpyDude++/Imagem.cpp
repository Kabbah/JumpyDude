#include "Imagem.hpp"

Imagem::Imagem(SDLObject* sdl, string caminho) {
    sdlobj = sdl;

    SDL_Surface* loadedSurface = IMG_Load(caminho.c_str()); //Carrega a imagem
    if(loadedSurface == NULL) {
        cout << "Falha no carregamento da imagem. Erro: " << IMG_GetError() << endl;
    }
    else {
        box.w = loadedSurface->w;
        box.h = loadedSurface->h;

        textura = SDL_CreateTextureFromSurface(sdlobj->renderer, loadedSurface); //Converte imagem em textura
        if(textura == NULL) {
            cout << "Falha na criação da textura. Erro: " << IMG_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface); //Libera memória da imagem antiga.
    }
}

Imagem::~Imagem() {
    SDL_DestroyTexture(textura);
}

void Imagem::setCorner(int posx, int posy) {
    box.x = posx;
    box.y = posy;
}

void Imagem::renderizar() {
    SDL_RenderCopy(sdlobj->renderer, textura, NULL, &box);
}
