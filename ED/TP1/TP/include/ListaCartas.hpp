#ifndef CARTA_H
#define CARTA_H

struct Carta
{
    int num;
    char naipe;

};

class ListaCartas
{
    public:
        ListaCartas(){tam = 0;};
        int GetTam(){return tam;};
        Carta GetCarta(int pos){return cartas[pos];};

        void AdicionaFinal(Carta c);
        int Classifica();

        int ValQuadra();
        int ValTrinca();
        int ValDuplaMaior();
        int ValDuplaMenor();
        int ValMaior();
        int MaiorAbs();
        int MaiorAbs_2();
        int MaiorAbs_3();
        int MaiorAbs_4();
        int MaiorAbs_5();

    private:
        static const int MAXTAM = 5;
        Carta cartas[MAXTAM];
        int tam;

        void Ordena();

        bool RSF();
        bool SF();
        bool FK();
        bool FH();
        bool F();
        bool S();
        bool TK();
        bool TP();
        bool OP();
};


#endif