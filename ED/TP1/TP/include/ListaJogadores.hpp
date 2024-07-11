#ifndef JOGADORES_H
#define JOGADORES_H

#include <string>
#include <iostream>
#include "ListaCartas.hpp"

struct Jogador
{
    std::string nome;
    int dinheiro;
    ListaCartas cartas = ListaCartas();
};
class ListaJogadores
{
    public:
        ListaJogadores(){tam = 0;};
        int GetTam(){return tam;};
        Jogador GetJogador(int pos){return jogadores[pos];};

        void AdicionaFinal(Jogador j);
        void OrdenaPorCartas();
        std::string Imprime();

        bool TesteSanidade(int pingo);
        bool TesteSanidadeApostas(int apostas[], int pingo);

        ListaJogadores * Ganhadores();

        std::string MaiorJogada();
        void Aposta(int val);
        
        void BuscaAposta(std::string nome, int val);
        void BuscaRecebe(std::string nome, int val);

        void OrdenaPorDinheiro();
        std::string ImprimeResultado();

        Jogador Busca(std::string nome);

    private:
        int tam;
        static const int MAXTAM = 10;
        Jogador jogadores[MAXTAM];
};


#endif