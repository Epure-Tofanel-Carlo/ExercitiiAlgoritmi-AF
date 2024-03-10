#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream in("secvente.in");

const int INF = 1e9;
const int NMAX = 100;

int n, s, t, sumaGradeInt, sumaGradeExt;
int capacitate[NMAX + 1][NMAX + 1], flux[NMAX + 1][NMAX + 1];
int p[NMAX + 1];

vector<int>G[NMAX + 1];
vector<int> gradeInt;
vector<int> gradeExt;


// Implementarea algoritmului Edmonds-Karp pentru gasirea fluxului maxim
int EdmondsKarp(int src, int dest)
{
    queue<int> q;

    int viz[NMAX + 1] = {0};
    int flow = INF;

    bool ajunge_la_destinatie = false;

    q.push(src);
    viz[src] = 1;

    while(!q.empty())
    {
        int nod = q.front();
        q.pop();

        for(auto next : G[nod])
        {
            if(capacitate[nod][next] - flux[nod][next] > 0 && !viz[next])
            {
                p[next] = nod;
                q.push(next);
                viz[next] = 1;

                if(next == dest)
                {
                    ajunge_la_destinatie = true;
                }
            }
        }
    }

    if(!ajunge_la_destinatie)
    {
        return 0;
    }

    int nod_curent = p[dest];

    while(nod_curent != 0)
    {
        if(capacitate[nod_curent][dest] != 0)
        {
            flow = min(flow, capacitate[nod_curent][dest] - flux[nod_curent][dest]);
        }
        else
        {
            if (capacitate[dest][nod_curent] != 0)
            {
                flow = min(flow, flux[dest][nod_curent]);
            }
        }
        dest = nod_curent;
        nod_curent = p[nod_curent];
    }
    return flow;
}

int maxFlow(int src, int dest)
{
    int sum = 0;

    for(auto next : G[src])
    {
        sum += flux[src][next];
    }
    while(true)
    {
        int fl = EdmondsKarp(src, dest);
        sum += fl;
        if(fl == 0)
            break;
        else
        {
            int t = dest;
            while(t != 0)
            {
                flux[p[t]][t] += fl;
                flux[t][p[t]] -= fl;
                t = p[t];
            }
        }
    }

    return sum;
}

void afisareArce()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j < G[i].size(); j++)
        {
            if(G[i][j] != 0 && capacitate[i][G[i][j]] == 1 && flux[i][G[i][j]] == 1)
            {
                cout << i << " " << G[i][j] - n << "\n";
            }
        }
    }
}

int main()
{
    in >> n;
    for(int i = 0 ; i < n; i++) // grade interioare
    {
        int x;
        in >> x;
        sumaGradeInt += x;
        gradeInt.push_back(x);
    }

    for(int i = 0 ; i < n; i++) //grade exterioare
    {
        int x;
        in >> x;
        sumaGradeExt += x;
        gradeExt.push_back(x);
    }
    // Constructia retelei de flux
    for(int i = 1; i <= n; i++)
    {
        G[0].push_back(i);
        G[i].push_back(0);
        capacitate[0][i] = gradeExt[i - 1];
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = n + 1; j <= 2 * n; j++)
        {
            if(j - n != i)
            {
                G[i].push_back(j);
                G[j].push_back(i);
                capacitate[i][j] = 1;
            }
        }
    }

    for(int i = n + 1; i <= 2 * n; i++)
    {
        G[i].push_back(2 * n + 1);
        G[2 * n + 1].push_back(i);
        capacitate[i][2 * n + 1] = gradeInt[i - n - 1];
    }
    // Setarea sursa si destinatie in retea
    s = 0;
    t = 2 * n + 1;
    int flowMax = maxFlow(s, t);

    if (flowMax != sumaGradeInt || flowMax != sumaGradeExt || sumaGradeInt != sumaGradeExt)
    {
        cout << "NU" << "\n";
    }
    else
    {
        afisareArce();
    }

    in.close();

    return 0;
}
