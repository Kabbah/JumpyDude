#ifndef PLATAFORMA_HPP_INCLUDED
#define PLATAFORMA_HPP_INCLUDED

#include "SDLObject.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cstdlib>

class Player; // Declara��o antecipada

class Plataforma {
private:
    SDLObject* sdlobj;
    int comprimento;
    static double vel;
    static int espacamento;

public:
    SDL_Texture* textura;
    SDL_Rect pos;

    Plataforma();
    Plataforma(SDLObject* sdl, int x, int y, int w, int h);
    ~Plataforma();

    // Retorna true se o Player est� sobre a plataforma referenciada, e o faz parar na plataforma.
    // Retorna false em caso contr�rio.
    friend bool sobrePlataforma(Player &p, Plataforma &plat);

    // Retorna true se o Player estava sobre uma plataforma, n�o pulou e caiu. GG EZ LEARN 2 JUMP
    friend bool foraPlataforma(Player &p, Plataforma &plat);

    void setTextura(SDL_Texture* newTextura);
    void updatePlatInicial();
    void update(Plataforma* platAnterior);
    int alturaAleatoria();

    double getVel();
    int getComprimento();
    int getEspacamento();

    void setComprimento(int newComprimento);
    void setVel(double newVel);
    void setEspacamento(int i);

    void setSDLObject(SDLObject* sdl);

    void renderizar();
};

#endif // PLATAFORMA_HPP_INCLUDED
