#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Definirea constantei pentru numarul maxim de noduri
const int NMAX = 100000;

// Lista de adiacenta si alte variabile globale
ifstream fin("dfs.in");
ofstream fout("dfs.out");
vector<int> G[NMAX + 1]; // Lista de adiacenta
bool vis[NMAX + 1];      // Vector de vizitare
int n, m;                // Numarul de noduri si muchii

// Prototipul functiei DFS
void DFS(int x);

int main()
{
    fin >> n >> m; // Citirea numarului de noduri si muchii

    // Citirea muchiilor si construirea listei de adiacenta
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        // G[y].push_back(x); // Decomenteaza pentru graf neorientat
    }

    // Apelul functiei DFS pentru fiecare componenta conexa
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            DFS(i);
        }
    }

    // Inchiderea fisierelor
    fin.close();
    fout.close();
    return 0;
}

// Functia DFS
void DFS(int x)
{
    // Marcarea nodului curent ca vizitat
    vis[x] = true;

    // Recursivitatea pentru vizitarea nodurilor adiacente
    for (auto i : G[x])
    {
        if (!vis[i])
        {
            DFS(i);
        }
    }
}
