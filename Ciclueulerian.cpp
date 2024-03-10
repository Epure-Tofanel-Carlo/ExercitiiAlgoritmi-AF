#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const int NMAX = 1e4 + 1;

vector <int> G[NMAX]; // Lista de adiacenta pentru fiecare nod
int grad[NMAX]; // Gradul fiecarui nod

// Functia pentru afisarea unui circuit eulerian
void print_circuit(const vector<int> &circuit) {
    if (circuit.size() == 0) {
        out << "Nu exista circuit eulerian\n";
        return;
    }
    for (int i = (int)circuit.size() - 1; i >= 0; i--) {
        out << circuit[i] << " ";
    }
}

// Functia pentru gasirea unui ciclu eulerian folosind Hierhozen
void gasire_ciclu() {
    stack <int> s;
    s.push(1); // Porneste de la nodul 1
    vector<int> circuit;

    while (!s.empty()) {
        int nod_curent = s.top();
        if (G[nod_curent].size() > 0) {
            // Daca nodul curent are vecini, continua explorarea
            int next = G[nod_curent].back();
            G[nod_curent].pop_back(); // Elimina muchia parcursa
            s.push(next);
        } else {
            // Daca nodul nu mai are vecini, adauga-l in ciclu
            circuit.push_back(nod_curent);
            nod_curent = s.top();
            s.pop();
        }
    }

    print_circuit(circuit);
}

int main(int argc, const char * argv[]) {
    int n, m;
    in >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;
        G[x].push_back(y); // Construieste lista de adiacenta
    }
    for (int i = 1; i <= n; i++) {
        grad[i] = (int)G[i].size(); // Calculeaza gradul fiecarui nod
    }
    gasire_ciclu(); // Gaseste ciclul eulerian
    return 0;
}
