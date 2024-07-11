//--------------------------------------------------------------------------------------
// Arquivo: ordenacao.c
// Conteudo: funcoes necessarias para a implementacao do programa de ordenacao
// Autor: Leandro Freitas de Souza (leandrofreitas@dcc.ufmg.br)
// Historico: 2022-06-28 - arquivo criado
//--------------------------------------------------------------------------------------

#include "ordenacao.h"
#include <ctype.h>


void GetOrder(FILE * in, int * rank)
// Descricao: le do arquivo de entrada a ordem lexicografica e retorna uma
// array com o ranking (ou valor) de cada letra do alfabeto
// Entrada: in, rank
// Saida: rank
{
    char * order = ReadLine(in);

    LowerCase(order);

    int len = strlen(order), j = 0;

    for(int i = 0; i < len; i++){
        if(order[i] != ' '){
            rank[order[i] - 'a'] = j;
            j++;
        }
    }
}
void LowerCase(char * str)
// Descricao: converte uma string para letras minusculas
// Entrada: str
// Saida: str
{
    for(char *p = str; *p; p++){
        *p = tolower(*p);
    }
}
char * ReadLine(FILE * in)
// Descricao: le uma linha do arquivo
// Entrada: in
// Saida: line
{
    char * str;
    unsigned int len = 32, size = 0;

    str = (char *) malloc(sizeof(char) * len);

    char c = getc(in);

    while(c != '\n' && c != EOF){
        if(size == len){
            len *= 2;
            str = realloc(str, len);
        }

        str[size] = c;
        size++;

        c = getc(in);
    }
    return str;
}
char ** ReadWords(FILE * in, int * size)
// Descricao: le as palavras a serem ordenadas
// Entrada: in
// Saida: word
{
    char ** words;
    unsigned int len = 32;

    words = (char **) malloc(sizeof(char *) * len);

    char c = getc(in);

    while(c != EOF){
        
        // caso haja espacos ou quebras de linha seguidos
        if(c == ' ' || c == '\n'){
            c = getc(in);
            continue;
        }

        // realocar tamanho da array caso necessário
        if(*size == len){
            len *= 2;
            words = (char **)realloc(words, sizeof(char *) * len);
        }

        unsigned int len1 = 32, size1 = 0;
        words[*size] = (char *) malloc(sizeof(char) * len1);

        while(c != ' ' && c != '\n' && c != EOF){

            // desconsiderar caracteres indesejados
            if(UndesiredChar(c)){
                c = getc(in);
                continue;
            }

            // realocar o tamanho da string caso necessario
            if(size1 == len1){
                len1 *= 2;
                words[*size] = realloc(words[*size], len1);
            }
            words[*size][size1] = c;
            size1++;

            c = getc(in);
        }

        // tornar todos os caracteres da string minusculos
        LowerCase(words[*size]);

        (*size)++;

        c = getc(in);
    }
    return words;
}
int UndesiredChar(char c)
// Descricao: retorna verdadeiro se o char é um caractere indesejado
// Entrada: c
// Saida: 0 ou 1
{
    return (c == ',' || c == '.' || c == '!' || c == '?' || c == ':' || c ==';' || c == '_');
}
int strGcmp(char * str1, char * str2, int * rank)
// Descricao: compara duas strings de acordo com um ranking (equivalente ao operador >)
// Entrada: str1, str2
// Saida: str1 > str2
{
    int size = min(strlen(str1), strlen(str2));

    for(int i = 0; i < size; i++){
        if(str1[i] == str2[i])
            continue;

        if((str1[i] >= 97 && str1[i] <= 122) && (str2[i] >= 97 && str2[i] <= 122)){
            return (rank[str1[i] - 'a'] < rank[str2[i] - 'a']);
        }
        return (str1[i] < str2[i]);
    }

    return (strlen(str1) < strlen(str2));
}
int strLcmp(char * str1, char * str2, int * rank)
// Descricao: compara duas strings de acordo com um ranking (equivalente ao operador <)
// Entrada: str1, str2
// Saida: str1 < str2
{
    int size = min(strlen(str1), strlen(str2));

    for(int i = 0; i < size; i++){
        if(str1[i] == str2[i])
            continue;

        if((str1[i] >= 97 && str1[i] <= 122) && (str2[i] >= 97 && str2[i] <= 122)){
            return (rank[str1[i] - 'a'] > rank[str2[i] - 'a']);
        }
        return (str1[i] > str2[i]);
    }

    return (strlen(str1) > strlen(str2));
}
void SaveOrder(FILE * out, char ** words, int size)
// Descricao: salva, em um arquivo de saida, a ordenacao das palavras
// Entrada: out, words
// Saida: out
{
    int count = 1;
    for(int i = 0; i < size - 1; i++){
        if(!strcmp(words[i], words[i+1]))
            count++;
        else{
            fprintf(out, "%s %d\n", words[i], count);
            count = 1;
        }
    }
    fprintf(out, "%s %d\n#FIM\n", words[size-1], count);
}
void HyphenFixer(char ** words, int * size)
// Descricao: junta duas palavras se uma delas é terminada com um hifen
// Entrada: words, size
// Saida: words
{
    for(int i = 0; i < *size - 1; i++){
        if(words[i][strlen(words[i])-1] == '-'){
            words[i] = realloc(words[i], strlen(words[i]) + strlen(words[i+1]));
            strcat(words[i], words[i+1]);

            for(int j = i + 1; j < *size - 1; j++){
                words[j] = realloc(words[j], strlen(words[j+1]));
                strcpy(words[j], words[j+1]);
            }
            (*size)--;
        }
    }

}
void clean(char ** words, int size)
// Descricao: desaloca um vetor de palavras
// Entrada: words
// Saida: nenhuma
{
    for(int i = 0; i < size; i++)
        free(words[i]);
    free(words);
}