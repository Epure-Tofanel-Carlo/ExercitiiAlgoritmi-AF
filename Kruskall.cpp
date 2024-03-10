#include <fstream>
#include <bitset>
#include <algorithm>
using namespace std;

const int N = 2e5 + 1;
const int M = 4e5 + 1;
ifstream in("kruskal.in");
ofstream out("kruskal.out");

struct muchie
{
    int x,y,c;
};

int t[N],nr[N],m,n;
muchie v[M];
bitset <M> folosit;

bool cmp(muchie m1, muchie m2)
{
    return (m1.c < m2.c);
}

int radacina(int x)
{
    if(t[x] == 0)
    {
        return x;
    }
    t[x] = radacina(t[x]);
    return t[x];
}

bool verificare(int x,int y)
{
    return (radacina(x) == radacina(y));
}


void reuniune(int x,int y)
{
    int rx = radacina(x);
    int ry = radacina(y);
    if(nr[rx] < nr[ry])
    {
        t[rx] = ry;
        nr[ry] += nr[rx];
    }
    else
    {
        t[ry] = rx;
        nr[rx] += nr[ry];
    }
}

int kruskal()
{
    sort(v,v + m,cmp);
    int cost = 0,nrm = 0,i = 0;
    while(nrm < n-1)
    {
        if(!verificare(v[i].x,v[i].y))
        {
            folosit[i] = 1;
            nrm++;
            cost += v[i].c;
            reuniune(v[i].x,v[i].y);
        }
        i++;
    }
    return cost;
}


int main()
{
    in >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int x,y,c;
        in >> v[i].x >> v[i].y >> v[i].c;
    }
    in.close();
    out << kruskal() << "\n";
    for(int i = 0; i < m; i++)
    {
        if(folosit[i])
        {
            out << v[i].x << " " << v[i].y << "\n";
        }
    }
    out.close();
    return 0;
}