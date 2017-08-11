#ifndef SDLOBJECT_HPP_INCLUDED
#define SDLOBJECT_HPP_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

enum GameState {
    JOGO,
    GAME_OVER,
    RECORDS,
    MENU,
    NOME,
    CREDITOS
};

class SDLObject {
public:
    SDL_Window* janela; // Janela do programa
    SDL_Renderer* renderer; // Renderizador
    SDL_Event evento; // Tratador de eventos
    GameState gamestate;

    SDL_Texture* texturaPlat; // Textura da plataforma

    /* CONSTANTES */
    static const int JANELA_LARGURA; // Dimensões da janela
    static const int JANELA_ALTURA;
    static const string IMG_PLATAFORMA; // Imagem da textura da plataforma

    // Construtor
    SDLObject();

    // Destrutor
    ~SDLObject(); // Destrutor

    // Inicializa o SDL e seus atributos
    bool init();

    // Finaliza o SDL e libera a memória
    void close();
};

#endif // SDLOBJECT_HPP_INCLUDED
