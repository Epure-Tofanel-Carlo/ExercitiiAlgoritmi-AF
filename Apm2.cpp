#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


const int MAXN = 10001;
const int MAXLOG = 14;


struct Edge {
    int x, y, weight;
};


vector<Edge> edges;
vector<int> parent(MAXN), nodeRank(MAXN); // vectori pentru a stoca parintele si rangul fiecarui nod
vector<vector<pair<int, int>>> adj(MAXN); // lista de adiacenta pentru fiecare nod
vector<vector<int>> up(MAXN, vector<int>(MAXLOG)); // matrice pentru a stoca stramosii
vector<vector<int>> maxEdge(MAXN, vector<int>(MAXLOG)); // matrice pentru a stoca greutatea maxima de pe calea spre stramosi
vector<int> depth(MAXN); // vector pentru a stoca adancimea fiecarui nod


bool compareEdges(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}


int find(int a) {
    if (a != parent[a]) {
        parent[a] = find(parent[a]);
    }
    return parent[a];
}

// functie pentru unirea a doua seturi
void unionSets(int a, int b, int weight) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (nodeRank[a] < nodeRank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (nodeRank[a] == nodeRank[b]) {
            nodeRank[a]++;
        }
    }
}

// parcurgere in adancime pentru a initializa 'up' si 'maxEdge'
void dfs(int v, int p, int w, int d) {
    up[v][0] = p;
    maxEdge[v][0] = w;
    depth[v] = d;
    for (int i = 1; i < MAXLOG; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
        maxEdge[v][i] = max(maxEdge[v][i - 1], maxEdge[up[v][i - 1]][i - 1]);
    }

    for (auto edge : adj[v]) {
        if (edge.first != p) {
            dfs(edge.first, v, edge.second, d + 1);
        }
    }
}

// functie pentru a gasi stramosul comun cel mai apropiat adica LCA si greutatea maxima de pe cale
int lca(int a, int b) {
    int maxWeight = 0;
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    int diff = depth[a] - depth[b];
    for (int i = 0; i < MAXLOG; i++) {
        if ((diff >> i) & 1) {
            maxWeight = max(maxWeight, maxEdge[a][i]);
            a = up[a][i];
        }
    }

    if (a == b) {
        return maxWeight;
    }

    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            maxWeight = max({maxWeight, maxEdge[a][i], maxEdge[b][i]});
            a = up[a][i];
            b = up[b][i];
        }
    }

    return max({maxWeight, maxEdge[a][0], maxEdge[b][0]});
}

int main() {
    ifstream fin("apm2.in");
    ofstream fout("apm2.out");

    int N, M, Q;
    fin >> N >> M >> Q;

    edges.resize(M); // facem resize la vectorul de muchii
    for (int i = 0; i < M; i++) {
        fin >> edges[i].x >> edges[i].y >> edges[i].weight;
    }

    sort(edges.begin(), edges.end(), compareEdges); // sortam muchiile dupa greutate

    for (int i = 1; i <= N; i++) {
        parent[i] = i; // initializam parintele fiecarui nod ca fiind el insusi
    }

    // construim arborele
    for (const Edge &e : edges) {
        if (find(e.x) != find(e.y)) {
            unionSets(e.x, e.y, e.weight);
            adj[e.x].push_back({e.y, e.weight});
            adj[e.y].push_back({e.x, e.weight});
        }
    }

    dfs(1, 0, 0, 0); // initializam 'up' si 'maxEdge' folosind DFS

    // procesam interogarile
    for (int i = 0; i < Q; i++) {
        int a, b;
        fin >> a >> b;

        int maxWeight = lca(a, b); // gasim LCA si greutatea maxima
        fout << maxWeight - 1 << endl; // scriem rezultatul in fisier
    }

    fin.close();
    fout.close();

    return 0;
}
