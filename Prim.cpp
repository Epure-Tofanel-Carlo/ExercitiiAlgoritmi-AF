#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
using namespace std;

const int N = 101;
const int INF = 1e6;

vector <pair<int,int>> a[N];
priority_queue <pair<int,int>> pq;
bitset <N> selectat;

int n,m,d[N],pred[N],cost;

ifstream in("prim.in");
ofstream out("prim.out");

void prim()
{
    for(int i = 2; i <= n; i++)
    {
        d[i] = INF;
    }
    pq.push({0,1});
    while(!pq.empty())
    {
        int x = pq.top().second;
        pq.pop();
        if(selectat[x])
        {
            continue;
        }
        cost += d[x];
        selectat[x] = true;
        for(auto p : a[x])
        {
            int y = p.first;
            int c = p.second;
            if(!selectat[y] && c < d[y])
            {
                d[y] = c;
                pred[y] = x;
                pq.push({-c,y});
            }
        }
    }
}


int main()
{
    in >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        int x,y,c;
        in >> x >> y >> c;
        a[x].push_back({y,c});
        a[y].push_back({x,c});
    }
    in.close();
    prim();
    out << cost << "\n";
    for(int i = 1; i <= n; i++)
    {
        out << pred[i] << " ";
    }
    out.close();
    return 0;
}