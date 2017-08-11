#include "Player.hpp"

#define ALT_PLATAFORMAS 30

const int Player::X = 100; // Posição horizontal inicia
const int Player::Y_INIT = 250; // Posição vertical inicial
const int Player::PLAYER_WIDTH = 35; // Dimensões do Player
const int Player::PLAYER_HEIGHT = 50;
const double Player::VEL_PULO = -30; // Velocidade inicial do pulo
const double Player::GRAV = 1; // Aceleração da gravidade
const string Player::ARQUIVO_IMG = "data/Sprite.png";
const string Player::ARQUIVO_IMG_PULO = "data/Jump.png";

// Construtor
Player::Player(SDLObject* sdl) {
    // Inicializa o ponteiro para o SDLObject
    sdlobj = sdl;

    SDL_Surface* imgTemp = IMG_Load(ARQUIVO_IMG.c_str());
    if(imgTemp == NULL) {
        cout << "Falha no carregamento da imagem. Erro: " << IMG_GetError() << endl;
    }
    else {
        sprite = SDL_CreateTextureFromSurface(sdlobj->renderer, imgTemp); //Converte imagem em textura
        if(sprite == NULL) {
            cout << "Falha na criação da textura. Erro: " << IMG_GetError() << endl;
        }
        SDL_FreeSurface(imgTemp); //Libera memória da imagem antiga.
    }

    imgTemp = IMG_Load(ARQUIVO_IMG_PULO.c_str());
    if(imgTemp == NULL) {

        cout << "Falha no carregamento da imagem. Erro: " << IMG_GetError() << endl;
    }
    else {
        spritePulo = SDL_CreateTextureFromSurface(sdlobj->renderer, imgTemp); //Converte imagem em textura
        if(spritePulo == NULL) {
            cout << "Falha na criação da textura. Erro: " << IMG_GetError() << endl;
        }
        SDL_FreeSurface(imgTemp); //Libera memória da imagem antiga.
    }

    for(int i = 0; i < 4; i++) {
        clip[i] = {i*35, 0, 35, 50};
    }

    // Nome default
    nome = "Guest";

    //Pontuação
    pontuacao = 0;

    // Posições iniciais (canto superior esquerdo)
    r.x = X;
    r.y = Y_INIT;

    // Dimensões da hitbox
    r.w = PLAYER_WIDTH;
    r.h = PLAYER_HEIGHT;

    // Player inicia no chão
    noChao = true;

    // Velocidade inicial
    vely = 0;

    plataforma = 0;
}

// Altera o nome do Player
void Player::setNome(string s) {
    nome = s;
}

// Altera a pontuação do Player
void Player::setPontuacao(int i) {
    pontuacao = i;
}

// Retorna o nome do Player
string Player::getNome() {
    return nome;
}

// Retorna o Y inicial
int Player::getYInit() {
    return Y_INIT;
}

// Retorna a pontuação
int Player::getPontuacao() {
    return pontuacao;
}

bool Player::isNoChao() {
    return noChao;
}

// Dá uma velocidade inicial ao jogador quando ele aperta a tecla UP
void Player::iniciaPulo() {
    if(noChao) {
        vely = VEL_PULO;
        noChao = false;
    }
}

// Reduz a velocidade do player se ele soltar a tecla UP muito cedo
void Player::iniciaQueda() {
    if(!noChao) {
        if(vely < VEL_PULO * 13/15){
            vely = VEL_PULO / 3;
        }
        else if(vely < VEL_PULO * 11/15){
            vely = VEL_PULO * 2 / 5;
        }
        else if(vely < VEL_PULO / 2) {
            vely = VEL_PULO / 2;
        }
    }
}

// Retorna true se o Player está sobre a plataforma referenciada, e o faz parar na plataforma.
// Retorna false em caso contrário.
bool sobrePlataforma(Player &p, Plataforma &plat) {
    if(p.vely > 0) {
        if((p.r.x + p.r.w) >= plat.pos.x && p.r.x <= (plat.pos.x + plat.comprimento)) {
            if(p.r.y >= (plat.pos.y - p.r.h) && p.r.y <= (plat.pos.y - p.r.h + (plat.pos.h))) {
                p.r.y = plat.pos.y - p.r.h;
                p.vely = 0;
                p.noChao = true;
                p.plataforma = &plat;
                return true;
            }
        }
    }
    return false;
}

// Retorna true se o Player estava sobre uma plataforma, não pulou e caiu. GG EZ LEARN 2 JUMP
bool foraPlataforma(Player &p, Plataforma &plat) {
    if(&plat == 0) {
        return false;
    }
    if(p.noChao) {
        if(p.r.x > (plat.pos.x + plat.comprimento)) {
            p.noChao = false;
            return true;
        }
    }
    return false;
}

// Atualiza a posição da hitbox
void Player::atualiza() {
    vely += GRAV;

    if(vely > ALT_PLATAFORMAS){
        vely = ALT_PLATAFORMAS;
    }

    r.y += vely;
    pontuacao++;

    if(r.y > sdlobj->JANELA_ALTURA) {
        r.y = sdlobj->JANELA_ALTURA;
        vely = 0;
        noChao = true;

        sdlobj->gamestate = GAME_OVER; // E morreu
        cout << "Entrando na tela de GAME OVER..." << endl;
    }
}

void Player::renderizar() {
    if(noChao) {
        SDL_RenderCopy(sdlobj->renderer, sprite, &(clip[(pontuacao / 6) % 4]), &r);
    }
    else {
        SDL_RenderCopy(sdlobj->renderer, spritePulo, NULL, &r);
    }
}
