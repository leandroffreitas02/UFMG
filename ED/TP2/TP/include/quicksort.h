#ifndef QUICKSORT_H
#define QUICKSORT_H

void insertion_sort(char ** words, int l, int r, int * rank);
void partition(char ** words, int l, int r, int *i, int *j, int x, int * rank);
void order(char ** words, int l, int r, int insert, int x, int * rank);
void QuickSort(char ** words, int size, int insert, int x, int * rank);
char * FindMedian(char ** words, int l, int r, int x, int * rank);

#endif