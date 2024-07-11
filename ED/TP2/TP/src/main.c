//-----------------------------------------------------------------
// Arquivo: main.c
// Conteudo: programa de execucao do TP2
// Autor: Leandro Freitas de Souza (leandrofreitas@dcc.ufmg.br)
// Historico: 2021-06-28 - arquivo criado
//            2021-06-29 - implementacao do quicksort
//-----------------------------------------------------------------

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "msgassert.h"
#include "ordenacao.h"
#include "quicksort.h"

// variaveis globais utilizadas em parse_args
char infile[100];
char outfile[100];
int median;
int insert;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nenhuma
// Saida: impressao das opcoes
{
    fprintf(stderr, "main\n");
    fprintf(stderr, "\t-i \t(arquivo de entrada)\n");
    fprintf(stderr, "\t-o \t(arquivo de saida)\n");
    fprintf(stderr, "\t-m \t(valor da mediana para o quicksort)\n");
    fprintf(stderr, "\t-s \t(valor do tamanho maximo de uma particao para fazer insercao)\n");
}

void parse_args(int argc, char** argv)
// Descricao: le as opcoes da linha de comando e inicia as variaveis
// Entrada: argc e argv
// Saida: infile, outfile, median, insertion
{
    // inicializacao das variaveis globais
    infile[0] = 0;
    outfile[0] = 0;
    median = -1;
    insert = -1;

    // variavel auxiliar
    char opt;

    while((opt = getopt(argc, argv, "i:o:m:s:")) != -1){
        switch(opt){
            case 'i':
                strcpy(infile, optarg);
                break;
            case 'o':
                strcpy(outfile, optarg);
                break;
            case 'm':
                median = atoi(optarg);
                break;
            case 's':
                insert = atoi(optarg);
                break;
            default:
                uso();
                exit(1);
        }
    }

    // verificacao da consistencia das opcoes
    erroAssert(strlen(infile) > 0, "main - nome do arquivo de entrada deve ser definido");
    erroAssert(strlen(outfile) > 0, "main - nome do arquivo de saida deve ser definido");
    erroAssert(median > 0, "valor da mediana deve ser definido");
    erroAssert(insert > 0, "valor de tamanho máximo das particoes para que seja realizada insercao deve ser definido");
}

int main(int argc, char* argv[])
// Descricao: programa principal para execucao do TP2
// Entrada: argc e argv
// Saida: arquivo com as palavras ordenadas de acordo com os parametros recebidos
{
    // variaveis e estruturas a serem usadas
    FILE *in, *out;
    char * command;
    char ** words;
    int rank[26];

    // processar os comandos recebidos
    parse_args(argc, argv);

    in = fopen(infile, "r");
    erroAssert(in != NULL, "Erro ao abrir arquivo de entrada");

    // leitura dos comandos do programa
    command = ReadLine(in);
    erroAssert(strcmp(command, "#ORDEM") == 0, "Comando invalido");

    GetOrder(in, rank);
    
    command = ReadLine(in);
    erroAssert(strcmp(command, "#TEXTO") == 0, "Comando invalido");

    int len = 0;
    words = ReadWords(in, &len);
    HyphenFixer(words, &len);

    // todo o que deveria ser lido já foi lido -> fim de arquivo atingido
    fclose(in);

    QuickSort(words, len, insert, median, rank);

    out = fopen(outfile, "w");
    erroAssert(out != NULL, "Erro ao abrir arquivo de saida");

    SaveOrder(out, words, len);

    fclose(out);

    // desalocar os espacos ocupados na memoria
    free(command);
    clean(words, len);


    return 0;
}