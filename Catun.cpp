#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <queue>
using namespace std;

ifstream inputFile("catun.in");
ofstream outputFile("catun.out");

const int MAX_NODES = 36001;
const int MAX_EDGES = 72001;
const int INFINITY = 1e9;

int nodeCount, edgeCount, castleCount, fortress[MAX_NODES], dist[MAX_NODES];

vector<pair<int, int>> graph[MAX_EDGES];
bitset<MAX_NODES> isFortress, isVisited;
priority_queue<pair<int, int>> priorityQ;

// implementarea algoritmului dijkstra pentru gasirea celei mai scurte cai
void executeDijkstra()
{
    while (!priorityQ.empty())
    {
        int currentNode = priorityQ.top().second;
        priorityQ.pop();
        // verificam daca nodul curent a fost deja vizitat
        if (isVisited[currentNode])
        {
            continue;
        }
        isVisited[currentNode] = false;
        // parcurgem toti vecinii nodului curent
        for (auto adjNode : graph[currentNode])
        {
            int neighbor = adjNode.first;
            int weight = adjNode.second;
            // actualizam distanta si forta daca gasim o cale mai scurta
            if (dist[currentNode] + weight < dist[neighbor])
            {
                dist[neighbor] = dist[currentNode] + weight;
                fortress[neighbor] = fortress[currentNode];
                priorityQ.push({-dist[neighbor], neighbor});
            }
                // actualizam forta in caz de egalitate si distanta mai mica
            else if (dist[currentNode] + weight == dist[neighbor] && fortress[currentNode] < fortress[neighbor])
            {
                fortress[neighbor] = fortress[currentNode];
                priorityQ.push({-dist[neighbor], neighbor});
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    inputFile >> nodeCount >> edgeCount >> castleCount;
    for (int i = 0; i <= nodeCount; i++)
    {
        dist[i] = INFINITY;
    }
    // initializam fortaretele si setam distantele lor la 0
    for (int i = 0; i < castleCount; i++)
    {
        int node;
        inputFile >> node;
        dist[node] = 0;
        isFortress[node] = true;
        fortress[node] = node;
        priorityQ.push({-dist[node], node});
    }
    // citirea muchiilor si construirea grafului
    for (int i = 0; i < edgeCount; i++)
    {
        int nodeA, nodeB, cost;
        inputFile >> nodeA >> nodeB >> cost;
        graph[nodeA].push_back({nodeB, cost});
        graph[nodeB].push_back({nodeA, cost});
    }
    inputFile.close();

    // aplicarea algoritmului dijkstra
    executeDijkstra();

    // afisarea rezultatelor - distanta pana la cea mai apropiata forta
    for (int i = 1; i <= nodeCount; i++)
    {
        if (isFortress[i])
            outputFile << 0 << " ";
        else
            outputFile << fortress[i] << " ";
    }
    outputFile.close();
    return 0;
}
