#include "SDLObject.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Plataforma.hpp"
#include "Texto.hpp"
#include "Record.hpp"
#include "Botao.hpp"
#include "Imagem.hpp"
#include "Musica.hpp"
#include "Soundeffect.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

#define ERRO_INIT 1

#define NUM_PLATAFORMAS 5
#define COMP_PLATAFORMAS 175
#define ALT_PLATAFORMAS 30
#define NUM_RECORDS 3

/** JumpyDude++
 * TRABALHO FINAL DE FUNDAMENTOS DE PROGRAMAÇÃO 2
 * ALUNOS:
 * Angelo Borsoi Ross (1717405)
 * Victor Barpp Gomes (1717545)
*/

int main(int argc, char* args[]) {
    // Objeto que contém partes importantes do SDL
    cout << "Criando SDLObject..." << endl;
    SDLObject sdl;

    // Inicializa o SDL
    cout << "Inicializando SDL..." << endl;
    if(!(sdl.init())) {
        cout << "Falha na inicialização do SDLObject." << endl;
        return ERRO_INIT;
    }

    cout << "Criando Player..." << endl;
    // Player
    Player player(&sdl);

    cout << "Criando Background..." << endl;
    // Plano de fundo
    Background bg(&sdl);
    if(!(bg.init())) {
        cout << "Falha na inicialização do Background." << endl;
        return ERRO_INIT;
    }

    //Criando música e efeitos sonoros
    Musica musMenu("data/Summer_Day.wav");
    Musica musJogo("data/Beachfront_Celebration.wav");
    Soundeffect soundPulo("data/Jumping.wav");
    string currentMusic = "";
    Mix_VolumeMusic(MIX_MAX_VOLUME/3);

    // Logo
    Imagem* logo;

    // Cria os records, input e organiza
    Record records[NUM_RECORDS];
    ifstream input(records[0].getArquivo().c_str());
    for(int i=0; i < NUM_RECORDS; i++){
        input >> records[i].nome >> records[i].pontuacao;
    }
    organizarRecords(records, NUM_RECORDS);
    input.close();

    // Digitação do nome
    string digit;

    cout << "Inicializando seed de RNG..." << endl;
    srand(time(NULL));

    cout << "Criando vetor de plataformas..." << endl;
    Plataforma platInicial;
    Plataforma plat[NUM_PLATAFORMAS];

    // Flags que fazem o código rodar apenas uma vez
    bool firstSpawnPlats = false;
    bool resetPlayer = false;
    bool geraMenu = false;
    bool recordsEscritos = false;
    bool creditosEscritos = false;

    cout << "Criando blocos de texto..." << endl;
    Texto* textoGameOver;
    Texto* textoPontuacao;
    Texto* textoTitulo;
    Texto* creditoAngelo;
    Texto* creditoVictor;
    Texto* creditoIncompetech1;
    Texto* creditoIncompetech2;
    Texto* textoNome;
    Texto* textoRecords[NUM_RECORDS];

    cout << "Criando botões..." << endl;
    // Botões do menu
    Botao* botaoPlay;
    Botao* botaoRecords;
    Botao* botaoCreditos;
    Botao* botaoSair;
    Botao* botaoNome;

    // Botões dos recordes
    Botao* botaoRetorno;

    cout << "Iniciando loop do jogo..." << endl;
    // Loop do programa
    bool quit = false;
    while(!quit) {
        switch(sdl.gamestate) {
        /* -------------------------------------------------------------------------------------------------------- */
        // Início JOGO
            case JOGO: {
                if(!firstSpawnPlats) { // Setup das plataformas, player, e etc.
                    // Inicia o texto da Pontuação
                    string pontos = "Pontuacao: " + to_string(player.getPontuacao()); // Cria a string a ser exibida no texto
                    textoPontuacao = new Texto(&sdl, "data/arial.ttf", 32, pontos, {255, 0, 0}); // Cria o texto com a string gerada

                    resetPlayer = false; // Faz o GAME_OVER resetar a posição do Player depois de perder

                    // Calcula o espaçamento entre as plataformas
                    int buraco = (sdl.JANELA_LARGURA - (NUM_PLATAFORMAS - 1) * COMP_PLATAFORMAS) / (NUM_PLATAFORMAS - 2);
                    plat[0].setEspacamento(buraco);

                    // Inicia música do jogo
                    if(currentMusic == ""){
                        Mix_PlayMusic(musJogo.musica, -1);
                        currentMusic = musJogo.arquivo.c_str();
                    }
                    else if(Mix_PlayingMusic() && (currentMusic != musJogo.arquivo.c_str())){
                        Mix_HaltMusic();
                        Mix_PlayMusic(musJogo.musica, -1);
                        currentMusic = musJogo.arquivo.c_str();
                    }

                    // Cria uma plataforma inicial
                    cout << "Criando plataforma inicial..." << endl;
                    platInicial.setSDLObject(&sdl);
                    platInicial.setComprimento(sdl.JANELA_LARGURA - buraco);
                    platInicial.pos.x = 0;
                    platInicial.pos.y = sdl.JANELA_ALTURA / 2;
                    platInicial.pos.w = sdl.JANELA_LARGURA - buraco;
                    platInicial.pos.h = ALT_PLATAFORMAS;

                    // Inicializa as plataformas
                    cout << "Inicializando plataformas..." << endl;
                    for(int i = 0; i < NUM_PLATAFORMAS; i++) {
                        plat[i].setSDLObject(&sdl);
                        plat[i].setComprimento(COMP_PLATAFORMAS);
                        plat[i].pos.x = sdl.JANELA_LARGURA + i*(COMP_PLATAFORMAS + buraco);
                        plat[i].pos.y = plat[i].alturaAleatoria();
                        plat[i].pos.w = COMP_PLATAFORMAS;
                        plat[i].pos.h = ALT_PLATAFORMAS;
                        cout << " - Plataforma " << i << " criada em (" << plat[i].pos.x << ", " << plat[i].pos.y << ")." << endl;
                    }
                    plat[0].setVel(7); // A velocidade é static

                    firstSpawnPlats = true; // Esse trecho só roda uma vez por partida
                }
                // Refaz o vetor de char com a nova pontuação
                string pontos = "Pontuacao: " + to_string(player.getPontuacao()); // Gera a string do texto novamente

                textoPontuacao->alterText(pontos, {255, 0, 0}); // Altera o texto já existente

                // Atualiza a posição do plano de fundo
                bg.update();

                // Atualiza a posição das plataformas
                platInicial.updatePlatInicial();
                for(int i = 0; i < NUM_PLATAFORMAS; i++) {
                    int anterior = i - 1;
                    if(i == 0) {
                        anterior = NUM_PLATAFORMAS - 1;
                    }

                    plat[i].update(&(plat[anterior])); // Coloca a plataforma a uma distância fixa da anterior.
                }

                // Atualiza a posição do jogador
                player.atualiza();
                if(player.getPontuacao()%500 == 0){
                    plat[0].setVel(plat[0].getVel()+0.5);
                }

                // Verifica se ele está em cima de alguma plataforma.
                sobrePlataforma(player, platInicial);
                for(int i = 0; i < NUM_PLATAFORMAS; i++) {
                    if(sobrePlataforma(player, plat[i])) {
                        break;
                    }
                }

                // Verifica se ele caiu de alguma plataforma
                foraPlataforma(player, *(player.plataforma));

                // Mostra o plano de fundo
                SDL_RenderCopy(sdl.renderer, bg.textura, &(bg.srcRect), NULL);

                // Mostra o jogador
                player.renderizar();

                // Mostra as nuvens
                platInicial.renderizar();
                for(int i = 0; i < NUM_PLATAFORMAS; i++) {
                    plat[i].renderizar();
                }

                // Mostra a pontuação
                SDL_Rect boxTextoPontuacao = {50, 50, textoPontuacao->getComprimento(), textoPontuacao->getAltura()};
                SDL_RenderCopy(sdl.renderer, textoPontuacao->textura, NULL, &boxTextoPontuacao);

                // Atualiza a tela
                SDL_RenderPresent(sdl.renderer);

                // Tratamento da fila de eventos
                while(SDL_PollEvent(&(sdl.evento)) != 0) {
                    if(sdl.evento.type == SDL_QUIT) { // Fechar a janela
                        quit = true;

                        delete textoPontuacao; // Deleta o texto para não causar memory leak

                        cout << "Finalizando jogo..." << endl;
                    }
                    else if(sdl.evento.type == SDL_KEYDOWN) { // Apertar uma tecla
                        switch(sdl.evento.key.keysym.sym) {
                        case SDLK_UP: // Teclas UP ou W
                        case SDLK_w:
                            if(player.isNoChao()){
                                Mix_PlayChannel(-1, soundPulo.chunk, 0);
                            }
                            player.iniciaPulo();
                            break;
                        }
                    }
                    else if(sdl.evento.type == SDL_KEYUP) { // Soltar uma tecla
                        switch(sdl.evento.key.keysym.sym) {
                        case SDLK_UP: // Teclas UP ou W
                        case SDLK_w:
                            player.iniciaQueda();
                            break;
                        }
                    }
                    else if(sdl.evento.type == SDL_MOUSEBUTTONDOWN) {
                        if(player.isNoChao()){
                            Mix_PlayChannel(-1, soundPulo.chunk, 0);
                        }
                        player.iniciaPulo();
                    }
                    else if(sdl.evento.type == SDL_MOUSEBUTTONUP) {
                        player.iniciaQueda();
                    }
                }
            }
            break; // Break do case JOGO
        // Fim JOGO

        /* -------------------------------------------------------------------------------------------------------- */
        // Início GAME_OVER
            case GAME_OVER: {
                if(!resetPlayer) {
                    delete textoPontuacao; // Deleta o texto do case JOGO

                    firstSpawnPlats = false; // O próximo jogo terá que respawnar as plataformas.

                    // Restaura a posição inicial do Player;
                    cout << "Resetando posição inicial do jogador..." << endl;
                    player.r.y = player.getYInit();

                    // Atualiza records
                    atualizaRecords(records, NUM_RECORDS, player);

                    // Inicia o texto da Pontuação
                    string pontos = "Sua pontuacao foi: " + to_string(player.getPontuacao()); // Cria a string a ser exibida no texto

                    textoPontuacao = new Texto(&sdl, "data/arial.ttf", 40, pontos, {255, 0, 0}); // Cria o texto com a string gerada
                    textoGameOver = new Texto(&sdl, "data/arial.ttf", 32, "Aperte DOWN ou clique no botao abaixo para tentar novamente.", {255, 0, 0});

                    // Cria os botões
                    botaoPlay = new Botao(&sdl,
                                          {(sdl.JANELA_LARGURA - 700)/2, sdl.JANELA_ALTURA / 2 + 50, 700, 100}, {255, 0, 0},
                                          50, "JOGAR NOVAMENTE", {255, 255, 255});
                    botaoRetorno = new Botao(&sdl,
                                             {sdl.JANELA_LARGURA - 50 - 150, sdl.JANELA_ALTURA - 50 - 50, 150, 50}, {255, 0, 0},
                                             36, "Voltar", {255, 255, 255});

                    resetPlayer = true; // Impede que este código seja executado mais de uma vez por loop
                }

                // Preenche a tela de preto
                SDL_SetRenderDrawColor(sdl.renderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(sdl.renderer);

                // Mostra o texto na tela
                SDL_Rect boxTextoPontuacao = {(sdl.JANELA_LARGURA - textoPontuacao->getComprimento()) / 2, sdl.JANELA_ALTURA / 4 - textoPontuacao->getAltura()/ 2, textoPontuacao->getComprimento(), textoPontuacao->getAltura()};
                SDL_RenderCopy(sdl.renderer, textoPontuacao->textura, NULL, &boxTextoPontuacao);
                SDL_Rect boxTextoGameOver = {(sdl.JANELA_LARGURA - textoGameOver->getComprimento()) / 2, (sdl.JANELA_ALTURA - textoGameOver->getAltura()) / 2 - 50, textoGameOver->getComprimento(), textoGameOver->getAltura()};
                SDL_RenderCopy(sdl.renderer, textoGameOver->textura, NULL, &boxTextoGameOver);

                // Mostra os botões na tela
                botaoPlay->renderizar();
                botaoRetorno->renderizar();

                // Atualiza a tela
                SDL_RenderPresent(sdl.renderer);

                // Captura a posição do mouse
                int mousex, mousey;
                SDL_GetMouseState(&mousex, &mousey);

                while(SDL_PollEvent(&(sdl.evento)) != 0) {
                    if(sdl.evento.type == SDL_QUIT) { // Fechar a janela
                        quit = true;

                        delete textoGameOver; // Deleta os textos para não causar memory leak
                        delete textoPontuacao;
                        delete botaoPlay;
                        delete botaoRetorno;

                        cout << "Finalizando jogo..." << endl;
                    }
                    else if(sdl.evento.type == SDL_MOUSEBUTTONUP) {
                        if(botaoPlay->mouseOver(mousex, mousey)) {
                            sdl.gamestate = JOGO;

                            delete textoGameOver; // Deleta os textos para não causar memory leak
                            delete textoPontuacao;
                            delete botaoPlay;
                            delete botaoRetorno;

                            player.setPontuacao(0);
                        }
                        if(botaoRetorno->mouseOver(mousex, mousey)) {
                            sdl.gamestate = MENU;

                            delete textoGameOver; // Deleta os textos para não causar memory leak
                            delete textoPontuacao;
                            delete botaoPlay;
                            delete botaoRetorno;

                            player.setPontuacao(0);
                        }
                    }
                    else if(sdl.evento.type == SDL_KEYDOWN) {
                        switch(sdl.evento.key.keysym.sym) {
                        case SDLK_DOWN:
                        case SDLK_s:
                            sdl.gamestate = JOGO;

                            delete textoGameOver; // Deleta os textos para não causar memory leak
                            delete textoPontuacao;
                            delete botaoPlay;
                            delete botaoRetorno;

                            player.setPontuacao(0);
                            break;
                        }
                    }
                }
            }
            break; // Break do case GAME_OVER

        // Fim GAME_OVER

        /* -------------------------------------------------------------------------------------------------------- */
        // Inicio CREDITOS
            case CREDITOS: {
                if(!creditosEscritos){
                    textoTitulo = new Texto(&sdl, "data/arial.ttf", 36, "Desenvolvedores:", {255,0,0});
                    creditoAngelo = new Texto(&sdl, "data/arial.ttf", 36, "Angelo Borsoi Ross", {255,0,0});
                    creditoVictor = new Texto(&sdl, "data/arial.ttf", 36, "Victor Barpp Gomes", {255,0,0});
                    creditoIncompetech1 = new Texto(&sdl, "data/arial.ttf", 24, "\"Summer Day\" e \"Beachfront Celebration\" Kevin MacLeod (incompetech.com)", {255,0,0});
                    creditoIncompetech2 = new Texto(&sdl, "data/arial.ttf", 24, "Licensed under Creative Commons: By Attribution 3.0 License", {255,0,0});
                    botaoRetorno = new Botao(&sdl,
                                                 {sdl.JANELA_LARGURA - 50 - 150, sdl.JANELA_ALTURA - 50 - 50, 150, 50}, {255, 0, 0},
                                                 36, "Voltar", {255, 255, 255});
                    creditosEscritos = true;
                }
                // Mostra o plano de fundo
                SDL_RenderCopy(sdl.renderer, bg.textura, &(bg.srcRect), NULL);

                SDL_Rect boxIncompetech1 = { (sdl.JANELA_LARGURA - creditoIncompetech1->getComprimento()) / 2, sdl.JANELA_ALTURA * 4 / 6, creditoIncompetech1->getComprimento(), creditoIncompetech1->getAltura()};
                SDL_Rect boxIncompetech2 = { (sdl.JANELA_LARGURA - creditoIncompetech2->getComprimento()) / 2, sdl.JANELA_ALTURA * 4 / 6 + creditoIncompetech1->getAltura() , creditoIncompetech2->getComprimento(), creditoIncompetech2->getAltura()};
                SDL_RenderCopy(sdl.renderer, creditoIncompetech1->textura, NULL, &boxIncompetech1);
                SDL_RenderCopy(sdl.renderer, creditoIncompetech2->textura, NULL, &boxIncompetech2);

                SDL_Rect boxTitulo = { (sdl.JANELA_LARGURA - textoTitulo->getComprimento()) / 2, sdl.JANELA_ALTURA / 6, textoTitulo->getComprimento(), textoTitulo->getAltura()};
                SDL_Rect boxAngelo = { (sdl.JANELA_LARGURA - creditoAngelo->getComprimento()) / 2, sdl.JANELA_ALTURA * 2 / 6, creditoAngelo->getComprimento(), creditoAngelo->getAltura()};
                SDL_Rect boxVictor = { (sdl.JANELA_LARGURA - creditoVictor->getComprimento()) / 2, sdl.JANELA_ALTURA * 3 / 6, creditoVictor->getComprimento(), creditoVictor->getAltura()};

                SDL_RenderCopy(sdl.renderer, creditoAngelo->textura, NULL, &boxAngelo);
                SDL_RenderCopy(sdl.renderer, creditoVictor->textura, NULL, &boxVictor);
                SDL_RenderCopy(sdl.renderer, textoTitulo->textura, NULL, &boxTitulo);

                botaoRetorno->renderizar();
                SDL_RenderPresent(sdl.renderer);


                int mousex, mousey;
                SDL_GetMouseState(&mousex, &mousey);

                while(SDL_PollEvent(&(sdl.evento)) != 0) {
                    if(sdl.evento.type == SDL_QUIT) { // Fechar a janela
                        quit = true;

                        delete botaoRetorno;
                        delete creditoAngelo;
                        delete creditoVictor;
                        delete textoTitulo;
                        delete creditoIncompetech1;
                        delete creditoIncompetech2;

                        creditosEscritos = false;

                        cout << "Finalizando jogo..." << endl;
                    }
                    else if(sdl.evento.type == SDL_MOUSEBUTTONUP) {
                        if(botaoRetorno->mouseOver(mousex, mousey)) {
                            sdl.gamestate = MENU;

                            delete botaoRetorno;
                            delete creditoAngelo;
                            delete creditoVictor;
                            delete textoTitulo;
                            delete creditoIncompetech1;
                            delete creditoIncompetech2;

                            creditosEscritos = false;
                        }
                    }
                }
            }
            break; // Break do case CREDITOS
        // Fim CREDITOS

        /* -------------------------------------------------------------------------------------------------------- */
        // Início RECORDS
            case RECORDS: {
                // NÃO RESETA O PLAYER JÁ QUE AINDA NÃO TEM TRIGGER PARA SAIR
                if(!recordsEscritos) { //Escrever os records apenas uma vez.
                    for(int i=0; i<NUM_RECORDS; i++) {
                        string txtRecord = records[i].nome + " ---> " + to_string(records[i].pontuacao);
                        textoRecords[i] = new Texto(&sdl, "data/arial.ttf", 40, txtRecord, {255, 0, 0});
                    }
                    textoTitulo = new Texto(&sdl, "data/arial.ttf", 72, "Recordes", {255, 0, 0});

                    botaoRetorno = new Botao(&sdl,
                                             {sdl.JANELA_LARGURA - 50 - 150, sdl.JANELA_ALTURA - 50 - 50, 150, 50}, {255, 0, 0},
                                             36, "Voltar", {255, 255, 255});

                    recordsEscritos = true;
                }

                // Mostra o plano de fundo
                SDL_RenderCopy(sdl.renderer, bg.textura, &(bg.srcRect), NULL);

                // Mostra os textos
                SDL_Rect boxTitulo = {(sdl.JANELA_LARGURA - textoTitulo->getComprimento()) / 2, 50, textoTitulo->getComprimento(), textoTitulo->getAltura()};
                SDL_RenderCopy(sdl.renderer, textoTitulo->textura, NULL, &boxTitulo);

                for(int i=0; i<NUM_RECORDS; i++) {
                    SDL_Rect boxTextoRecord = {(sdl.JANELA_LARGURA - textoRecords[i]->getComprimento()) / 2, sdl.JANELA_ALTURA / (NUM_RECORDS+1) * (i+1), textoRecords[i]->getComprimento(), textoRecords[i]->getAltura()};
                    SDL_RenderCopy(sdl.renderer, textoRecords[i]->textura, NULL, &boxTextoRecord);
                }

                // Mostra os botões
                botaoRetorno->renderizar();

                // Mostra o conteúdo na tela
                SDL_RenderPresent(sdl.renderer);

                // Captura a posição do mouse
                int mousex, mousey;
                SDL_GetMouseState(&mousex, &mousey);

                while(SDL_PollEvent(&(sdl.evento)) != 0) {
                    if(sdl.evento.type == SDL_QUIT) { // Fechar a janela
                        quit = true;

                        for(int i=0; i<NUM_RECORDS; i++){
                            delete textoRecords[i]; //Não a memory leak
                        }
                        delete textoTitulo;
                        delete botaoRetorno;

                        recordsEscritos = false;

                        cout << "Finalizando jogo..." << endl;
                    }
                    else if(sdl.evento.type == SDL_MOUSEBUTTONUP) {
                        if(botaoRetorno->mouseOver(mousex, mousey)) {
                            sdl.gamestate = MENU;

                            for(int i=0; i<NUM_RECORDS; i++){
                                delete textoRecords[i]; //Não a memory leak
                            }
                            delete textoTitulo;
                            delete botaoRetorno;

                            recordsEscritos = false;
                        }
                    }
                }
            }
            break; // Break do case RECORDS
        //Fim RECORDS

        /* -------------------------------------------------------------------------------------------------------- */
        // Início MENU
            case MENU: {
                if(!geraMenu) {
                    // Cria a imagem do logo
                    logo = new Imagem(&sdl, "data/logo.png");
                    logo->setCorner((sdl.JANELA_LARGURA - logo->box.w)/2, 50);

                    // Cria os botões
                    botaoPlay = new Botao(&sdl,
                                          {50, sdl.JANELA_ALTURA / 2, sdl.JANELA_LARGURA / 2 - 2*50, sdl.JANELA_ALTURA / 2 - 50}, {255, 0, 0},
                                          50, "JOGAR", {255, 255, 255});
                    botaoRecords = new Botao(&sdl,
                                          {sdl.JANELA_LARGURA / 2 + 50, sdl.JANELA_ALTURA / 2, sdl.JANELA_LARGURA / 2 - 2*50, sdl.JANELA_ALTURA / 6 - 50/3 - 2*20/3}, {255, 0, 0},
                                          28, "RECORDES", {255, 255, 255});
                    botaoCreditos = new Botao(&sdl,
                                          {sdl.JANELA_LARGURA / 2 + 50, sdl.JANELA_ALTURA / 2 + sdl.JANELA_ALTURA / 6 - 50/3 - 2*20/3 + 20, sdl.JANELA_LARGURA / 2 - 2*50, sdl.JANELA_ALTURA / 6 - 50/3 - 2*20/3}, {255, 0, 0},
                                          28, "CREDITOS", {255, 255, 255});
                    botaoSair = new Botao(&sdl,
                                          {sdl.JANELA_LARGURA / 2 + 50, sdl.JANELA_ALTURA / 2 + 2*sdl.JANELA_ALTURA / 6 - 2*50/3 - 2*2*20/3 + 2*20, sdl.JANELA_LARGURA / 2 - 2*50, sdl.JANELA_ALTURA / 6 - 50/3 - 2*20/3}, {255, 0, 0},
                                          28, "SAIR", {255, 255, 255});
                    botaoNome = new Botao(&sdl,
                                          {25, 25, 300, 50}, {255, 0, 0},
                                          28, player.getNome(), {255, 255, 255});

                    geraMenu = true;

                    //Inicia música menu
                    if(currentMusic == ""){
                        Mix_PlayMusic(musMenu.musica, -1);
                        currentMusic = musMenu.arquivo.c_str();
                    }
                    else if(Mix_PlayingMusic() && currentMusic != musMenu.arquivo.c_str()){
                        Mix_HaltMusic();
                        Mix_PlayMusic(musMenu.musica, -1);
                        currentMusic = musMenu.arquivo.c_str();
                    }
                }

                // Mostra o plano de fundo
                SDL_RenderCopy(sdl.renderer, bg.textura, &(bg.srcRect), NULL);

                // Mostra o logo
                logo->renderizar();

                // Mostra os botões
                botaoPlay->renderizar();
                botaoRecords->renderizar();
                botaoCreditos->renderizar();
                botaoSair->renderizar();
                botaoNome->renderizar();

                SDL_RenderPresent(sdl.renderer);

                // Captura a posição do mouse
                int mousex, mousey;
                SDL_GetMouseState(&mousex, &mousey);

                while(SDL_PollEvent(&(sdl.evento)) != 0) {
                    if(sdl.evento.type == SDL_QUIT) { // Fechar a janela

                        delete logo;
                        delete botaoPlay;
                        delete botaoRecords;
                        delete botaoCreditos;
                        delete botaoSair;
                        delete botaoNome;

                        geraMenu = false;
                        quit = true;
                    }
                    else if(sdl.evento.type == SDL_MOUSEBUTTONUP) {
                        if(botaoPlay->mouseOver(mousex, mousey)) {
                            sdl.gamestate = JOGO;

                            delete logo;
                            delete botaoPlay;
                            delete botaoRecords;
                            delete botaoCreditos;
                            delete botaoSair;
                            delete botaoNome;

                            geraMenu = false;
                        }
                        if(botaoRecords->mouseOver(mousex, mousey)) {
                            sdl.gamestate = RECORDS;

                            delete logo;
                            delete botaoPlay;
                            delete botaoRecords;
                            delete botaoCreditos;
                            delete botaoSair;
                            delete botaoNome;

                            geraMenu = false;
                        }
                        if(botaoSair->mouseOver(mousex, mousey)) {
                            delete logo;
                            delete botaoPlay;
                            delete botaoRecords;
                            delete botaoCreditos;
                            delete botaoSair;
                            delete botaoNome;

                            geraMenu = false;
                            quit = true;
                        }
                        if(botaoNome->mouseOver(mousex, mousey)) {
                            sdl.gamestate = NOME;

                            delete logo;
                            delete botaoPlay;
                            delete botaoRecords;
                            delete botaoCreditos;
                            delete botaoSair;
                            delete botaoNome;

                            geraMenu = false;
                        }
                        if(botaoCreditos->mouseOver(mousex, mousey)) {
                            sdl.gamestate = CREDITOS;

                            delete logo;
                            delete botaoPlay;
                            delete botaoRecords;
                            delete botaoCreditos;
                            delete botaoSair;
                            delete botaoNome;

                            geraMenu = false;
                        }
                    }
                }
            }
            break; // Break do case MENU
        // Fim MENU

        /* -------------------------------------------------------------------------------------------------------- */
        // Início NOME
            case NOME: {
                if(!geraMenu) {
                    SDL_StartTextInput();

                    digit = player.getNome();

                    botaoRetorno = new Botao(&sdl,
                                             {sdl.JANELA_LARGURA - 50 - 250, sdl.JANELA_ALTURA - 50 - 50, 250, 50}, {255, 0, 0},
                                             36, "Salvar nome", {255, 255, 255});

                    textoNome = new Texto(&sdl, "data/arial.ttf", 32, digit, {0, 0, 0});
                    textoTitulo = new Texto(&sdl, "data/arial.ttf", 72, "Digite seu nome:", {255, 0, 0});

                    geraMenu = true;
                }

                SDL_Rect boxTexto;
                // Atualiza o texto
                if(digit.length() != 0) {
                    textoNome->alterText(digit, {0, 0, 0});
                    boxTexto = {(sdl.JANELA_LARGURA - textoNome->getComprimento())/2, (sdl.JANELA_ALTURA - textoNome->getAltura())/2, textoNome->getComprimento(), textoNome->getAltura()};
                }

                SDL_Rect boxTitulo = {(sdl.JANELA_LARGURA - textoTitulo->getComprimento()) / 2, 50, textoTitulo->getComprimento(), textoTitulo->getAltura()};

                // Mostra o plano de fundo
                SDL_RenderCopy(sdl.renderer, bg.textura, &(bg.srcRect), NULL);

                // Mostra o texto
                SDL_RenderCopy(sdl.renderer, textoTitulo->textura, NULL, &boxTitulo);
                if(digit.length() != 0) SDL_RenderCopy(sdl.renderer, textoNome->textura, NULL, &boxTexto);

                // Mostra o botão
                botaoRetorno->renderizar();

                SDL_RenderPresent(sdl.renderer);

                // Captura a posição do mouse
                int mousex, mousey;
                SDL_GetMouseState(&mousex, &mousey);

                while(SDL_PollEvent(&(sdl.evento)) != 0) {
                    if(sdl.evento.type == SDL_QUIT) { // Fechar a janela
                        delete botaoRetorno;
                        delete textoNome;
                        delete textoTitulo;

                        geraMenu = false;
                        quit = true;
                    }
                    else if(sdl.evento.type == SDL_KEYDOWN) {
                        if(sdl.evento.key.keysym.sym == SDLK_BACKSPACE) {
                            if(digit.length() > 0) {
                                digit.pop_back();
                            }
                        }
                        else if(sdl.evento.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                            SDL_SetClipboardText(digit.c_str());
                        }
                        else if(sdl.evento.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                            digit = SDL_GetClipboardText();
                        }
                    }
                    else if(sdl.evento.type == SDL_TEXTINPUT) {
                        if(!((sdl.evento.text.text[0] == 'c' || sdl.evento.text.text[0] == 'C') && (sdl.evento.text.text[0] == 'v' || sdl.evento.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
                            if(sdl.evento.text.text[0] != ' ') {
                                digit += sdl.evento.text.text;
                            }
                        }
                    }
                    if(sdl.evento.type == SDL_MOUSEBUTTONUP) {
                        if(digit.length() != 0) {
                            if(botaoRetorno->mouseOver(mousex, mousey)) {
                                sdl.gamestate = MENU;

                                player.setNome(digit);

                                delete botaoRetorno;
                                delete textoNome;
                                delete textoTitulo;

                                SDL_StopTextInput();
                                geraMenu = false;
                            }
                        }
                    }
                }
            }
            break; // Break do case NOME
        /* -------------------------------------------------------------------------------------------------------- */
        }

    }

    sdl.close();

    return 0;
}
