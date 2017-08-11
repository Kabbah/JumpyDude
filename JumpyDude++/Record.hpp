#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED
#include <string>
#include <fstream>
#include "Player.hpp"

template< typename T >
class GetSet {
private:
    T atrib;
public:
    T getAtrib();
    void setAtrib(T param);
};

class Record {
public:
    string nome;
    int pontuacao;
    static const string arquivo;
    GetSet< int > id;

    Record(string newNome, int newPontuacao);
    Record();
    ~Record();

    string getNome();
    int getPontuacao();
    string getArquivo();

    void setNome(string newNome);
    void setPontuacao(int newPontuacao);

    void operator=(Player player);
};

void organizarRecords(Record* records, int numRecords);

void atualizaRecords(Record* records, int numRecords, Player player);

#endif // RECORD_H_INCLUDED
