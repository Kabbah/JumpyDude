#ifndef MUSICA_HPP_INCLUDED
#define MUSICA_HPP_INCLUDED
#include <SDL_mixer.h>
#include <string>
#include <iostream>

using namespace std;

class Musica{
public:
    string arquivo;
    Mix_Music *musica;
    Musica(string s);
    ~Musica();

    string getArquivo();
    bool setArquivo(string s);
};

#endif // MUSICA_HPP_INCLUDED
