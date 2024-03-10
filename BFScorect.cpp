#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

// Definirea constantei pentru numarul maxim de noduri
const int NMAX = 100000;

// Lista de adiacenta si alte variabile globale
ifstream fin("bfs.in");
ofstream fout("bfs.out");
vector<int> G[NMAX + 1]; // Lista de adiacenta
queue<int> q;            // Coada folosita in BFS
bool vis[NMAX + 1];      // Vector de vizitare
int d[NMAX + 1];         // Distanta de la nodul sursa la restul nodurilor
int n, m;                // Numarul de noduri si muchii

// Prototipul functiei BFS
void BFS(int x);

int main()
{
    int z;
    fin >> n >> m >> z; // Citirea numarului de noduri, muchii si nodul sursa

    // Citirea muchiilor si construirea listei de adiacenta
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        // G[y].push_back(x); // Decomenteaza pentru graf neorientat
    }

    // Initializarea distantelor cu -1
    for (int i = 1; i <= n; i++)
        d[i] = -1;

    // Apelul functiei BFS
    BFS(z);

    // Afisarea distantelor
    for (int i = 1; i <= n; i++)
    {
        fout << d[i];
        if (i != n)
            fout << " ";
    }

    // Inchiderea fisierelor
    fin.close();
    fout.close();
    return 0;
}

// Functia BFS
void BFS(int x)
{
    // Initializarea cozii si marcarea nodului sursa
    q.push(x);
    d[x] = 0;
    vis[x] = true;

    // Parcurgerea grafului
    while (!q.empty())
    {
        int y = q.front();
        q.pop();
        for (auto i : G[y])
        {
            // Verificarea daca nodul a fost vizitat
            if (!vis[i])
            {
                // Adaugarea nodului in coada si actualizarea distantelor
                q.push(i);
                vis[i] = true;
                d[i] = d[y] + 1;
            }
        }
    }
}
