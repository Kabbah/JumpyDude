#include "Musica.hpp"

using namespace std;

Musica::Musica(string s){
    arquivo = s.c_str();
    musica = Mix_LoadMUS(arquivo.c_str());
    if(musica == NULL){
        cout << "Falha ao carregar a música. Erro: " << Mix_GetError() << endl;
    }
}
Musica::~Musica(){
    Mix_FreeMusic(musica);
}

bool Musica::setArquivo(string s){
    arquivo = s.c_str();
    musica = Mix_LoadMUS(arquivo.c_str());
    if(musica == NULL){
        cout << "Falha ao carregar a música. Erro: " << Mix_GetError() << endl;
        return false;
    }
    return true;
}
