#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e4;
int d[NMAX + 1]; //stocarea costurilor minime de la statii la statii initiale
bool vis[NMAX + 1];
vector<pair<int, int>> G[NMAX + 1]; //graf canalelo de comunicare

int main() {
    int t; //numarul de seturi de date
    cin >> t;
    while(t--) {
        int n, m, L, k; //n = numarul de statii | m = numarul de canale | L = marimea programului | k = numarul de statii initiale
        cin >> n >> m >> L >> k;
        set<pair<int, int>> s; //set pentru a alege urmatoarea statie cu costul minim

        for(int i = 1; i <= n; i++) {
            d[i] = 1e9;
            vis[i] = 0;
        }
        //initializam statiile unde programul este deja instalat
        for(int i = 1; i <= k; i++) {
            int x;
            cin >> x;
            d[x] = 0;
            s.insert({0, x});
        }
        //citim canalele si costurile lor
        for(int i = 1; i <= m; i++) {
            int x, y, c;
            cin >> x >> y >> c;
            G[x].push_back({y, c});
            G[y].push_back({x, c});
        }
        long long sol = 0;
        //cost minim activare canale, variatie Prim
        while(!s.empty()) {
            auto it = s.begin();
            int cost = it->first;
            int node = it->second;
            s.erase(it);
            if(vis[node]) continue;
            vis[node] = 1;
            sol += 1LL * cost;
            for(auto next : G[node]) {
                if(d[next.first] > next.second) {
                    d[next.first] = next.second;
                    s.insert({d[next.first], next.first});
                }
            }
        }
        //resetam graful pt urm set de date
        for(int i = 1; i <= n; i++) {
            G[i].clear();
        }
        //adaugam costul pt trasnmiterea programului pe fiecare canal activat
        sol += 1LL * (n - k) * L;
        cout << sol << '\n';
    }
    return 0;
}
