#include "ListaJogadores.hpp"
#include <string.h>
#include <fstream>

int main(){
    std::ifstream arq;

    arq.open("entrada.txt");

    if(!arq)
        throw "ERRO: Nao existe arquivo com o nome Entrada.txt!";

    int n, di;

    arq >> n >> di;   

 // Le a primeira jogada, que contém todos os jogadores

    int J, P;

    arq >> J >> P;

    ListaJogadores jogadores = ListaJogadores();

    int apostas[J];
    int TotalApostas = P*J;

    for(int i = 0; i < J; i++){
        Jogador j;

        arq >> j.nome >> apostas[i];
        j.dinheiro = di;

        TotalApostas += apostas[i];

        for(int k = 0; k < 5; k++){
            Carta c;

            arq >> c.num >> c.naipe;

            j.cartas.AdicionaFinal(c);
        }
        jogadores.AdicionaFinal(j);
    }
    std::ofstream arqout;
    arqout.open("saida.txt");

    if(!jogadores.TesteSanidade(P) || !jogadores.TesteSanidadeApostas(apostas, P)){
        TotalApostas = 0;
        P = 0;
        memset(apostas, 0, sizeof apostas);
    }

    for(int i = 0; i < J; i++){
        jogadores.BuscaAposta(jogadores.GetJogador(i).nome, apostas[i]);
    }

    jogadores.Aposta(P);

    ListaJogadores * ganhadores = jogadores.Ganhadores();
    int t = ganhadores->GetTam();

    for(int i = 0; i < t; i++){
        jogadores.BuscaRecebe(ganhadores->GetJogador(i).nome, TotalApostas/t);
    }


    arqout << t << ' ' << TotalApostas/t << ' ' << ganhadores->MaiorJogada() << '\n';
    arqout << ganhadores->Imprime();

    n--;

 // Le as jogadas restantes, considerando que todos os jogadores apostaram na primeira jogada

    while(n--){
        int j, p;
        arq >> j >> p;

        memset(apostas, 0, sizeof apostas);
        TotalApostas = J*p;

        ListaJogadores jogada = ListaJogadores();

        for(int i = 0; i < j; i++){
            Jogador jog;

            arq >> jog.nome >> apostas[i];
            jog.dinheiro = jogadores.Busca(jog.nome).dinheiro;

            TotalApostas += apostas[i];

            for(int k = 0; k < 5; k++){
                Carta c;

                arq >> c.num >> c.naipe;

                jog.cartas.AdicionaFinal(c);
            }
            jogada.AdicionaFinal(jog);
        }
        if(!jogadores.TesteSanidade(p) || !jogada.TesteSanidadeApostas(apostas, p)){
            p = 0;
            TotalApostas = 0;
            memset(apostas, 0, sizeof apostas);
        }
        for(int i = 0; i < j; i++){
            jogadores.BuscaAposta(jogada.GetJogador(i).nome, apostas[i]);
        }
        jogadores.Aposta(p);

        ganhadores = jogada.Ganhadores();
        int t = ganhadores->GetTam();

        for(int i = 0; i < t; i++){
            jogadores.BuscaRecebe(ganhadores->GetJogador(i).nome, TotalApostas/t);
        }
        arqout << t << ' ' << TotalApostas/t << ' ' << jogada.MaiorJogada() << '\n';
        arqout << ganhadores->Imprime();
    }

   arqout << "####\n" << jogadores.ImprimeResultado();

   return 0;
}