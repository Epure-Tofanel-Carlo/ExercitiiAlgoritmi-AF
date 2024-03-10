#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <climits>
using namespace std;

const int NMAX = 100005;

int parent[NMAX], edg;
vector<int> muchii_folosite;  // indexii edge uri folosite

struct edge
{
    int x, y, c;
} edges[NMAX];

bool cmp(edge x, edge y)
{
    return x.c < y.c;
}

void initialise(int n)
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = 0;
    }
}

int find(int x)
{
    if (parent[x] == 0)
    {
        return x;  // radacina
    }
    return parent[x] = find(parent[x]);
}

int union1(int i, int sum)
{
    int x, y;
    x = find(edges[i].x);
    y = find(edges[i].y);
    if (x != y) {
        parent[x] = y;  // unim cele 2 componente prin parinte
        muchii_folosite.push_back(i);  // adaugam muchie folosita
        sum += edges[i].c;  // crestem suma totala cu costul
    }
    return sum;
}

int union2(int i, int sum)
{
    int x, y;
    x = find(edges[i].x);
    y = find(edges[i].y);
    if (x != y) {
        parent[x] = y;  // la fel ca mai sus dar contorizam edge urile
        sum += edges[i].c;
        edg++;
    }
    return sum;
}

int main()
{
    int n, m;
    cin >> n >> m;

    initialise(n);

    for(int i = 0; i < m; i++)
    {
        cin >> edges[i].x >> edges[i].y >> edges[i].c;
    }

    sort(edges, edges + m, cmp);

    int sum = 0;
    for (int i = 0; i < m; i++)
    {
        sum = union1(i, sum);  // primul arbore minim de acoperire
    }
    cout << sum << " ";

    int sec_best_mst = INT_MAX;
    sum = 0;
    for (int j = 0; j < muchii_folosite.size(); j++)
    {
        initialise(n);
        edg = 0;
        for (int i = 0; i < m; i++)
        {
            if (i == muchii_folosite[j])
            {
                continue;
            }
            sum = union2(i, sum);
        }
        if (edg != n - 1)
        {
            sum = 0;  // daca nu are exact - 1 muchii, ignoram
            continue;
        }
        if (sec_best_mst > sum)
        {
            sec_best_mst = sum;
        }
        sum = 0;
    }

    cout << sec_best_mst;
    return 0;
}
