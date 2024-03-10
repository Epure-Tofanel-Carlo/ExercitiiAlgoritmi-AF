#include <iostream>
#include <fstream>
using namespace std;


const int MAXN = 1000;
char harta[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n, m;

// Direcțiile în care se poate merge
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void DFS(int x, int y);
int RoomCounter();
int main() {
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j)
        {
            cin >> harta[i][j];
        }
    }
    cout << RoomCounter();
    return 0;
}

void DFS(int x, int y)
{
    vis[x][y] = true; // vizitam nodul curent
    for(int dir = 0; dir < 4; dir++) { // mergem in toate 4 directiile
        int new_x = x + dx[dir], new_y = y + dy[dir];
        if(new_x >= 0 && new_x < n && new_y >= 0 && new_y < m && harta[new_x][new_y] == '.' && !vis[new_x][new_y]) // verificam daca e valida directia, si daca e pdoea
        {
            DFS(new_x, new_y);
        }
    }
}

int RoomCounter() {
    int roomCount = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++) // sa fim siguri ca e totul false
        {
            vis[i][j] = false;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(harta[i][j] == '.' && !vis[i][j]) // cand gasim o camera nevizitata, o vizitam si crestem numarul de camere
            {
                DFS(i, j);
                roomCount++;
            }
        }
    }
    return roomCount;
}