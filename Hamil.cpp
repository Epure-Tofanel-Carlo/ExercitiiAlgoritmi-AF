#include <fstream>
#include <vector>
using namespace std;

ifstream in("hamil.in");
ofstream out("hamil.out");

const int NMAX = 19;
const int MMAX = (1 << 18) + 1;
const int INF = 1e9 + 1;

vector<pair<int,int>> G[NMAX]; // Lista de adiacenta, cu costul fiecarei muchii

int dp[MMAX][NMAX], n, m;

// Functia pentru calculul costului minim al unui ciclu hamiltonian
int ciclu_hamiltonian_cost_minim() {
    dp[1][0] = 0; // Initializare pentru nodul de start
    for (int masca = 0; masca < (1 << n); masca++) {
        for (int i = 0; i < n; i++) {
            if ((masca & (1 << i)) != 0) {
                for (auto next : G[i]) {
                    if ((masca & (1 << next.first)) != 0) {
                        // Actualizeaza costul minim pentru a ajunge la nodul i, cu nodul precedent fiind next.first
                        dp[masca][i] = min(dp[masca][i], dp[masca ^ (1 << i)][next.first] + next.second);
                    }
                }
            }
        }
    }
    // Calcul cost minim pentru ciclu hamiltonian complet
    int cost_minim = INF;
    for (auto nod : G[0]) {
        cost_minim = min(cost_minim, dp[(1 << n) - 1][nod.first] + nod.second);
    }
    return cost_minim;
}

int main(int argc, const char * argv[]) {
    in >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, c;
        in >> x >> y >> c; // Citeste muchiile si costul lor
        G[x].push_back({y, c});
    }
    in.close();

    // Initializare dp cu infinit
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }

    // Calcul cost minim ciclu hamiltonian
    int cost_minim = ciclu_hamiltonian_cost_minim();
    if (cost_minim == INF) {
        out << "Nu exista solutie\n";
    } else {
        out << cost_minim << "\n";
    }
    return 0;
}
