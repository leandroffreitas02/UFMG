#include "ListaCartas.hpp"

void ListaCartas::AdicionaFinal(Carta c){
    if(tam == MAXTAM)
        throw "ERRO: Uma mao contem apenas 5 cartas!";

    cartas[tam] = c;
    tam++;
}
void ListaCartas::Ordena(){
    for(int i = 0; i < tam-1; i++){
        for(int j = 1; j < tam-i; j++){
            if(cartas[j].num < cartas[j-1].num){
                Carta aux = cartas[j-1];
                cartas[j-1] = cartas[j];
                cartas[j] = aux;
            }
        }
    }
}
bool ListaCartas::RSF(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";

    int rsf[] = {1, 10, 11, 12, 13};
    char naipe = cartas[0].naipe;

    for(int i = 0; i < 5; i++){
        if(cartas[i].num != rsf[i] || cartas[i].naipe != naipe)
            return false;
    }
    return true;
}
bool ListaCartas::SF(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";
    
    char naipe = cartas[0].naipe;

    for(int i = 1; i < 5; i++){
        if(cartas[i].num != cartas[i-1].num + 1 || cartas[i].naipe != naipe)
            return false;
    }
    return true;
}
bool ListaCartas::FK(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";

    int count = 1;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 4)
                return true;

            count = 1;
        }
        else count++;
    }
    if(count == 4)
        return true;
    
    return false;
}
bool ListaCartas::FH(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";

    int count = 1;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 1)
                return false;
            count = 1;
        }
        else count++;
    }
    if(count == 1)
        return false;
    
    return true;
}
bool ListaCartas::F(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";
    
    char naipe = cartas[0].naipe;

    for(int i = 0; i < 5; i++){
        if(cartas[i].naipe != naipe)
            return false;
    }
    return true;
}
bool ListaCartas::S(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";
    
    int rs[] = {1, 10, 11, 12, 13};

    bool RS = true;

    for(int i = 0; i < 5; i++){
        if(cartas[i].num != rs[i])
            RS = false;
    }
    if(RS)
        return true;

    for(int i = 1; i < 5; i++){
        if(cartas[i].num != cartas[i-1].num + 1)
            return false;
    }
    return true;
}
bool ListaCartas::TK(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";
    
    int count = 1;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 3)
                return true;
            count = 1;
        }
        else count++;
    }
    if(count == 3)
        return true;
    
    return false;
}
bool ListaCartas::TP(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";

    int count = 1;

    bool achou = false;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 2){
                if(achou)
                    return true;
                else
                    achou = true;
            }
            count = 1;
        }
        else count++;
    }
    if(count == 2 && achou)
        return true;
    
    return false;
}
bool ListaCartas::OP(){
    if(tam != MAXTAM)
        throw "ERRO: Cartas insuficientes!";
    
    int count = 1;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 2)
                return true;
            count = 1;
        }
        else count++;
    }
    if(count == 2)
        return true;
    
    return false;
}
int ListaCartas::Classifica(){
    Ordena();
    if(RSF()) return 10;
    if(SF()) return 9;
    if(FK()) return 8;
    if(FH()) return 7;
    if(F()) return 6;
    if(S()) return 5;
    if(TK()) return 4;
    if(TP()) return 3;
    if(OP()) return 2;

    return 1;
}
int ListaCartas::ValQuadra(){
    int count = 1;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 4){
                if(cartas[i].num == 1)
                    return 14;
                else
                    return cartas[i].num;
            }

            count = 1;
        }
        else count++;
    }
    if(count == 4){
        if(cartas[4].num == 1)
            return 14;
        else 
            return cartas[4].num;
    }
    
    return -1;
}
int ListaCartas::ValTrinca(){
    int count = 1;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 3){
                if(cartas[i].num == 1)
                    return 14;
                else
                    return cartas[i].num;
            }
            
            count = 1;
        }
        else count++;
    }
    if(count == 3){
        if(cartas[4].num == 1)
            return 14;
        else
            return cartas[4].num;
    }
    
    return -1;
}
int ListaCartas::ValDuplaMaior(){
    int count = 1, MaxDupla = 0;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 2 && cartas[i].num == 1)
                return 14;

            else if(count == 2 && cartas[i].num > MaxDupla)
                MaxDupla = cartas[i].num;

            count = 1;
        }
        else count++;
    }
    if(count == 2 && cartas[4].num > MaxDupla)
        MaxDupla = cartas[4].num;
    
    return MaxDupla;
}
int ListaCartas::ValDuplaMenor(){
    int count = 1, MinDupla = 15;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 2 && cartas[i].num == 1 && 14 < MinDupla)
                MinDupla = 14;

            else if(count == 2 && cartas[i].num < MinDupla)
                MinDupla = cartas[i].num;
            
            count = 1;
        }
        else count++;
    }
    if(count == 2 && cartas[4].num < MinDupla)
        MinDupla = cartas[4].num;

    return MinDupla;
}
int ListaCartas::ValMaior(){
    int count = 1, Maior = 0;

    for(int i = 0; i < 4; i++){
        if(cartas[i].num != cartas[i+1].num){
            if(count == 1 && cartas[i].num == 1)
                return 14;
            
            else if(count == 1 && cartas[i].num > Maior)
                Maior = cartas[i].num;

            count = 1;
        }
        else count++;
    }
    if(count == 1 && cartas[4].num > Maior)
        Maior = cartas[4].num;

    return Maior;
}
int ListaCartas::MaiorAbs(){
    if(cartas[0].num == 1)
        return 14;
    else
        return cartas[4].num;
}
int ListaCartas::MaiorAbs_2(){
    if(cartas[1].num == 1)
        return 14;
    
    else if(MaiorAbs() == 14)
        return cartas[4].num;

    else
        return cartas[3].num;
}
int ListaCartas::MaiorAbs_3(){
    if(cartas[2].num == 1)
        return 14;

    else if(MaiorAbs_2() == 14)
        return cartas[4].num;

    else if(MaiorAbs() == 14)
        return cartas[3].num;
    
    else
        return cartas[2].num;
}
int ListaCartas::MaiorAbs_4(){
    if(cartas[3].num == 1)
        return 14;
    
    else if(MaiorAbs_3() == 14)
        return cartas[4].num;
    
    else if(MaiorAbs_2() == 14)
        return cartas[3].num;

    else if(MaiorAbs() == 14)
        return cartas[2].num;

    else
        return cartas[1].num;
}
int ListaCartas::MaiorAbs_5(){
    if(cartas[4].num == 1)
        return 14;
    
    else if(MaiorAbs_4() == 14)
        return cartas[4].num;

    else if(MaiorAbs_3() == 14)
        return cartas[3].num;

    else if(MaiorAbs_2() == 14)
        return cartas[2].num;

    else if(MaiorAbs() == 14)
        return cartas[1].num;
    
    else
        return cartas[0].num;
}