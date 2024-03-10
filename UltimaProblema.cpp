#include <iostream>
#include <vector>
#include <queue>
//#include <fstream>
using namespace std;

//ifstream fin("graf.in");
//ofstream fout("graf.out"); // sa imi fie mai usor la testat oriunde

const int NMAX = 100000;
vector<int> G[NMAX + 1];
queue<int> q;
int d[NMAX + 1];
int n, m;

void BFS()  // apelam bfs pt toate punctele de control si le notam distantele
{

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (int next : G[node])
        {
            if (d[next] == INT_MAX)
            {
                q.push(next);
                d[next] = d[node] + 1;
            }
        }
    }
}

int main() {
    int x;
    cin >> n >> m >> x;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (int i = 1; i <= n; i++)
    {
        d[i] = INT_MAX;
    }

    int control_point;

    while (x > 0)
    {
        cin>>control_point;
        q.push(control_point);
        d[control_point] = 0;
        x--;
    }



    BFS();

    for (int i = 1; i <= n; i++)
    {
        if (d[i] == INT_MAX)
        {
            cout << -1 << " ";
        } else
        {
            cout << d[i] << " ";
        }
    }
    //fin.close();
    //fout.close();
    return 0;
}
