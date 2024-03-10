#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;

ifstream in("retea.in");
ofstream out("retea.out");

const int NMAX = 101;
const int INF = 1e8;
int capacitate[NMAX][NMAX], flux[NMAX][NMAX], p[NMAX];
int n,m;
vector <int> G[NMAX];
bitset <NMAX> vizitat;

// Implementarea algoritmului Edmonds-Karp pentru flux maxim
int Edmonds_Karp(int s, int d) {
    queue <int> q;
    int flow = INF;

    q.push(s);
    vizitat[s] = true;
    while(!q.empty()) {
        int nod = q.front();
        q.pop();
        for(auto next : G[nod]) {
            if(capacitate[nod][next] - flux[nod][next] > 0 && !vizitat[next]) {
                p[next] = nod;
                q.push(next);
                vizitat[next] = true;
            }
            if(next == d) {
                // parcurge drumul si actualizeaza fluxul
                int dest_curr = d;
                int sursa_curr = s;
                while(dest_curr != sursa_curr) {
                    flow = min(flow, capacitate[p[dest_curr]][dest_curr] - flux[p[dest_curr]][dest_curr]);
                    dest_curr = p[dest_curr];
                }
                return flow;
            }
        }
    }
    return 0;
}

// Calculeaza fluxul maxim folosind Edmonds-Karp
int maxFlow(int s, int d) {
    int sum = 0;
    while(true) {
        int f = Edmonds_Karp(s, d);
        sum += f;
        if(f == 0) {
            break;
        } else {
            int desc = d, sursa = s;
            while(desc != sursa) {
                flux[p[desc]][desc] += f;
                flux[desc][p[desc]] -= f;
                desc = p[desc];
            }
        }
    }
    return sum;
}

// Verifica daca reteaua respecta conditiile de a mentine fluxul
bool cond_conservare_flux(int &s, int &d) {
    for(int nod = 1; nod <= n; nod++) {
        if(nod == s || nod == d) continue;
        int f_val = 0;
        for(int nod_n = 1; nod_n <= n; nod_n++) {
            f_val += flux[nod][nod_n];
        }
        if(f_val != 0) return true;
    }
    return false;
}

// DFS pentru identificarea nodurilor accesibile din sursa
void dfs(int nod, int s) {
    vizitat[nod] = true;
    for(auto next : G[nod]) {
        if(!vizitat[next] && capacitate[nod][next] - flux[nod][next] > 0) {
            dfs(next, s);
        }
    }
}

// Identifica si afiseaza taietura minima din retea
void taietura_minima(int &start) {
    vizitat.reset();
    dfs(start, start);
    for(int i = 1; i <= n; i++) {
        for(auto next: G[i]) {
            if(vizitat[i] && !vizitat[next] && capacitate[i][next] > 0) {
                out << i << " " << next << "\n";
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    int s,d;
    in >> n >> s >> d >> m;
    for(int i = 0; i < m; i++) {
        int x, y, c, f;
        in >> x >> y >> c >> f;
        G[x].push_back(y);
        G[y].push_back(x);
        if(f < 0 || f > c) {
            out << "Flux u nu respecta conditia pt marginirea de muchie" << x << "  -  " << y << '\n';
        }
        capacitate[x][y] = c;
        flux[x][y] += f;
        flux[y][x] -= f;
    }
    in.close();

    // Verifica daca reteaua respecta legea conservarii fluxului
    if(cond_conservare_flux(s, d)) {
        out << "NU\n";
        return 0;
    } else {
        out << "DA\n";
    }

    // Calculeaza si afiseaza fluxul maxim
    int flux_val = 0;
    for(auto next : G[s]) {
        flux_val += flux[s][next];
    }
    int flux_max = flux_val + maxFlow(s, d);
    out << flux_max << "\n";

    // Afiseaza fluxurile pe muchii
    for(int i = 1; i <= n; i++) {
        for(auto next : G[i]) {
            if(flux[i][next] >= 0 && capacitate[i][next] > 0) {
                out << i << " " << next << " " << flux[i][next] << "\n";
            }
        }
    }

    // Calculeaza si afiseaza taietura minima
    out << flux_max << "\n";
    taietura_minima(s);
    out.close();
    return 0;
}
