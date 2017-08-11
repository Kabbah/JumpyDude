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

    bool noChao; // Indica se o personagem est� no ch�o ou n�o.

    int pontuacao; // Pontua��o
    double vely; // Velocidade vertical

    SDLObject* sdlobj; // SDLObject criado no main

    SDL_Texture* sprite;
    SDL_Texture* spritePulo;
    SDL_Rect clip[4];

    /* CONSTANTES */
    static const int X; // Posi��o horizontal inicial
    static const int Y_INIT; // Posi��o vertical inicial
    static const int PLAYER_WIDTH; // Dimens�es do Player
    static const int PLAYER_HEIGHT;
    static const double VEL_PULO; // Velocidade inicial do pulo
    static const double GRAV; // Acelera��o da gravidade

    static const string ARQUIVO_IMG;
    static const string ARQUIVO_IMG_PULO;

public:
    SDL_Rect r; // Ret�ngulo da hitbox
    Plataforma* plataforma; // Plataforma em que o Player est� em cima.

    // Construtor
    Player(SDLObject* sdl);

    // Altera o nome do Player
    void setNome(string s);

    // Altera a pontua��o do Player
    void setPontuacao(int i);

    // Retorna o nome do Player
    string getNome();

    // Retorna o Y inicial
    int getYInit();

    // Retorna a pontua��o
    int getPontuacao();

    // Retorna se o player est� no ch�o
    bool isNoChao();

    // Inicia a velocidade Y quando o jogador aperta a tecla UP
    void iniciaPulo();

    // Se o jogador soltar a tecla UP cedo, o pulo ser� menor.
    void iniciaQueda();

    // Retorna true se o Player est� sobre a plataforma referenciada, e o faz parar na plataforma.
    // Retorna false em caso contr�rio.
    friend bool sobrePlataforma(Player &p, Plataforma &plat);

    // Retorna true se o Player estava sobre uma plataforma, n�o pulou e caiu. GG EZ LEARN 2 JUMP
    friend bool foraPlataforma(Player &p, Plataforma &plat);

    // Atualiza a posi��o da hitbox
    void atualiza();

    // Renderiza
    void renderizar();
};

#endif // PLAYER_HPP_INCLUDED

