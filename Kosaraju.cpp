#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int NMAX = 1e5 + 1;
int viz[NMAX],kingdomlist[NMAX],newkingdom;
vector <int> G[NMAX],GT[NMAX];
stack <int> s;


void dfs_t(int x);
void dfs(int x);

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        GT[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        if (viz[i] != 1) {
            dfs(i);
        }
    }
    while (!s.empty()) {
        int x = s.top();
        s.pop();
        if (viz[x] != 2) {
            newkingdom++;
            dfs_t(x);
        }
    }
    cout << newkingdom << "\n";
    for (int i = 1; i <= n; i++) {
        cout << kingdomlist[i] << " ";
    }
    return 0;
}

void dfs_t(int x)
{
    viz[x] = 2;
    kingdomlist[x] = newkingdom;
    for(auto y : GT[x])
    {
        if(viz[y] != 2)
        {
            dfs_t(y);
        }
    }
}

void dfs(int x)
{
    viz[x] = true;
    for(auto y : G[x])
    {
        if(!viz[y])
        {
            dfs(y);
        }
    }
    s.push(x);
}

