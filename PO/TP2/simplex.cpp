#include <iostream>
#include <iomanip>
#include <cstring>

const int INF = 0x3f3f3f3f;
const double eps = 1e-6;

class simplex
{
private:

    int n, m;

    struct tableau
    {
        int n, m;
        double M[300][300];
    };

    struct tableau auxiliary_tableau;
    struct tableau primary_tableau;
    
    double a[100][100];
    double b[100];
    double c[100];

    int B[100];
    double certificate[100];
    double viable_solution[100];

    void build_auxiliary();
    void build_primary();
    void pivot(struct tableau *T, int i, int j);
    void canonical(struct tableau *T);
    int negative_column(struct tableau *T);

    void ilimited(struct tableau *T, int k);
    void inviable(struct tableau *T);
    void optimal(struct tableau *T);

public:
    simplex();

    void read_data();
    void print_tableau(struct tableau *T);
    double obj_value(struct tableau *T);
    void execute();
};

simplex::simplex()
{
    for(int i = 0; i < 100; i++){
        certificate[i] = 0;
        viable_solution[i] = 0;
    }

    for(int i = 0; i < 300; i++){
        for(int j = 0; j < 300; j++){
            auxiliary_tableau.M[i][j] = 0;
            primary_tableau.M[i][j] = 0;
        }
    }
}

void simplex::read_data()
{
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

void simplex::build_auxiliary()
{
    auxiliary_tableau.n = n;
    auxiliary_tableau.m = m + n;

    for(int i = 0; i < n; i++){
        auxiliary_tableau.M[i+1][i] = 1;
        auxiliary_tableau.M[i+1][i+n+m] = 1;

        auxiliary_tableau.M[0][i+n+m] = 1;
        auxiliary_tableau.M[i+1][2*n+m] = b[i];

        B[i] = i+n+m;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            auxiliary_tableau.M[i+1][j+n] = a[i][j]; 
        }
    }

    for(int i = 0; i < n; i++){
        if(b[i] < 0){
            auxiliary_tableau.M[i+1][2*n+m] = -auxiliary_tableau.M[i+1][2*n+m];

            for(int j = 0; j < n+m; j++){
                auxiliary_tableau.M[i+1][j] = -auxiliary_tableau.M[i+1][j];
            }
        }
    }
}
void simplex::build_primary()
{
    primary_tableau.n = n;
    primary_tableau.m = m;

    for(int i = 1; i < n+1; i++){
        for(int j = 0; j < n+m; j++){
            primary_tableau.M[i][j] = auxiliary_tableau.M[i][j];
        }

        primary_tableau.M[i][n+m] = auxiliary_tableau.M[i][2*n + m];
    }

    for(int i = 0; i < m; i++){
        primary_tableau.M[0][i+n] = -c[i];
    }
}
void simplex::print_tableau(struct tableau *T)
{
    for(int i = 0; i < T->n + 1; i++){
        for(int j = 0; j < T->m + T->n + 1;  j++){
            std::cout << T->M[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
void simplex::pivot(struct tableau *T, int i, int j)
{
    if(j >= T->n + T->m)
        return;

    double norm = T->M[i][j];

    for(int k = 0; k < T->n + T->m + 1; k++){
        T->M[i][k] /= norm;
    }

    for(int k = 0; k < T->n + 1; k++) if(k != i){
        double factor = T->M[k][j];

        for(int l = 0; l < T->n + T->m + 1; l++){
            T->M[k][l] -= T->M[i][l] * factor;
        }
    }
    //std::cout << i << ' ' << j << std::endl;
    //print_tableau(T);
}
void simplex::canonical(struct tableau *T)
{
    for(int i = 0; i < n; i++)
        pivot(T, i+1, B[i]);
}
int simplex::negative_column(struct tableau *T)
{
    int ret = -1;
    int aux = 0;

    for(int i = T->n; i < T->n + T->m; i++){
        if(T->M[0][i] < aux){
            aux = T->M[0][i];
            ret = i;
        } 
    }

    return ret;
}
double simplex::obj_value(struct tableau *T)
{

    canonical(T);
    int k = negative_column(T);

    while(k != -1){

        int r = -1;
        double t = INF;

        for(int i = 1; i < T->n + 1; i++) if(T->M[i][k] > 0){
            if(T->M[i][T->n + T->m] / T->M[i][k] < t){
                t = T->M[i][T->n + T->m] / T->M[i][k];
                r = i-1;
            }
        }

        if(r == -1){
            ilimited(T, k);
            return INF;
        }
        else{
            B[r] = k;
        }

        canonical(T);
        k = negative_column(T);
    }

    return T->M[0][T->n + T->m];
}
void simplex::execute()
{
    build_auxiliary();
    //print_tableau(&auxiliary_tableau);
    double sol = obj_value(&auxiliary_tableau);

    if(sol < -eps){
        inviable(&auxiliary_tableau);
        return;
    }
    else if(sol == INF){
        return;
    }

    build_primary();
    //print_tableau(&primary_tableau);
    sol = obj_value(&primary_tableau);

    if(sol == INF){
        return;
    }
    else{
        optimal(&primary_tableau);
    }
}
void simplex::ilimited(struct tableau *T, int k)
{
    std::cout << "ilimitada" << std::endl;

    certificate[k - T->n] = 1;

    for(int i = 0; i < n; i++) if(B[i] < T->m + T->n){
        viable_solution[B[i] - T->n] = T->M[i+1][T->n + T->m];
        certificate[B[i] - T->n] = -T->M[i+1][k];
    }

    for(int i = 0; i < m; i++){
        std::cout << viable_solution[i] << ' ';
    }
    std::cout << std::endl;

    for(int i = 0; i < m; i++){
        std::cout << certificate[i] << ' ';
    }

    std::cout << std::endl;
}
void simplex::inviable(struct tableau *T)
{
    std::cout << "inviavel" << std::endl;

    for(int i = 0; i < n; i++){
        std::cout << T->M[0][i] << ' ';
    }
    std::cout << std::endl;
}
void simplex::optimal(struct tableau *T)
{
    std::cout << "otima" << std::endl;
    std::cout << T->M[0][T->n + T->m] << std::endl;

    for(int i = 0; i < n; i++) if(B[i] < T->m + T->n){
        viable_solution[B[i] - T->n] = T->M[i+1][T->n + T->m];
    }

    for(int i = 0; i < m; i++){
        std::cout << viable_solution[i] << ' ';
    }
    std::cout << std::endl;

    for(int i = 0; i < n; i++){
        std::cout << T->M[0][i] << ' ';
    }
    std::cout << std::endl;
}
int main(){
    std::cout << std::setprecision(3);
    struct simplex S = simplex();

    S.read_data();
    S.execute();
}