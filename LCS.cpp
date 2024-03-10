#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int NMAX = 1000;
int dp[NMAX][NMAX];

// Functia pentru gasirea lungimii celei mai lungi subsecvente comune (LCS) intre doua siruri
void find_subsq(string &sir1, string &sir2, int n, int m) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(sir1[i-1] == sir2[j-1]) {
                // Daca caracterele curente se potrivesc, adauga 1 la lungimea subsecventei
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                // Daca nu se potrivesc, alege maximul dintre cele doua optiuni posibile
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
}

// Functia pentru afisarea celei mai lungi subsecvente comune
void show_LCS(string sir1, string sir2, int n, int m) {
    int i = n, j = m;
    string lcs;
    while (i > 0 && j > 0) {
        if (sir1[i - 1] == sir2[j - 1]) {
            // Daca caracterele se potrivesc, adauga-le la subsecventa si deplaseaza inapoi in ambele siruri
            lcs = sir1[i - 1] + lcs;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            // Mergi inapoi in sirul unde valoarea din dp este mai mare
            i--;
        } else {
            j--;
        }
    }
    cout << lcs << endl;
}

int main(int argc, const char * argv[]) {
    string sir1, sir2;
    cin >> sir1 >> sir2;
    int n = (int)sir1.length();
    int m = (int)sir2.length();
    find_subsq(sir1, sir2, n, m); // Calculeaza lungimea LCS
    show_LCS(sir1, sir2, n, m);   // Afiseaza LCS
    return 0;
}
