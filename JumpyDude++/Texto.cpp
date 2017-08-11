#include "Texto.hpp"

Texto::Texto(SDLObject* sdl, string arquivo, int textSize, string texto, SDL_Color cor) {
    sdlobj = sdl;

    // Cria a fonte do texto
    cout << "Gerando fonte do texto..." << endl;
    fonte = TTF_OpenFont(arquivo.c_str(), textSize);
    if(fonte == NULL) {
        cout << "Falha no carregamento da fonte do texto. Erro: " << TTF_GetError() << endl;
    }

    cout << "Gerando superfície do texto..." << endl;
    SDL_Surface* surface = TTF_RenderUTF8_Solid(fonte, texto.c_str(), cor);

    if(surface == NULL) {
        cout << "Falha na geração do bloco de texto. Erro: " << TTF_GetError() << endl;
    }
    else {
        cout << "Gerando textura do texto..." << endl;
        box = {0, 0, surface->w, surface->h};

        textura = SDL_CreateTextureFromSurface(sdlobj->renderer, surface);
        if(textura == NULL) {
            cout << "Falha na conversão do texto de superfície para textura. Erro: " << SDL_GetError() << endl;
        }

        SDL_FreeSurface(surface);
    }
}

Texto::~Texto() {
    // Libera a memória da fonte
    cout << "Destruíndo fonte do texto..." << endl;
    TTF_CloseFont(fonte);
    fonte = NULL;

    // Libera a memória da textura
    cout << "Destruíndo a textura do texto..." << endl;
    SDL_DestroyTexture(textura);
    textura = NULL;
}

void Texto::alterText(string texto, SDL_Color cor) {
    // Libera a memória da textura
    SDL_DestroyTexture(textura);
    textura = NULL;

    SDL_Surface* surface = TTF_RenderUTF8_Solid(fonte, texto.c_str(), cor);

    if(surface == NULL) {
        cout << "Falha na geração do bloco de texto. Erro: " << TTF_GetError() << endl;
    }
    else {
        box = {0, 0, surface->w, surface->h};

        textura = SDL_CreateTextureFromSurface(sdlobj->renderer, surface);
        if(textura == NULL) {
            cout << "Falha na conversão do texto de superfície para textura. Erro: " << SDL_GetError() << endl;
        }

        SDL_FreeSurface(surface);
    }
}

int Texto::getAltura() {
    return box.h;
}

int Texto::getComprimento() {
    return box.w;
}
