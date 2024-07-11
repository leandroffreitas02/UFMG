//----------------------------------------------------------------------
// Arquivo: quicksort.c
// Conteudo: implementacao do quicksort para palavras
// Autor: Leandro Freitas de Souza (leandrofreitas@dcc.ufmg.br)
// Historico: 2022-06-29 - arquivo criado
//----------------------------------------------------------------------

#include "quicksort.h"
#include "ordenacao.h"


void insertion_sort(char ** words, int l, int r, int * rank)
// Descricao: realiza o metodo da insercao
// Entrada: words, size
// Saida: words
{
    char * aux = (char *) malloc(sizeof(char) * 32);

    for(int i = l+1; i < r; i++){
        if(strlen(aux) < strlen(words[i]))
            aux = realloc(aux, strlen(words[i]));
        strcpy(aux, words[i]);

        int j = i - 1;

        while((j >= l) && strGcmp(aux, words[j], rank)){
            if(strlen(words[j+1]) < strlen(words[j]))
                words[j+1] = realloc(words[j+1], strlen(words[j]));
            strcpy(words[j+1], words[j]);

            j--;
        }
        if(strlen(words[j+1]) < strlen(aux))
            words[j+1] = realloc(words[j+1], strlen(aux));
        strcpy(words[j+1], aux);
    }

    free(aux);
}
void partition(char ** words, int l, int r, int *i, int *j, int x, int * rank)
// Descricao: realiza a particao para o QuickSort
// Entrada: words, l, r, x(pivô)
// Saida: words
{
    *i = l, *j = r;

    char * aux = (char *) malloc(sizeof(char) * 32);

    char * med = FindMedian(words, l, r, x, rank);

    do
    {
        while(strLcmp(med, words[*i], rank)) (*i)++;
        while(strGcmp(med, words[*j], rank)) (*j)--;

        if(*i <= *j){
            aux = realloc(aux, sizeof(words[*i]));
            strcpy(aux, words[*i]);

            words[*i] = realloc(words[*i], strlen(words[*j]));
            strcpy(words[*i], words[*j]);

            words[*j] = realloc(words[*j], strlen(aux));
            strcpy(words[*j], aux);

            (*i)++; (*j)--;
        }

    } while(*i <= *j);

    free(aux);
}
void order(char ** words, int l, int r, int insert, int x, int * rank)
// Descricao: Execucao recursiva do QuickSort
// Entrada: words, l, r, insert, x
// Saida: words
{
    if(r - l <= insert){
        insertion_sort(words, l, r+1, rank);
        return;
    }
    int i, j;
    partition(words, l, r, &i, &j, x, rank);

    if(l < j){
        order(words, l, j, insert, x, rank);
    }
    if(i < r){
        order(words, i, r, insert, x, rank);
    }

}
void QuickSort(char ** words, int size, int insert, int x, int * rank)
// Descricao: realiza o QuickSort
// Entrada, words, size, insert, x, rank
// Saida: words
{
    order(words, 0, size-1, insert, x, rank);
}
char * FindMedian(char ** words, int l, int r, int x, int * rank)
// Descricao: encontra a mediana entre os primeiros x elementos em certo range do vetor
// Entrada: words, l, r, x, rank
// Saida: mediana
{
    // para caso o tamanho do vetor seja menor que x
    int a = min(r-l+1, x);

    if(a == 1)
        return words[l];

    char ** aux = (char **) malloc(sizeof(char *) * a);

    for(int i = l; i - l < a; i++){
        aux[i-l] = (char *) malloc(sizeof(char) * strlen(words[i]));
        strcpy(aux[i-l], words[i]);
    }

    insertion_sort(aux, 0, a, rank);

    char * ret = (char *) malloc(sizeof(char) * strlen(aux[a/2]));
    strcpy(ret, aux[a/2]);

    clean(aux, a);

    return ret;
}