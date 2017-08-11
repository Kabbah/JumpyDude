#include "Background.hpp"

const string Background::caminho = "data/background.png"; // Caminho do arquivo

Background::Background(SDLObject* sdl) {
    sdlobj = sdl;

    textura = NULL;
}

bool Background::init() {
    bool exito = true;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = sdlobj->JANELA_LARGURA;
    srcRect.h = sdlobj->JANELA_ALTURA;

    SDL_Surface* loadedSurface = IMG_Load(caminho.c_str()); //Carrega a imagem
    if(loadedSurface == NULL) {
        cout << "Falha no carregamento da imagem. Erro: " << IMG_GetError() << endl;
        exito = false;
    }
    else {
        textura = SDL_CreateTextureFromSurface(sdlobj->renderer, loadedSurface); //Converte imagem em textura
        if(textura == NULL) {
            cout << "Falha na criação da textura. Erro: " << IMG_GetError() << endl;
            exito = false;
        }
        SDL_FreeSurface(loadedSurface); //Libera memória da imagem antiga.
    }

    return exito;
}

Background::~Background() {
    SDL_DestroyTexture(textura);
    textura = NULL;
}

void Background::update(){
    (srcRect.x)++;

    if((srcRect.x) >= sdlobj->JANELA_LARGURA){
        (srcRect.x) = 0;
    }
}
