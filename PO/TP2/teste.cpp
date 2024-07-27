#include <vector>
#include <iostream>
#include <cstring>

const int INF = 0x3f3f3f3f;

int n, m;
double a[100][100];
double b[100];
double c[100];

double tableau[310][310];
int B[100];

double sol[200];

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

void print_tableau(){
    for(int i = 0; i < n+1; i++){
        for(int j = 0; j < 2*n+m+1; j++){
            std::cout << tableau[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// pivots position i,j from tableau
void pivot(int i, int j){

    std::cout << i << ' ' << j << std::endl;
    print_tableau();

    double aux = tableau[i][j];

    for(int k = 0; k < 2*n+m+1; k++){
        tableau[i][k] /= aux;
    }
    print_tableau();

    for(int k = 0; k < n+1; k++) if(k != i){
        double factor = tableau[k][j];

        for(int l = 0; l < 2*n+m+1; l++){
            tableau[k][l] -= tableau[i][l]*factor;
        }
    }
    print_tableau();
}

void canonical(){
    for(int i = 0; i < n; i++)
        pivot(i+1, B[i]);
}



int found_solution(){
    
    for(int i = n; i < n+m; i++){
        if(tableau[0][i] < 0) return i;
    }

    return -1;
}

void ilimited(){
    std::cout << "a\n";
}

void simplex(){

    make_tableau();
    canonical();

    int k = found_solution();

    while(k != -1){

        int r = -1;
        double t = INF;

        for(int i = 1; i < n+1; i++) if(tableau[i][k] > 0){
            if(tableau[i][2*n+m] / tableau[i][k] < t){
                t = tableau[i][2*n+m] / tableau[i][k];
                r = i-1;
            }
        }


        if(r == -1){
            ilimited();
            break;
        }

        else{
            B[r] = k;
        }
        canonical();

        k = found_solution();
    }
}



int main(){
    read_instances();
    simplex();

    print_tableau();
}