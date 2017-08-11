#include "Soundeffect.hpp"

using namespace std;

Soundeffect::Soundeffect(string s){
    arquivo = s.c_str();
    chunk = Mix_LoadWAV(arquivo.c_str());
    if(chunk == NULL){
        cout << "Falha ao carregar o soundeffect. Erro: " << Mix_GetError() << endl;
    }
}
Soundeffect::~Soundeffect(){
    Mix_FreeChunk(chunk);
}

bool Soundeffect::setArquivo(string s){
    arquivo = s.c_str();
    chunk = Mix_LoadWAV(arquivo.c_str());
    if(chunk == NULL){
        cout << "Falha ao carregar o soundeffect. Erro: " << Mix_GetError() << endl;
        return false;
    }
    return true;
}
