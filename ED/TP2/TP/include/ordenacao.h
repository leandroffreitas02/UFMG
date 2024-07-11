#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b));
#define min(a, b) (((a) < (b)) ? (a) : (b));

void GetOrder(FILE * in, int * rank);
void LowerCase(char * str);
char * ReadLine(FILE * in);
char ** ReadWords(FILE * in, int * size);
int UndesiredChar(char c);
int strGcmp(char * str1, char * str2, int * rank);
int strLcmp(char * str1, char * str2, int * rank);
void SaveOrder(FILE * out, char ** words, int size);
void HyphenFixer(char ** words, int * size);
char RemoveAccent(char c);
void clean(char ** words, int size);

#endif