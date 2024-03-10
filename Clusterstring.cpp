
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
int parent[MAXN + 1] = {0}, height[MAXN + 1] = {0};

struct Edge {
    int u, v, weight;
};


bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}


int Find(int u) {
    if(parent[u] == 0)
        return u;
    return Find(parent[u]);
}


void Union(int u, int v) {
    int ru = Find(u);
    int rv = Find(v);
    if (height[ru] > height[rv]) {
        parent[rv] = ru;
    } else {
        parent[ru] = rv;
        if (height[ru] == height[rv]) {
            height[rv]++;
        }
    }
}


int levenshteinDistance(string &s1, string &s2) {
    int dp[s1.size() + 1][s2.size() + 1];
    for(int i = 0; i <= s1.size(); i++)
        dp[i][0] = i;
    for(int j = 0; j <= s2.size(); j++)
        dp[0][j] = j;
    for(int i = 1; i <= s1.size(); i++)
        for(int j = 1; j <= s2.size(); j++)
            if(s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    return dp[s1.size()][s2.size()];
}


void clusteringLevenshtein() {
    vector<string> words; // vector pentru stocarea cuvintelor
    string word;
    // citim cuvintele pana la intalnirea cuvantului "END"
    while (cin >> word && word != "END") {
        words.push_back(word);
    }

    int k; // nr clustere
    cin >> k;

    vector<Edge> edges;
    // calculam distantele pentru fiecare pereche de cuvinte
    for(int i = 0; i < words.size(); i++)
        for(int j = i + 1; j < words.size(); j++) {
            int cost = levenshteinDistance(words[i], words[j]);
            edges.push_back({i, j, cost});
        }

    sort(edges.begin(), edges.end(), compareEdges); // sortam edge urile crescator dupa cost

    int clusters = words.size(); // nr de clustere
    int separationDegree = 0; // gradul de separare

    // aplicam algoritmul Kruskal
    for (auto &edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int w = edge.weight;

        int ru = Find(u);
        int rv = Find(v);

        // unim clusterele daca nu sunt deja in acelasi cluster
        if (ru != rv) {
            if (clusters == k) {
                separationDegree = w; // setam gradul de separare
                break;
            } else {
                Union(ru, rv);
                clusters--;
            }
        }
    }

    // afisam cuvintele din fiecare cluster
    vector<string> CLUSTER(words.size(), "");
    for(int i = 0; i < words.size(); i++){
        int rep = Find(i);
        CLUSTER[rep].append(" " + words[i]);
    }

    for(const auto & cuv : CLUSTER)
        if(!cuv.empty())
            cout << cuv.substr(1, cuv.size()) << endl;

    cout << separationDegree << endl;
}

int main() {
    clusteringLevenshtein();
    return 0;
}
