#include "ListaJogadores.hpp"
#include <string.h>

void ListaJogadores::AdicionaFinal(Jogador j){
    if(tam == MAXTAM)
        throw "Numero de jogadores invalido!";
    
    jogadores[tam] = j;
    tam++;
}
void ListaJogadores::OrdenaPorCartas(){
    for(int i = 0; i < tam-1; i++){
        for(int j = 1; j < tam-i; j++){
            if(jogadores[j].cartas.Classifica() > jogadores[j-1].cartas.Classifica()){
                Jogador aux = jogadores[j-1];
                jogadores[j-1] = jogadores[j];
                jogadores[j] = aux;
            }
        }
    }
}
std::string ListaJogadores::Imprime(){
    std::string s = "";
    for(int i = 0; i < tam; i++){
        s += jogadores[i].nome + '\n';
    }
    return s;
}
bool ListaJogadores::TesteSanidade(int pingo){
    for(int i = 0; i < tam; i++){
        if(jogadores[i].dinheiro - pingo < 0)
            return false;
    }
    return true;
}
bool ListaJogadores::TesteSanidadeApostas(int apostas[], int pingo){
    for(int i = 0; i < tam; i++){
        if(jogadores[i].dinheiro - apostas[i] - pingo < 0)
            return false;
        if(apostas[i] % 50)
            return false;
    }
    return true;
}
ListaJogadores * ListaJogadores::Ganhadores(){
    OrdenaPorCartas();
    int Classif = jogadores[0].cartas.Classifica();

    int count = 0;

    for(int i = 0; i < tam; i++){
        if(jogadores[i].cartas.Classifica() != Classif) 
            break;
        
        else count++;
    }
    ListaJogadores * l = new ListaJogadores();

    if(Classif == 10 || Classif == 9){
        for(int i = 0; i < count; i++)
            l->AdicionaFinal(jogadores[i]);

        return l;
    }

    bool desempate[count];
    memset(desempate, false, sizeof desempate);

    if(Classif == 8){
        int MaxQuadra = 0, MaxCarta = 0;

        for(int i = 0; i < count; i++){
            int mq = jogadores[i].cartas.ValQuadra();
            if(MaxQuadra < mq){
                MaxQuadra = mq;
                MaxCarta = jogadores[i].cartas.ValMaior();

                for(int j = 0; j < i; j++)
                    desempate[j] = false;
                desempate[i] = true;
            }
            else if(MaxQuadra == mq){
                int mc = jogadores[i].cartas.ValMaior();

                if(MaxCarta < mc){
                    MaxCarta = mc;

                    for(int j = 0; j < i; j++)
                        desempate[j] = false;
                    desempate[i] = true;
                }
                else if(MaxCarta == mc)
                    desempate[i] = true;
            }
        }
    }
    else if(Classif == 7){
        int MaxTrinca = 0, MaxPar = 0;

        for(int i = 0; i < count; i++){
            int mt = jogadores[i].cartas.ValTrinca();

            if(MaxTrinca < mt){
                MaxTrinca = mt;
                MaxPar = jogadores[i].cartas.ValDuplaMaior();

                for(int j = 0; j < i; j++)
                    desempate[j] = false;
                desempate[i] = true;
            }
            else if(MaxTrinca == mt){
                int mp = jogadores[i].cartas.ValDuplaMaior();

                if(MaxPar < mp){
                    MaxPar = mp;

                    for(int j = 0; j < i; j++)
                        desempate[j] = false;
                    desempate[i] = true;
                }
                else if(MaxPar == mp)
                    desempate[i] = true;
            }
        }
    }
    else if(Classif == 6){
        int MaxCartas[5];
        memset(MaxCartas, 0, sizeof MaxCartas);

        for(int i = 0; i < count; i++){
            int mc = jogadores[i].cartas.MaiorAbs();

            if(MaxCartas[4] < mc){
                MaxCartas[4] = mc;
                MaxCartas[3] = jogadores[i].cartas.MaiorAbs_2();
                MaxCartas[2] = jogadores[i].cartas.MaiorAbs_3();
                MaxCartas[1] = jogadores[i].cartas.MaiorAbs_4();
                MaxCartas[0] = jogadores[i].cartas.MaiorAbs_5();

                for(int j = 0; j < i; j++)
                    desempate[j] = false;
                desempate[i] = true;
            }
            else if(MaxCartas[4] == mc){
                int mc2 = jogadores[i].cartas.MaiorAbs_2();

                if(MaxCartas[3] < mc2){
                    MaxCartas[3] = mc2;
                    MaxCartas[2] = jogadores[i].cartas.MaiorAbs_3();
                    MaxCartas[1] = jogadores[i].cartas.MaiorAbs_4();
                    MaxCartas[0] = jogadores[i].cartas.MaiorAbs_5();

                    for(int j = 0; j < i; j++)
                        desempate[j] = false;
                    desempate[i] = true;
                }
                else if(MaxCartas[3] == mc2){
                    int mc3 = jogadores[i].cartas.MaiorAbs_3();

                    if(MaxCartas[2] < mc3){
                        MaxCartas[2] = mc3;
                        MaxCartas[1] = jogadores[i].cartas.MaiorAbs_4();
                        MaxCartas[0] = jogadores[i].cartas.MaiorAbs_5();

                        for(int j = 0; j < i; j++)
                            desempate[j] = false;
                        desempate[i] = true;
                    }
                    else if(MaxCartas[2] == mc3){
                        int mc4 = jogadores[i].cartas.MaiorAbs_4();

                        if(MaxCartas[1] < mc4){
                            MaxCartas[1] = mc4;
                            MaxCartas[0] = jogadores[i].cartas.MaiorAbs_5();

                            for(int j = 0; j < i; j++)
                                desempate[j] = false;
                            desempate[i] = true;
                        }
                        else if(MaxCartas[1] == mc4){
                            int mc5 = jogadores[i].cartas.MaiorAbs_5();

                            if(MaxCartas[0] < mc5){
                                MaxCartas[0] = mc5;

                                for(int j = 0; j < i; j++)
                                    desempate[j] = false;
                                desempate[i] = true;
                            }
                            else if(MaxCartas[0] == mc5)
                                desempate[i] = true;
                        }
                    }
                }
            }
        }
    }
    else if(Classif == 5){
        int MaxCarta = 0;

        for(int i = 0; i < count; i++){
            int mc = jogadores[i].cartas.GetCarta(4).num;
            if(jogadores[i].cartas.GetCarta(0).num == 1)
                mc = 14;

            if(MaxCarta < mc){
                MaxCarta = mc;

                for(int j = 0; j < i; j++)
                    desempate[j] = false;
                desempate[i] = true;
            }
            else
                desempate[i] = true;
        }
    }
    else if(Classif == 4){
        int MaxTrinca = 0;
        int MaxCartas[2] = {0, 0};

        for(int i = 0; i < count; i++){
            int mt = jogadores[i].cartas.ValTrinca();

            if(mt > MaxTrinca){
                MaxTrinca = mt;
                MaxCartas[1] = jogadores[i].cartas.ValMaior();
                for(int j = 0; j < 5; j++)
                    if(jogadores[i].cartas.GetCarta(j).num != mt && jogadores[i].cartas.GetCarta(j).num != MaxCartas[1])
                        MaxCartas[0] = jogadores[i].cartas.GetCarta(j).num;

                for(int j = 0; j < i; j++)
                    desempate[j] = false;
                desempate[i] = true;
            }
            else if(mt == MaxTrinca){
                int mc = jogadores[i].cartas.ValMaior();

                if(MaxCartas[1] < mc){
                    MaxCartas[1] = mc;
                    for(int j = 0; j < 5; j++)
                        if(jogadores[i].cartas.GetCarta(j).num != mt && jogadores[i].cartas.GetCarta(j).num != mc)
                            MaxCartas[0] = jogadores[i].cartas.GetCarta(j).num;

                    for(int j = 0; j < i; j++)
                        desempate[j] = false;

                    desempate[i] = true;
                }
                else if(MaxCartas[1] == mc){
                    int mc2;
                    for(int j = 0; j < 5; j++){
                        if(jogadores[i].cartas.GetCarta(j).num != mt && jogadores[i].cartas.GetCarta(j).num != mc)
                            mc2 = jogadores[i].cartas.GetCarta(j).num;
                    }
                    if(MaxCartas[0] < mc2){
                        MaxCartas[0] = mc2;

                        for(int j = 0; j < i; j++)
                            desempate[j] = false;
                        desempate[i] = true;
                    }
                    else if(MaxCartas[0] == mc2)
                        desempate[i] = true;
                }
            }
        }
    }
    else if(Classif == 3){
        int MaxParMaior = 0;
        int MaxParMenor = 0;
        int MaxCarta = 0;

        for(int i = 0; i < count; i++){
            int mp = jogadores[i].cartas.ValDuplaMaior();

            if(MaxParMaior < mp){
                MaxParMaior = mp;
                MaxParMenor = jogadores[i].cartas.ValDuplaMenor();
                MaxCarta = jogadores[i].cartas.ValMaior();

                for(int j = 0; j < i; j++)
                    desempate[j] = false;
                desempate[i] = true;
            }
            else if(MaxParMaior == mp){
                int mp2 = jogadores[i].cartas.ValDuplaMenor();

                if(mp2 > MaxParMenor){
                    MaxParMenor = mp2;
                    MaxCarta = jogadores[i].cartas.ValMaior();

                    for(int j = 0; j < i; j++)
                        desempate[j] = false;
                    desempate[i] = true;
                }
                else if(mp2 == MaxParMenor){
                    int mc = jogadores[i].cartas.ValMaior();

                    if(mc > MaxCarta){
                        MaxCarta = mc;

                        for(int j = 0; j < i; j++)
                            desempate[j] = false;
                        desempate[i] = true;
                    }
                    else if(mc == MaxCarta)
                        desempate[i] = true;
                }
            }
        }
    }
    else if(Classif == 2){
        int MaxPar = 0;
        int MaxCartas[3] = {0, 0, 0};

        for(int i = 0; i < count; i++){
            int mp = jogadores[i].cartas.ValDuplaMaior();
            int aux;

            if(mp == 14)
                aux = 1;
            else aux = mp;

            if(mp > MaxPar){
                MaxPar = mp;
                MaxCartas[2] = jogadores[i].cartas.ValMaior();
                for(int j = 0; j < 5; j++){
                    if(jogadores[i].cartas.GetCarta(j).num != MaxCartas[2] && jogadores[i].cartas.GetCarta(j).num != aux){
                        MaxCartas[1] = jogadores[i].cartas.GetCarta(j).num;
                    }
                }
                for(int j = 0; j < 5; j++){
                    if(jogadores[i].cartas.GetCarta(j).num != MaxCartas[2] && jogadores[i].cartas.GetCarta(j).num != MaxCartas[1] && jogadores[i].cartas.GetCarta(j).num != aux){
                        MaxCartas[0] = jogadores[i].cartas.GetCarta(j).num;
                    }
                }
                for(int j = 0; j < i; j++)
                    desempate[j] = false;
                desempate[i] = true;
            }
            else if(mp == MaxPar){
                int mc1 = jogadores[i].cartas.ValMaior();
                int aux2;

                if(mc1 == 14)
                    aux2 = 1;
                
                else aux2 = mc1;

                if(mc1 > MaxCartas[2]){
                    MaxCartas[2] = mc1;
                    for(int j = 0; j < 5; j++){
                        if(jogadores[i].cartas.GetCarta(j).num != aux2 && jogadores[i].cartas.GetCarta(j).num != aux){
                            MaxCartas[1] = jogadores[i].cartas.GetCarta(j).num;
                        }
                    }
                    for(int j = 0; j < 5; j++){
                        if(jogadores[i].cartas.GetCarta(j).num != aux2 && jogadores[i].cartas.GetCarta(j).num != MaxCartas[1] && jogadores[i].cartas.GetCarta(j).num != aux){
                            MaxCartas[0] = jogadores[i].cartas.GetCarta(j).num;
                        }
                    }
                    for(int j = 0; j < i; j++)
                        desempate[j] = false;
                    desempate[i] = true;
                }
                else if(mc1 == MaxCartas[2]){
                    int mc2;
                    for(int j = 0; j < 5; j++){
                        if(jogadores[i].cartas.GetCarta(j).num != aux2 && jogadores[i].cartas.GetCarta(j).num != aux){
                            mc2 = jogadores[i].cartas.GetCarta(j).num;
                        }
                    }
                    if(mc2 > MaxCartas[1]){
                        MaxCartas[1] = mc2;
                        for(int j = 0; j < 5; j++){
                            if(jogadores[i].cartas.GetCarta(j).num != aux2 && jogadores[i].cartas.GetCarta(j).num != mc2 && jogadores[i].cartas.GetCarta(j).num != aux){
                                MaxCartas[0] = jogadores[i].cartas.GetCarta(j).num;
                                break;
                            }
                        }
                        for(int j = 0; j < i; j++)
                            desempate[j] = false;
                        desempate[i] = true;
                    }
                    else if(mc2 == MaxCartas[1]){
                        int mc3;
                        for(int j = 0; j < 5; j++){
                            if(jogadores[i].cartas.GetCarta(j).num != aux2 && jogadores[i].cartas.GetCarta(j).num != mc2 && jogadores[i].cartas.GetCarta(j).num != aux){
                                mc3 = jogadores[i].cartas.GetCarta(j).num;
                                break;
                            }
                        }
                        if(mc3 > MaxCartas[0]){
                            MaxCartas[0] = mc3;
                            for(int j = 0; j < 5; j++)
                                desempate[j] = false;
                            desempate[i] = true;
                        }
                        else if(mc3 == MaxCartas[0])
                            desempate[i] = true;
                    }
                }
            }
        }
    }
    else if(Classif == 1){
        int MaxCartas[5];
        memset(MaxCartas, 0, sizeof MaxCartas);

        for(int i = 0; i < count; i++){
            int mc = jogadores[i].cartas.MaiorAbs();

            if(MaxCartas[4] < mc){
                MaxCartas[4] = mc;
                MaxCartas[3] = jogadores[i].cartas.MaiorAbs_2();
                MaxCartas[2] = jogadores[i].cartas.MaiorAbs_3();
                MaxCartas[1] = jogadores[i].cartas.MaiorAbs_4();
                MaxCartas[0] = jogadores[i].cartas.MaiorAbs_5();

                for(int j = 0; j < i; j++)
                    desempate[j] = false;
                desempate[i] = true;
            }
            else if(MaxCartas[4] == mc){
                int mc2 = jogadores[i].cartas.MaiorAbs_2();

                if(MaxCartas[3] < mc2){
                    MaxCartas[3] = mc2;
                    MaxCartas[2] = jogadores[i].cartas.MaiorAbs_3();
                    MaxCartas[1] = jogadores[i].cartas.MaiorAbs_4();
                    MaxCartas[0] = jogadores[i].cartas.MaiorAbs_5();

                    for(int j = 0; j < i; j++)
                        desempate[j] = false;
                    desempate[i] = true;
                }
                else if(MaxCartas[3] == mc2){
                    int mc3 = jogadores[i].cartas.MaiorAbs_3();

                    if(MaxCartas[2] < mc3){
                        MaxCartas[2] = mc3;
                        MaxCartas[1] = jogadores[i].cartas.MaiorAbs_4();
                        MaxCartas[0] = jogadores[i].cartas.MaiorAbs_5();

                        for(int j = 0; j < i; j++)
                            desempate[j] = false;
                        desempate[i] = true;
                    }
                    else if(MaxCartas[2] == mc3){
                        int mc4 = jogadores[i].cartas.MaiorAbs_4();

                        if(MaxCartas[1] < mc4){
                            MaxCartas[1] = mc4;
                            MaxCartas[0] = jogadores[i].cartas.MaiorAbs_5();

                            for(int j = 0; j < i; j++)
                                desempate[j] = false;
                            desempate[i] = true;
                        }
                        else if(MaxCartas[1] == mc4){
                            int mc5 = jogadores[i].cartas.MaiorAbs_5();

                            if(MaxCartas[0] < mc5){
                                MaxCartas[0] = mc5;

                                for(int j = 0; j < i; j++)
                                    desempate[j] = false;
                                desempate[i] = true;
                            }
                            else if(MaxCartas[0] == mc5)
                                desempate[i] = true;
                        }
                    }
                }
            }
        }       
    }
    for(int i = 0; i < count; i++) if(desempate[i])
        l->AdicionaFinal(jogadores[i]);

    return l;
}
std::string ListaJogadores::MaiorJogada(){
    OrdenaPorCartas();
    int Classif = jogadores[0].cartas.Classifica();

    switch (Classif)
    {
    case 10:
        return "RSF";
    case 9:
        return "SF";
    case 8:
        return "FK";
    case 7:
        return "FH";
    case 6:
        return "F";
    case 5:
        return "S";
    case 4:
        return "TK";
    case 3:
        return "TP";
    case 2:
        return "OP";
    case 1:
        return "HC";

    default:
        return "";
    }
}
void ListaJogadores::Aposta(int val){
    for(int i = 0; i < tam; i++)
        jogadores[i].dinheiro -= val;
}
void ListaJogadores::BuscaAposta(std::string nome, int val){
    for(int i = 0; i < tam; i++){
        if(jogadores[i].nome == nome){
            jogadores[i].dinheiro -= val;
            break;
        }
    }
}
void ListaJogadores::BuscaRecebe(std::string nome, int val){
    for(int i = 0; i < tam; i++){
        if(jogadores[i].nome == nome){
            jogadores[i].dinheiro += val;
            break;
        }
    }
}
void ListaJogadores::OrdenaPorDinheiro(){
    for(int i = 0; i < tam-1; i++){
        for(int j = 1; j < tam-i; j++){
            if(jogadores[j].dinheiro > jogadores[j-1].dinheiro){
                Jogador aux = jogadores[j-1];
                jogadores[j-1] = jogadores[j];
                jogadores[j] = aux;
            }
            else if(jogadores[j].dinheiro == jogadores[j-1].dinheiro){
                if(jogadores[j].nome < jogadores[j-1].nome){
                    Jogador aux = jogadores[j-1];
                    jogadores[j-1] = jogadores[j];
                    jogadores[j] = aux;
                }
            }
        }
    }
}
std::string ListaJogadores::ImprimeResultado(){
    OrdenaPorDinheiro();
    std::string s = "";
    for(int i = 0; i < tam; i++){
        s += jogadores[i].nome + ' ' + std::to_string(jogadores[i].dinheiro) + '\n';
    }
    return s;
}
Jogador ListaJogadores::Busca(std::string nome){
    for(int i = 0; i < tam; i++){
        if(jogadores[i].nome == nome)
            return jogadores[i];
    }
    return jogadores[0];
}