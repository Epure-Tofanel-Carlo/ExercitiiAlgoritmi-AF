#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream in("activitati.in");
ofstream out("activitati.out");

const int NMAX = 100;

int d[NMAX], d_proiect[NMAX], nrp[NMAX], parent[NMAX], n, m, start_time[NMAX];
vector<int> G[NMAX];
queue<int> q, ordine_sort;

// functia de inversare vector furata de pe net
void reverse(vector<int>::iterator iterator, vector<int>::iterator iterator1);

// bfs pentru sortarea topologica
// de la fara predecesori la cei in care sunt accesibili
void bfs() {
    while (!q.empty()) {
        int x = q.front();
        ordine_sort.push(x);
        q.pop();
        for (auto y : G[x]) {
            nrp[y]--;
            if (nrp[y] == 0) {
                q.push(y);
            }
        }
    }
}

// bfs pentru calculul timpului fiecarei activitati
// in ordine topologica, actualizam timpul de incepe si de finalizare

void bfs_timp() {
    for (int i = 1; i <= n; i++) {
        d_proiect[i] = -100;
    }
    d[0] = 0;
    while (!ordine_sort.empty()) {
        int x = ordine_sort.front();
        ordine_sort.pop();
        for (auto y : G[x]) {
            start_time[y] = max(start_time[y], start_time[x] + d[x]);
            if (d_proiect[x] + d[y] > d_proiect[y]) {
                d_proiect[y] = d_proiect[x] + d[y];
                parent[y] = x;
            }
        }
    }
}

// afisarea timpului minim si a activitatilor critice
// parcurgem inapoi drumul critic de la ultima la prima cu parent

void afisare_timp_minim(int &nod) {
    out << "Timp minim: " << d_proiect[nod] << " \n";
    vector<int> ordine_drum_critic;
    while (parent[nod] != 0) {
        ordine_drum_critic.push_back(nod);
        nod = parent[nod];
    }
    ordine_drum_critic.push_back(nod);
    reverse(ordine_drum_critic.begin(), ordine_drum_critic.end());
    out << "Activitati critice: ";
    for (auto nod : ordine_drum_critic) {
        out << nod << " ";
    }
    out << "\n";
}

// aveam nevoie de un reverse vector si am luat o de pe net
void reverse(vector<int>::iterator iterator, vector<int>::iterator iterator1) {
    vector<int>::iterator iterator2;
    iterator2 = iterator1 - 1;
    while (iterator < iterator2) {
        swap(*iterator, *iterator2);
        iterator++;
        iterator2--;
    }
}

// afisam intervalele pentru fiecare activitate
void afisare_activitati() {
    for (int i = 1; i <= n; i++) {
        out << i << ": " << "(" << start_time[i] << " " << start_time[i] + d[i] << ")" << "\n";
    }
}

int main(int argc, const char * argv[]) {
    in >> n; // nr activitati
    for (int i = 1; i <= n; i++) {
        int x;
        in >> x; // durata fiecarei activitati
        d[i] = x;
    }
    in >> m; // nr activitati dependente
    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y; // x depinde de y
        G[x].push_back(y);
        nrp[y]++; // ++ nr predecesory y
    }
    q.push(0);
    for (int i = 1; i <= n; i++) {
        if (nrp[i] == 0) {
            q.push(i); // adaugam in coada activitatile care nu depinde de altele
            G[0].push_back(i);
        }
    }
    bfs(); // topologic
    bfs_timp(); // timpul fiecarei activitati
    int timp_minim = -1;
    int nod = -1;
    for (int i = 1; i <= n; i++) {
        if (timp_minim < d_proiect[i]) {
            timp_minim = d_proiect[i];
            nod = i; // determinam activitatea cu timpul maxim
        }
    }
    afisare_timp_minim(nod); // timp minim & activitati critice
    afisare_activitati(); // intervalele pt fiecare activitate
    return 0;
}