#include <iostream>
#include <cstring>

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
    int negative_column();

    void ilimited();
    void inviable();
    void optimal();

public:
    simplex();
    ~simplex();

    void read_data();
    void print_tableau(struct tableau T);
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
}
void simplex::build_primary()
{
    memset(primary_tableau.M, 0, sizeof(double));

    primary_tableau.n = n;
    primary_tableau.m = m;

    for(int i = 1; i < n+1; i++){
        for(int j = 0; j < n+m+1; j++){
            primary_tableau.M[i][j] = auxiliary_tableau.M[i][j];
        }
    }

    for(int i = 0; i < m; i++){
        primary_tableau.M[0][i+n] = -c[i];
    }
}