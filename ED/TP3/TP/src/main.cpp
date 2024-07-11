#include "msgassert.h"
#include <fstream>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "hash.hpp"

char infile[100];
char outfile[100];

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nenhuma
// Saida: impressao das opcoes
{
    fprintf(stderr, "main\n");
    fprintf(stderr, "\t-i \t(arquivo de entrada)\n");
    fprintf(stderr, "\t-o \t(arquivo de saida)\n");
}

void parse_args(int argc, char ** argv)
// Descricao: le as opcoes da linha de comando
// Entrada: argc e argv
// Saida: infile, outfile
{
    infile[0] = 0;
    outfile[0] = 0;

    char opt;

    while((opt = getopt(argc, argv, "i:o:")) != -1){
        switch (opt)
        {
            case 'i':
                strcpy(infile, optarg);
                break;
            case 'o':
                strcpy(outfile, optarg);
                break;
            default:
                uso();
                exit(1);
        }
    }
    erroAssert(strlen(infile) > 0, "main - nome do arquivo de entrada deve ser definido");
    erroAssert(strlen(outfile) > 0, "main - nome do arquivo de saida deve ser definido");
}

int main(int argc, char ** argv)
// Descricao: programa principal de execucao do TP3
// Entrada: argc e argv
// Saida: arquivo com as operacoes requeridas
{
    parse_args(argc, argv);

    std::ifstream in(infile);
    std::ofstream out(outfile);
    erroAssert(in.is_open(), "Erro ao abrir arquivo de entrada");
    erroAssert(out.is_open(), "Erro ao abrir arquivo de saida");

    std::string command;

    // Leitura do modulo a ser utilizado no hashing
    int M;
    in >> M;

    Hash_BT H(M);

    // leitura dos comandos do arquivo de entrada
    while(in >> command){
        if(command ==  "ENTREGA"){
            int N;
            Email email;

            email.message = "";

            in >> email.dest >> email.key >> N;

            for(int i = 0; i < N; i++){
                std::string msg;
                in >> msg;

                email.message += msg + " ";
            }
            email.message.pop_back();

            H.Insert(email);

            out << "OK: MENSAGEM " << email.key << " PARA " << email.dest << " ARMAZENADA EM " << email.dest % M << std::endl;
        }
        else if(command == "CONSULTA"){
            int U, E;

            in >> U >> E;

            Email email = H.Search(U, E);

            out << "CONSULTA " << U << ' ' << E << ": " << ((email.key == -1) ? "MENSAGEM INEXISTENTE" : email.message) << std::endl;
        }
        else if(command == "APAGA"){
            int U, E;

            in >> U >> E;

            std::string s = H.Remove(U, E);

            out << s << std::endl;
        }
    }
}