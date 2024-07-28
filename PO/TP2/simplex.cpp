#include <iostream>
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

    void build_auxiliary();
    void build_primary();
    void pivot(struct tableau *T, int i, int j);
    void canonical(struct tableau *T);
    int negative_column(struct tableau *T);

    void ilimited();
    void inviable();
    void optimal();

public:
    simplex();
    ~simplex();

    void read_data();
    void print_tableau(struct tableau *T);
    void obj_value(struct tableau *T);
    void execute();
};

simplex::simplex()
{
}

simplex::~simplex()
{
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
    memset(auxiliary_tableau.M, 0, sizeof(double));

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
    memset(primary_tableau.M, 0, sizeof(double));

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
    std::cout << i << ' ' << j << std::endl;
    print_tableau(T);
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
void simplex::obj_value(struct tableau *T)
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
            ilimited();
            break;
        }
        else{
            B[r] = k;
        }

        canonical(T);
        k = negative_column(T);
    }
}
void simplex::execute()
{
    build_auxiliary();
    print_tableau(&auxiliary_tableau);
    obj_value(&auxiliary_tableau);

    if(auxiliary_tableau.M[0][2*n + m] < -eps){
        inviable();
        return;
    }

    build_primary();
    print_tableau(&primary_tableau);
    obj_value(&primary_tableau);
}
void simplex::ilimited()
{
    std::cout << "ilimited" << std::endl;
}
void simplex::inviable()
{
    std::cout << "inviable" << std::endl;
}
void simplex::optimal()
{
    std::cout << "optimal" << std::endl;
}

int main(){
    simplex S;

    S.read_data();
    S.execute();
}