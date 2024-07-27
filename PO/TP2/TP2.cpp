#include <vector>
#include <iostream>
#include <cstring>

int n, m;
double a[100][100];
double b[100];
double c[100];

double tableau[310][310];
int B[100];

void read_instances(){
    std::cin >> n >> m;

    for(int i = 0; i < m; i++){
        std::cin >> c[i];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            std::cin >> a[i][j];
        }
        std::cin >> b[i];
    }
}

void make_tableau(){
    memset(tableau, 0, sizeof(double));

    // I_n for registering operations and b
    for(int i = 0; i < n; i++){
        tableau[i+1][i] = 1;
        tableau[i+1][i+n+m] = 1;

        tableau[0][i+n+m] = 1;
        tableau[i+1][2*n+m] = b[i];

        B[i] = i+n+m;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            tableau[i+1][j + n] = a[i][j];
        }
    }
}

// pivots position i,j from tableau
void pivot(int i, int j){
    for(int k = n; k < n+m; k++){
        tableau[i][k] /= tableau[i][j];
    }

    for(int k = 0; k < n+1; k++) if(k != i){
        double factor = tableau[k][j];

        for(int l = n; l < n+1; l++){
            tableau[k][l] -= tableau[i][l]*factor;
        }
    }
}

int main(){
    read_instances();

    make_tableau();

}