#include "SDLObject.hpp"

const int SDLObject::JANELA_LARGURA = 1200; // Dimensões da janela
const int SDLObject::JANELA_ALTURA = 600;
const string SDLObject::IMG_PLATAFORMA = "data/imgPlat.png"; // Imagem da plataforma

// Construtor
SDLObject::SDLObject() {
    janela = NULL;
    renderer = NULL;
    texturaPlat = NULL;

    gamestate = MENU;
}

// Destrutor
SDLObject::~SDLObject() {
    close();
}

// Inicializa o SDL e seus atributos
bool SDLObject::init() {
    bool exito = true;

    // Inicia o SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        cout << "Falha na inicialização do SDL. Erro: " << SDL_GetError() << endl;
        exito = false;
    }

    // Cria a janela
    cout << "Criando janela..." << endl;
    janela = SDL_CreateWindow("JumpyDude++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, JANELA_LARGURA, JANELA_ALTURA, SDL_WINDOW_SHOWN);
    if(janela == NULL) {
        cout << "Falha na criação da janela. Erro: " << SDL_GetError() << endl;
        exito = false;
    }

    // Cria o renderizador
    cout << "Criando renderizador..." << endl;
    renderer = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        cout << "Falha na criação do renderizador. Erro: " << SDL_GetError() << endl;
        exito = false;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // Inicializa a cor do renderizador

    // Inicializa o SDL_image
    cout << "Inicializando SDL_image..." << endl;
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        cout << "Falha na inicialização do SDL_image. Erro: " << IMG_GetError() << endl;
        exito = false;
    }

    // Cria a textura da plataforma
    cout << "Gerando textura das plataformas..." << endl;
    SDL_Surface* imagemPlat = IMG_Load(IMG_PLATAFORMA.c_str()); // Carrega a imagem
    if(imagemPlat == NULL) {
        cout << "Falha no carregamento da imagem da plataforma. Erro: " << IMG_GetError() << endl;
        exito = false;
    }
    else {
        texturaPlat = SDL_CreateTextureFromSurface(renderer, imagemPlat); // Converte imagem em textura
        if(texturaPlat == NULL) {
            cout << "Falha na criação da textura da plataforma. Erro: " << IMG_GetError() << endl;
            exito = false;
        }
        SDL_FreeSurface(imagemPlat); // Libera memória da imagem antiga.
    }

    // Inicia o SDL_ttf
    cout << "Inicializando SDL_ttf..." << endl;
    if(TTF_Init() == -1) {
        cout << "Falha na inicialização do SDL_ttf. Erro: " << TTF_GetError() << endl;
        exito = false;
    }

    // Inicializa o SDL_mixer
    cout << "Inicializando SDL_mixer..." << endl;
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Falha na inicialização do SDL_mixer. Erro: " << Mix_GetError() << endl;
        exito = false;
    }

    return exito;
}

// Finaliza o SDL e libera a memória
void SDLObject::close() {
    // Libera a memória da textura da plataforma
    cout << "Destruíndo textura das plataformas..." << endl;
    SDL_DestroyTexture(texturaPlat);
    texturaPlat = NULL;

    // Libera a memória do renderizador
    cout << "Destruíndo renderizador..." << endl;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    // Libera a memória da janela
    cout << "Destruíndo janela..." << endl;
    SDL_DestroyWindow(janela);
    janela = NULL;

    // Finaliza o SDL_mixer
    cout << "Finalizando SDL_mixer..." << endl;
    Mix_Quit();

    // Finaliza o SDL_ttf
    cout << "Finalizando SDL_ttf..." << endl;
    TTF_Quit();

    // Finaliza o SDL_image
    cout << "Finalizando SDL_image..." << endl;
    IMG_Quit();

    // Finaliza o SDL
    cout << "Finalizando SDL..." << endl;
    SDL_Quit();
}
