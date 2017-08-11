#ifndef SOUNDEFFECT_HPP_INCLUDED
#define SOUNDEFFECT_HPP_INCLUDED
#include <SDL_mixer.h>
#include <string>
#include <iostream>

using namespace std;

class Soundeffect{
public:
    string arquivo;
    Mix_Chunk *chunk;
    Soundeffect(string s);
    ~Soundeffect();

    string getArquivo();
    bool setArquivo(string s);
};

#endif // SOUNDEFFECT_HPP_INCLUDED
