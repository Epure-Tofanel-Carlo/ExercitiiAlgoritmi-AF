//LISTE DE ADIACENTA
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
ifstream fin("bfs.in");
ofstream fout("bfs.out");

const int NMAX=100000;
vector <int> G[NMAX+1];
queue <int> q;
bool vis[NMAX+1];
int d[NMAX+1];
int n, m;

void BFS(int x);

int main()
{
    int z;
    fin >> n >> m >> z;
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        // G[y].push_back(x);
    }

    /* Printu la graf
     for(int i = 1; i <= n; i++)
     {
         for(auto x:G[i])
         {
             cout << x << " ";
         }
         cout << endl;
     }
     */

    for (int i = 1; i <= n; i++)
        d[i] = -1;
    BFS(z);

    for (int i = 1; i <= n; i++)
    {
        fout << d[i];
        if (i != n)
            fout << " ";
    }
    fin.close();
    fout.close();
    return 0;
}

void BFS(int x)
{
    q.push(x);
    d[x] = 0;
    vis[x] = true;
    while(!q.empty())
    {
        int y = q.front();
        q.pop();
        for(auto i : G[y])
        {
            if(!vis[i])
            {
                q.push(i);
                vis[i] = true;
                d[i] = d[y] + 1;
            }
        }
    }
}


