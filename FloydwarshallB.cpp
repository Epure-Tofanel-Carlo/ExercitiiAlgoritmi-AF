#include <vector>
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;

// clasa pentru citire rapida din fisier
class InParser {
private:
    FILE *fin;
    char *buff;
    int sp;

    // citeste un caracter din buffer
    char read_ch() {
        ++sp;
        if (sp == 4096) {
            sp = 0;
            fread(buff, 1, 4096, fin);
        }
        return buff[sp];
    }

public:
    // constructor
    InParser(const char* nume) {
        fin = fopen(nume, "r");
        buff = new char[4096]();
        sp = 4095;
    }

    // operatori pentru citirea numerelor
    InParser& operator >> (int &n) {
        char c;
        while (!isdigit(c = read_ch()) && c != '-');
        int sgn = 1;
        if (c == '-') {
            n = 0;
            sgn = -1;
        } else {
            n = c - '0';
        }
        while (isdigit(c = read_ch())) {
            n = 10 * n + c - '0';
        }
        n *= sgn;
        return *this;
    }

    InParser& operator >> (long long &n) {
        char c;
        n = 0;
        while (!isdigit(c = read_ch()) && c != '-');
        long long sgn = 1;
        if (c == '-') {
            n = 0;
            sgn = -1;
        } else {
            n = c - '0';
        }
        while (isdigit(c = read_ch())) {
            n = 10 * n + c - '0';
        }
        n *= sgn;
        return *this;
    }
};

class OutParser {
private:
    FILE *fout;
    char *buff;
    int sp;

    void write_ch(char ch) {
        if (sp == 50000) {
            fwrite(buff, 1, 50000, fout);
            sp = 0;
            buff[sp++] = ch;
        } else {
            buff[sp++] = ch;
        }
    }

public:
    OutParser(const char* name) {
        fout = fopen(name, "w");
        buff = new char[50000]();
        sp = 0;
    }
    ~OutParser() {
        fwrite(buff, 1, sp, fout);
        fclose(fout);
    }

    OutParser& operator << (int vu32) {
        if (vu32 <= 9) {
            write_ch(vu32 + '0');
        } else {
            (*this) << (vu32 / 10);
            write_ch(vu32 % 10 + '0');
        }
        return *this;
    }

    OutParser& operator << (long long vu64) {
        if (vu64 <= 9) {
            write_ch(vu64 + '0');
        } else {
            (*this) << (vu64 / 10);
            write_ch(vu64 % 10 + '0');
        }
        return *this;
    }

    OutParser& operator << (char ch) {
        write_ch(ch);
        return *this;
    }
    OutParser& operator << (const char *ch) {
        while (*ch) {
            write_ch(*ch);
            ++ch;
        }
        return *this;
    }
};

InParser in("grafpond.in");
OutParser out("grafpond.out");

const int NMAX = 1e3 + 1;
const int INF = 1e6;

int M[NMAX][NMAX],n,m,e[NMAX],rg,parent[NMAX][NMAX];
bool exista_ciclu;

vector<int>centru_graf;

// implementarea algoritmului floyd-warshall pentru calculul drumurilor minime
void floyd_warshall() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(M[i][k] + M[k][j] < M[i][j]) {
                    M[i][j] = M[i][k] + M[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
}

// calculeaza excentricitatea unui nod
int excentricitate_nod(int x) {
    int e = -1;
    for(int i = 1; i <= n; i++) {
        e = max(e, M[x][i]);
    }
    return e;
}

// calculeaza raza grafului
void raza_graf() {
    int r = INF;
    for(int i = 1; i <= n; i++) {
        r = min(r, e[i]);
    }
    rg = r;
}

// verifica daca un nod este in centrul grafului
bool validare(int nod) {
    return rg == e[nod];
}

// calculeaza diametrul grafului
int diametru_graf() {
    int dGraf = 0;
    for(int i = 1; i <= n; i++) {
        dGraf = max(dGraf, e[i]);
    }
    return dGraf;
}

int main(int argc, const char * argv[]) {
    in >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y, c;
        in >> x >> y >> c;
        M[x][y] = c;
        M[y][x] = c;
        parent[x][y] = x;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(M[i][j] == 0 && i != j) {
                M[i][j] = INF;
            }
        }
    }
    floyd_warshall();
    for(int i = 1; i <= n; i++) {
        e[i] = excentricitate_nod(i);
    }
    raza_graf();
    for(int i = 1; i <= n; i++) {
        if(validare(i)) {
            centru_graf.push_back(i);
        }
    }
    int dGraf = diametru_graf();
    out << "Raza: " << rg << "\n";
    out << "Centru: ";
    for(int i = (int) centru_graf.size() - 1; i >= 0; i--) {
        out << centru_graf[i] << " ";
    }
    out << "\n";
    out << "Diametru: " << dGraf << "\n";
    out << "Lant diametral: ";
    int a, b;
    int gasit = 0;
    for(int i = 1; i <= NMAX; i++ && gasit == 0) {
        for(int j = 1; j <= NMAX; j++ && gasit == 0) {
            if(M[i][j] == dGraf && gasit == 0) {
                a = i;
                b = j;
                gasit = 1;
            }
        }
    }
    vector<int> path;
    path.push_back(b);
    while(a != b) {
        b = parent[a][b];
        path.push_back(b);
    }
    reverse(path.begin(), path.end());
    for (auto elem : path) {
        out << elem << " ";
    }
    return 0;
}
