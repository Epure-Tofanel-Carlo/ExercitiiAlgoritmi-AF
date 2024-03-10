#include <iostream>
#include <vector>
using namespace std;

// Clasa pentru citirea din fisier
class InParser {
private:
    FILE *fin;
    char *buff;
    int sp;

    // Functie pentru citirea unui caracter
    char citeste_caracter() {
        ++sp;
        if (sp == 4096) {
            sp = 0;
            fread(buff, 1, 4096, fin);
        }
        return buff[sp];
    }

public:
    // Constructor pentru deschiderea fisierului de intrare
    InParser(const char* nume) {
        fin = fopen(nume, "r");
        buff = new char[4096]();
        sp = 4095;
    }

    // Operator pentru citirea unui numar intreg
    InParser& operator >> (int &n) {
        char c;
        while (!isdigit(c = citeste_caracter()) && c != '-');
        int semn = 1;
        if (c == '-') {
            n = 0;
            semn = -1;
        } else {
            n = c - '0';
        }
        while (isdigit(c = citeste_caracter())) {
            n = 10 * n + c - '0';
        }
        n *= semn;
        return *this;
    }

    // Operator pentru citirea unui numar intreg lung
    InParser& operator >> (long long &n) {
        char c;
        n = 0;
        while (!isdigit(c = citeste_caracter()) && c != '-');
        long long semn = 1;
        if (c == '-') {
            n = 0;
            semn = -1;
        } else {
            n = c - '0';
        }
        while (isdigit(c = citeste_caracter())) {
            n = 10 * n + c - '0';
        }
        n *= semn;
        return *this;
    }
};

// Clasa pentru scrierea în fisier
class OutParser {
private:
    FILE *fout;
    char *buff;
    int sp;

    // Functie pentru scrierea unui caracter
    void scrie_caracter(char ch) {
        if (sp == 50000) {
            fwrite(buff, 1, 50000, fout);
            sp = 0;
            buff[sp++] = ch;
        } else {
            buff[sp++] = ch;
        }
    }

public:
    // Constructor pentru deschiderea fisierului de iesire
    OutParser(const char* nume) {
        fout = fopen(nume, "w");
        buff = new char[50000]();
        sp = 0;
    }
    // Destructor pentru scrierea bufferului în fisier și inchiderea fisierului
    ~OutParser() {
        fwrite(buff, 1, sp, fout);
        fclose(fout);
    }

    // Operator pentru scrierea unui număr intreg în fisier
    OutParser& operator << (int vu32) {
        if (vu32 <= 9) {
            scrie_caracter(vu32 + '0');
        } else {
            (*this) << (vu32 / 10);
            scrie_caracter(vu32 % 10 + '0');
        }
        return *this;
    }

    // Operator pentru scrierea unui numar intreg lung în fisier
    OutParser& operator << (long long vu64) {
        if (vu64 <= 9) {
            scrie_caracter(vu64 + '0');
        } else {
            (*this) << (vu64 / 10);
            scrie_caracter(vu64 % 10 + '0');
        }
        return *this;
    }

    // Operator pentru scrierea unui caracter în fisier
    OutParser& operator << (char ch) {
        scrie_caracter(ch);
        return *this;
    }
    // Operator pentru scrierea unui sir de caractere în fisier
    OutParser& operator << (const char *ch) {
        while (*ch) {
            scrie_caracter(*ch);
            ++ch;
        }
        return *this;
    }
};

InParser in("grafpond.in");
OutParser out("grafpond.out");

const int NMAX = 100;
const int INF = 1e9;
int matrice_costuri[NMAX][NMAX], urmator[NMAX][NMAX];

bool exista_ciclu;

void afiseaza_ciclu_negativ(int p)
{
    vector<int> cale;
    int nod = p;
    while(true)
    {
        nod = urmator[nod][p];
        cale.push_back(nod);
        if (nod == p) break;
    }
    for (int nod : cale) {
        out << nod << " ";
    }
}


void floyd_warshall(int &n)
{
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(matrice_costuri[i][j] > matrice_costuri[i][k] + matrice_costuri[k][j])
                {
                    matrice_costuri[i][j] = matrice_costuri[i][k] + matrice_costuri[k][j];
                    urmator[i][j] = urmator[i][k];
                }
                if(i == j && matrice_costuri[i][j] < 0)
                {
                    exista_ciclu = true;
                    out << "Ciclu de cost negativ\n";
                    afiseaza_ciclu_negativ(i);
                    return;
                }

            }
        }
    }
}
int main(int argc, const char * argv[])
{
    int n,m;
    in >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int x,y,c;
        in >> x >> y >> c;
        matrice_costuri[x][y] = c;
        urmator[x][y] = y;
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(i != j && matrice_costuri[i][j] == 0)
            {
                matrice_costuri[i][j] = INF;
            }
        }
    }
    floyd_warshall(n);
    if(!exista_ciclu)
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(matrice_costuri[i][j] == INF)
                {
                    matrice_costuri[i][j] = 0;
                }
                out << matrice_costuri[i][j] << " ";
            }
            out << "\n";
        }
    }
    return 0;
}
