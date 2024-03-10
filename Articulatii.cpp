#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e5;
vector<int> G[NMAX + 1];
int d[NMAX + 1], low[NMAX + 1], cnt, sol;// timpul de descoperire, cel mai mic timp de descoperire la care putem ajunge de la nod
int art[NMAX + 1], h, vis[NMAX + 1], r;

void dfs(int x, int p) {// DFS cu nodul curent x si parintele p
    vis[x] = 1;
    h++;
    d[x] = low[x] = h; // height++, discovery time
    for(auto next : G[x]) { // daca nodul adiacent nu este vizitat
        if(!vis[next]) {  // DFS pe nodul adiacent
            dfs(next, x); // daca nodul curent este radacina
            low[x] = min(low[x], low[next]); // incrementam contorul de copii ai radacinii
            if(x == r) { // vf daca x e punct de articulatie
                cnt++;
            } else {
                if(low[next] >= d[x]) {
                    art[x] = 1;
                }
            }
        } else {
            if(next != p) {
                low[x] = min(low[x], d[next]);
            }
        }
    }
}

int main() {
    while(true) {
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) {
            break;
        }
        while(m--) { // citim muchiile
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        r = 1; // radacina la dfs
        sol = 0;
        cnt = 0;
        h = 0;
        dfs(r, 0);
        if(cnt >= 2) { // daca radacina are mai mult de 2 copii, e punct de articulatie
            art[1] = 1;
        }
        for(int i = 1; i <= n; i++) {
            if(art[i] == 1) {
                sol++;
            }
        }
        for(int i = 1; i <= n; i++) {
            G[i].clear();
            art[i] = vis[i] = d[i] = low[i] = 0;
        }
        cout << sol << '\n';
    }
    return 0;
}