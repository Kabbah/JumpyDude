#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "SDLObject.hpp"
#include "Plataforma.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Player {
private:
    string nome; // Nome do Jogador

    bool noChao; // Indica se o personagem está no chão ou não.

    int pontuacao; // Pontuação
    double vely; // Velocidade vertical

    SDLObject* sdlobj; // SDLObject criado no main

    SDL_Texture* sprite;
    SDL_Texture* spritePulo;
    SDL_Rect clip[4];

    /* CONSTANTES */
    static const int X; // Posição horizontal inicial
    static const int Y_INIT; // Posição vertical inicial
    static const int PLAYER_WIDTH; // Dimensões do Player
    static const int PLAYER_HEIGHT;
    static const double VEL_PULO; // Velocidade inicial do pulo
    static const double GRAV; // Aceleração da gravidade

    static const string ARQUIVO_IMG;
    static const string ARQUIVO_IMG_PULO;

public:
    SDL_Rect r; // Retângulo da hitbox
    Plataforma* plataforma; // Plataforma em que o Player está em cima.

    // Construtor
    Player(SDLObject* sdl);

    // Altera o nome do Player
    void setNome(string s);

    // Altera a pontuação do Player
    void setPontuacao(int i);

    // Retorna o nome do Player
    string getNome();

    // Retorna o Y inicial
    int getYInit();

    // Retorna a pontuação
    int getPontuacao();

    // Retorna se o player está no chão
    bool isNoChao();

    // Inicia a velocidade Y quando o jogador aperta a tecla UP
    void iniciaPulo();

    // Se o jogador soltar a tecla UP cedo, o pulo será menor.
    void iniciaQueda();

    // Retorna true se o Player está sobre a plataforma referenciada, e o faz parar na plataforma.
    // Retorna false em caso contrário.
    friend bool sobrePlataforma(Player &p, Plataforma &plat);

    // Retorna true se o Player estava sobre uma plataforma, não pulou e caiu. GG EZ LEARN 2 JUMP
    friend bool foraPlataforma(Player &p, Plataforma &plat);

    // Atualiza a posição da hitbox
    void atualiza();

    // Renderiza
    void renderizar();
};

#endif // PLAYER_HPP_INCLUDED

