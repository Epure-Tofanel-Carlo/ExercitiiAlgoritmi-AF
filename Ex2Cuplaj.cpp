#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const int INF = 1e9;

struct Edge {
    int src, dest;
};

// Functia BFS pentru algoritmul Ford-Fulkerson
bool BFS(vector<vector<int>> &G, int s, int t, vector<int> &parent) {
    int size_of_graph = (int)G.size();
    vector<bool> visited(size_of_graph, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < size_of_graph; v++) {
            if (!visited[v] && G[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t) {
                    return true;
                }
            }
        }
    }

    return false;
}

// Algoritmul Ford-Fulkerson pentru calculul fluxului maxim
int FordFulkerson(vector<vector<int>> &G, int s, int t) {
    int size_of_graph = (int)G.size();
    vector<int> parent(size_of_graph, -1);

    int max_flow = 0;
    while (BFS(G, s, t, parent)) {
        int path_flow = INF;
        for (int next = t; next != s; next = parent[next]) {
            int nod = parent[next];
            path_flow = min(path_flow, G[nod][next]);
        }
        for (int next = t; next != s; next = parent[next]) {
            int nod = parent[next];
            G[nod][next] -= path_flow;
            G[next][nod] += path_flow;
        }
        max_flow += path_flow;
    }

    return max_flow;
}

// BFS pentru verificarea daca un graf este bipartit prin colorare
bool BFS_verifica_Bipartit_prin_colorare(vector<vector<int>> G, int nod, vector<int> &culori) {
    culori[nod] = 1;
    vector<int> tata(G.size(), -1);
    queue<int> q;
    q.push(nod);

    while (!q.empty()) {
        nod = q.front();
        q.pop();
        for (auto next : G[nod]) {
            if (!culori[next]) {
                culori[next] = 3 - culori[nod];
                tata[next] = nod;
                q.push(next);
            }
            else if (culori[next] == culori[nod]) {
                // Detectarea ciclului impar si afisarea acestuia
                vector<int> left, right;
                int start = nod, end = next;

                while (start != -1) {
                    right.push_back(start);
                    start = tata[start];
                }

                while (end != -1) {
                    left.push_back(end);
                    end = tata[end];
                }

                out << "Ciclu impar: ";
                reverse(left.begin(), left.end());
                for (auto varf : left) {
                    out << varf << " ";
                }
                for (auto varf : right) {
                    out << varf << " ";
                }
                out << "\n";

                return false;
            }
        }
    }
    return true;
}

int main() {
    int N, M, u, v;
    in >> N >> M;
    int V = N + 3;
    int s = 1, t = V - 1;

    vector<vector<int>> grafFlux(V, vector<int>(V, 0));
    vector<vector<int>> grafBFS(N+1, vector<int>());
    vector<Edge> Muchii;

    for (int i = 1; i <= M; i++) {
        in >> u >> v;
        grafBFS[u].push_back(v);
        grafBFS[v].push_back(u);
        Edge edge{u, v};
        Muchii.push_back(edge);
    }

    vector<int> culori(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        if(!culori[i]) {
            if(!BFS_verifica_Bipartit_prin_colorare(grafBFS, i, culori)) {
                out << "Graful NU este Bipartit!";
                return 0;
            }
        }
    }

    for (int nod = 1; nod <= N; ++nod) {
        if(culori[nod] == 1) {
            grafFlux[s][s+nod] = 1;
            for(auto next : grafBFS[nod]) {
                grafFlux[s+nod][s+next] = 1;
            }
        }
        else {
            grafFlux[s+nod][t] = 1;
            for(auto next : grafBFS[nod]) {
                grafFlux[s+next][s+nod] = 1;
            }
        }
    }

    FordFulkerson(grafFlux, s, t);

    for(auto [src, dest] : Muchii){
        if(culori[src] == 1) {
            if(grafFlux[s][s + src] == 0 && grafFlux[s + src][s + dest] == 0 && grafFlux[s + dest][t] == 0) {
                out << src << " " << dest << "\n";
            }
        }
        else {
            if(grafFlux[s][s + dest] == 0 && grafFlux[s + dest][s + src] == 0 && grafFlux[s + src][t] == 0) {
                out << src << " " << dest << "\n";
            }
        }
    }
    return 0;
}
