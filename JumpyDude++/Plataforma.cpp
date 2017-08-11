#include "Plataforma.hpp"

double Plataforma::vel = 0;
int Plataforma::espacamento = 0;
// Talvez a gente possa fazer as plataformas terem uma altura constante tamb�m

Plataforma::Plataforma() {}

// Int newComprimento e int w n�o s�o redundantes?
Plataforma::Plataforma(SDLObject* sdl, int x, int y, int w, int h) {
    comprimento = w;
    pos.x = x;
    pos.y = y;
    pos.w = w;
    pos.h = h;
    sdlobj = sdl;
    textura = sdl->texturaPlat;
}

// N�o � certo desalocar a textura, porque a� as pr�ximas plataformas n�o v�o ter acesso a textura.
// Ela j� � desalocada no SDLObject.
Plataforma::~Plataforma() {
    SDL_DestroyTexture(textura);
    textura = NULL;
}

void Plataforma::setTextura(SDL_Texture* newTextura) {
    textura = newTextura;
}

void Plataforma::updatePlatInicial() {
    pos.x-=vel;
}

void Plataforma::update(Plataforma* platAnterior) {
    if(pos.x < -(comprimento + espacamento)) {
        pos.x = platAnterior->pos.x + comprimento + espacamento;
        pos.y = alturaAleatoria();
    }

    pos.x-=vel;
}

int Plataforma::alturaAleatoria() {
    return (rand() % ((sdlobj->JANELA_ALTURA/2) + 1) + (sdlobj->JANELA_ALTURA)/4);
}

int Plataforma::getComprimento() {
    return comprimento;
}

int Plataforma::getEspacamento() {
    return espacamento;
}

// N�o tem que ajustar o w tamb�m quando coloca o comprimento?
void Plataforma::setComprimento(int newComprimento) {
    comprimento = newComprimento;
}

double Plataforma::getVel() {
    return vel;
}

void Plataforma::setVel(double newVel) {
    vel = newVel;
}

void Plataforma::setEspacamento(int i) {
    espacamento = i;
}

void Plataforma::setSDLObject(SDLObject* sdl) {
    sdlobj = sdl;
    textura = sdl->texturaPlat;
}

void Plataforma::renderizar() {
    SDL_Rect draw;

    draw.x = pos.x - 10;
    draw.y = pos.y - 15;
    draw.w = pos.w + 20;
    draw.h = pos.h + 30;

    SDL_RenderCopy(sdlobj->renderer, textura, NULL, &draw);
}
