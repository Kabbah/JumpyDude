#include "Record.hpp"

const string Record::arquivo = "data/records.txt";

Record::Record(string newNome, int newPontuacao){
    nome = newNome;
    pontuacao = newPontuacao;

    id.setAtrib(newPontuacao);
}
Record::Record(){
    nome = "";
    pontuacao = 0;
}
Record::~Record(){}

string Record::getNome(){
    return nome;
}
int Record::getPontuacao(){
    return pontuacao;
}
string Record::getArquivo(){
    return arquivo;
}

void Record::setNome(string newNome){
    nome = newNome;
}
void Record::setPontuacao(int newPontuacao){
    pontuacao = newPontuacao;
}

void Record::operator=(Player player){
    nome = player.getNome();
    pontuacao = player.getPontuacao();
}

void organizarRecords(Record* records, int numRecords){
    Record temporario;
    for(int i=0; i<numRecords; i++){
        for(int j=i+1; j<numRecords; j++){
            if(records[i].pontuacao < records[j].pontuacao){
                temporario = records[j];
                records[j] = records[i];
                records[i] = temporario;
            }
        }
    }
}

void atualizaRecords(Record* records, int numRecords, Player player){
    Record recordsTemp[numRecords+1]; //Cria records temporarios
    for(int i=0;i<numRecords;i++){
        recordsTemp[i]=records[i]; //Iguala records temporario ao recebido
    }
    recordsTemp[numRecords]=player; //Coloca o player atual nos records
    organizarRecords(recordsTemp, numRecords+1); //Organiza o temporario
    for(int i=0;i<numRecords;i++){ //Coloca os valores do temporario já organizado no novo vetor, menos o ultimo (o record que deve sair)
        records[i]=recordsTemp[i];
    }

    // Cria o output
    ofstream output;
    output.open(records[0].arquivo.c_str(), ofstream::out | ofstream::trunc); //Deleta os conteúdos atuais
    output.close();
    output.open(records[0].arquivo.c_str(), ofstream::app); //Abre no modo append
    for(int i=0; i<numRecords; i++){ //Escreve os novos records
        output << records[i].nome << " " << records[i].pontuacao << endl;
    }
    output.close();
}

template< typename T >
T GetSet< T >::getAtrib() {
    return atrib;
}
template< typename T >
void GetSet< T >::setAtrib(T param) {
    atrib = param;
}
