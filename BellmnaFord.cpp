#include <vector>
#include <queue>
#include <bitset>
using namespace std;

// Clasa pentru citirea din fisier
class InputParser {
private:
    FILE *fileIn;
    char *buffer;
    int bufferIndex;

    // Functie pentru citirea unui caracter
    char readCharacter() {
        ++bufferIndex;
        if (bufferIndex == 4096) {
            bufferIndex = 0;
            fread(buffer, 1, 4096, fileIn);
        }
        return buffer[bufferIndex];
    }

public:
    // Constructor pentru deschiderea fisierului de intrare
    InputParser(const char* fileName) {
        fileIn = fopen(fileName, "r");
        buffer = new char[4096]();
        bufferIndex = 4095;
    }

    // Operator pentru citirea unui numar intreg
    InputParser& operator >> (int &number) {
        char character;
        while (!isdigit(character = readCharacter()) && character != '-');
        int sign = 1;
        if (character == '-') {
            number = 0;
            sign = -1;
        } else {
            number = character - '0';
        }
        while (isdigit(character = readCharacter())) {
            number = 10 * number + character - '0';
        }
        number *= sign;
        return *this;
    }

    // Operator pentru citirea unui numar intreg lung
    InputParser& operator >> (long long &number) {
        char character;
        number = 0;
        while (!isdigit(character = readCharacter()) && character != '-');
        long long sign = 1;
        if (character == '-') {
            number = 0;
            sign = -1;
        } else {
            number = character - '0';
        }
        while (isdigit(character = readCharacter())) {
            number = 10 * number + character - '0';
        }
        number *= sign;
        return *this;
    }
};

// Clasa pentru scrierea in fisier
class OutputParser {
private:
    FILE *fileOut;
    char *buffer;
    int bufferIndex;

    // Functie pentru scrierea unui caracter
    void writeCharacter(char character) {
        if (bufferIndex == 50000) {
            fwrite(buffer, 1, 50000, fileOut);
            bufferIndex = 0;
            buffer[bufferIndex++] = character;
        } else {
            buffer[bufferIndex++] = character;
        }
    }


public:
    // Constructor pentru deschiderea fisierului de iesire
    OutputParser(const char* fileName) {
        fileOut = fopen(fileName, "w");
        buffer = new char[50000]();
        bufferIndex = 0;
    }
    // Destructor pentru scrierea bufferului in fisier si inchiderea fisierului
    ~OutputParser() {
        fwrite(buffer, 1, bufferIndex, fileOut);
        fclose(fileOut);
    }

    // Operator pentru scrierea unui numar intreg in fisier
    OutputParser& operator << (int value) {
        if (value <= 9) {
            writeCharacter(value + '0');
        } else {
            (*this) << (value / 10);
            writeCharacter(value % 10 + '0');
        }
        return *this;
    }

    // Operator pentru scrierea unui numar intreg lung in fisier
    OutputParser& operator << (long long value) {
        if (value <= 9) {
            writeCharacter(value + '0');
        } else {
            (*this) << (value / 10);
            writeCharacter(value % 10 + '0');
        }
        return *this;
    }

    // Operator pentru scrierea unui caracter in fisier
    OutputParser& operator << (char character) {
        writeCharacter(character);
        return *this;
    }
    // Operator pentru scrierea unui sir de caractere in fisier
    OutputParser& operator << (const char *str) {
        while (*str) {
            writeCharacter(*str);
            ++str;
        }
        return *this;
    }
};

// Deschiderea fisierelor de intrare si de iesire
InputParser input("grafpond.in");
OutputParser output("grafpond.out");

const int MAX_NODES = 1e4 + 1;
const int INF = 1e9;

int numberOfNodes, shortestDistances[MAX_NODES], numberOfPaths[MAX_NODES], parents[MAX_NODES];
bool hasNegativeCycle;
bitset<MAX_NODES> used;
vector<pair<int,int>> graph[MAX_NODES];
queue<int> queuee;

// Functie pentru afisarea ciclurilor negative
void printNegativeCycle(int &start, int &end)
{
    vector<int> cycle;
    while(start != end)
    {
        cycle.push_back(start);
        start = parents[start];
    }
    cycle.push_back(start);
    for(int i = (int)cycle.size() - 1; i >= 0; i--)
    {
        output << cycle[i] << " ";
    }
}

// Functie pentru afisarea drumurilor minime
void printShortestPath(int sourceNode)
{
    vector<int> path;
    while(parents[sourceNode] != 0)
    {
        path.push_back(sourceNode);
        sourceNode = parents[sourceNode];
    }
    path.push_back(sourceNode);
    output << "Path: ";
    for(int i = (int)path.size() - 1; i >= 0; i--)
    {
        output << path[i] << " ";
    }
}

// Functia principala pentru algoritmul Bellman-Ford
void bellmanFord(int startNode)
{
    for(int i = 2; i <= numberOfNodes; i++)
    {
        shortestDistances[i] = INF;
    }
    shortestDistances[startNode] = 0;
    queuee.push(startNode);
    numberOfPaths[startNode]++;
    used[startNode] = true;
    while(!queuee.empty())
    {
        int currentNode = queuee.front();
        queuee.pop();
        used[currentNode] = false;
        for(auto edge: graph[currentNode])
        {
            int adjacentNode = edge.first;
            int cost = edge.second;
            if(shortestDistances[adjacentNode] > shortestDistances[currentNode] + cost)
            {
                shortestDistances[adjacentNode] = shortestDistances[currentNode] + cost;
                if(!used[adjacentNode])
                {
                    queuee.push(adjacentNode);
                    numberOfPaths[adjacentNode]++;
                    used[adjacentNode] = true;
                    parents[adjacentNode] = currentNode;
                    if(numberOfPaths[adjacentNode] == numberOfNodes)
                    {
                        hasNegativeCycle = true;
                        output << "Negative Cycle: \n";
                        printNegativeCycle(currentNode, adjacentNode);
                        return;
                    }
                }
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    int numberOfEdges;
    input >> numberOfNodes >> numberOfEdges;
    for(int i = 0; i < numberOfEdges; i++)
    {
        int nodeA, nodeB, cost;
        input >> nodeA >> nodeB >> cost;
        graph[nodeA].push_back({nodeB, cost});
    }
    int startNode;
    input >> startNode;
    bellmanFord(startNode);
    if(!hasNegativeCycle)
    {
        for(int i = 2; i <= numberOfNodes; i++)
        {
            printShortestPath(i);
            output << "Cost: " << shortestDistances[i] << "\n";
        }
    }
    return 0;
}
