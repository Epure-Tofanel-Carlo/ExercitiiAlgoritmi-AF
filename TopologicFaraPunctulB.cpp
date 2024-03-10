#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 100000;
vector<int> G[NMAX + 1];
int state[NMAX + 1]; // 0 = nevizitat, 1 = in cautarea curenta, 2 = completat
vector<int> result; // lista de cursuri in ordinea date dee sortul topologic
int n, m;
bool Cycle = false;

void DFS(int x);

int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
    }

    for(int i = 1; i <= n; i++) {
        if(state[i] == 0) {
            DFS(i);
            if(Cycle) break; // daca am gasit ciclu ne oprim
        }
    }

    if(Cycle) {
        cout << "IMPOSSIBLE";
    } else {
        // printam in ordine inversa ca DFS u ne da de la ultimul spre primul cand le adaugam in lista
        for(int i = result.size() - 1; i >= 0; i--) {
            cout << result[i] << " ";
        }
    }

    return 0;
}

void DFS(int x) {
    if(state[x] == 1) {
        // am gasit un ciclu, ca e deja in cautarea curenta
        Cycle = true;
        return;
    }
    if(state[x] == 2) {
        // deja e completat, deci nu ne intereseaza
        return;
    }

    state[x] = 1; // marcam nodul curent ca a fi in cautarea curenta
    for(auto i : G[x]) {
        if(state[i] != 2) {
            DFS(i);
            if(Cycle) return; // daca am gasit un ciclu, nu e nevoie sa continuam
        }
    }
    state[x] = 2; // marcam ca si completat si adaugam in lista
    result.push_back(x);
}