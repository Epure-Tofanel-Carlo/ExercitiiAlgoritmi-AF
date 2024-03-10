#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//ifstream fin("dfs.in");
//ofstream fout("dfs.out");

const int NMAX = 100000;
vector<int> G[NMAX+1];
int color[NMAX+1];
int n, m;

bool DFS(int x, int c);

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    // initializam la -1 sa fie nevizitate
    for(int i = 1; i <= n; i++) {
        color[i] = -1;
    }

    bool isBipartite = true;
    for(int i = 1; i <= n; i++) {
        if(color[i] == -1) {
            if(!DFS(i, 0)) {    // pun !, ca daca returneasa false la check de bipartit, sa intru in if
                isBipartite = false;
                break;
            }
        }
    }

    if(isBipartite) {
        for(int i = 1; i <= n; i++) {
            cout << color[i] + 1 << " ";
        }
    } else {
        cout << "IMPOSSIBLE";
    }

    return 0;
}

bool DFS(int x, int c)
{
    color[x] = c;
    for(auto y : G[x])
    {
        if(color[y] == -1) {
            if(!DFS(y, 1-c)) {  // ''coloram'' cu culoarea opusa
                return false;
            }
        } else if(color[y] == c) { // daca e deja colorat, verificam sa nu fie la fel ca cel curent, daca e atunci nu e bipartit
            return false;
        }
    }
    return true;
}