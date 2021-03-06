#include "main.h"

using namespace std;
struct Muchie
{

    int flow, capacity;
    int x, y;
    Muchie(int flow, int capacity, int x, int y)
    {
        this->flow = flow;
        this->capacity = capacity;
        this->x = x;
        this->y = y;
    }
};
struct Nod
{
    int h, flowExcess;
    Nod(int h, int flowExcess)
    {
        this->h = h;
        this->flowExcess = flowExcess;
    }
};
class Graph
{
    int V;
    vector<Muchie> muchii;
    vector<Nod> noduri;
    bool push(int x);
    void inaltare(int x);
    void preflux(int x);

    void updateRevFlow(int x, int flow);

public:
    Graph(int V);

    void addMuchie(int x, int y, int w);
    int getMaxFlow(int start, int finish);
};
Graph::Graph(int V) : V{V}
{
    for (int i = 0; i < V; i++)
    {
        noduri.push_back(Nod(0, 0));
    }
}
void Graph::addMuchie(int x, int y, int capacity)
{
    muchii.push_back(Muchie(0, capacity, x, y));
}
void Graph::preflux(int x)
{
    noduri[x].h = noduri.size();
    for (int i = 0; i < muchii.size(); i++)
    {
        // daca am dat de muchie incidenta in x (care porneste din x)
        if (muchii[i].x == x)
        {
            // flow = capacitate -> trimitem pe muchie toata capacitatea ei posibila
            muchii[i].flow = muchii[i].capacity;
            // excess flow pentru cine primeste
            noduri[muchii[i].y].flowExcess += muchii[i].flow;
            // adaugam muchie inversa cu capacitate = 0 si flow opusul
            muchii.push_back(Muchie(-muchii[i].flow, 0, muchii[i].y, x));
        }
    }
}
int overflowNod(vector<Nod> &noduri)
{
    for (int i = 1; i < noduri.size() - 1; i++)
    {
        if (noduri[i].flowExcess > 0)
        {
            return i;
        }
    }
    // daca n uexista nod cu overflow
    return -1;
}
void Graph::updateRevFlow(int x, int flow)
{
    int u = muchii[x].y, v = muchii[x].x;

    for (int j = 0; j < muchii.size(); j++)
    {
        if (muchii[j].y == v && muchii[j].x == x)
        {
            // Daca exista muchia initiala, scadem de acolo si incheiem
            muchii[j].flow -= flow;
            return;
        }
    }
    // Daca nu exista, o adaugam
    Muchie e = Muchie(0, flow, u, v);
    muchii.push_back(e);
}
bool Graph::push(int x)
{
    // trecem prin toate muchiile, gasim vecinii lui x la care putem pompa
    for (int i = 1; i < muchii.size(); i++)
    {
        // verificam daca e muchie care poorneste din x
        if (muchii[i].x == x)
        {
            // daca flow = capacitate no push
            if (muchii[i].flow == muchii[i].capacity)
            {
                continue;
            }
            // putem da push doar daca inaltimea adiacentului < inaltimea lui x
            if (noduri[x].h > noduri[muchii[i].y].h)
            {
                // flow pompat = min(ce se mai poate pompa pe muchie vs. exces flow)
                // de ce min? pentru ca excesul e ceea ce intra, si nu putem pompa mai mult decat itnra pe muchie
                int flow = min(muchii[i].capacity - muchii[i].flow, noduri[x].flowExcess);
                // reducem excesul cu atata cat vom pompa
                noduri[x].flowExcess -= flow;
                // locul in care pompam va primi exces
                noduri[muchii[i].y].flowExcess += flow;
                // flow residual in directia inversa
                muchii[i].flow += flow;
                updateRevFlow(i, flow);

                return true;
            }
        }
    }
    return false;
}
void Graph::inaltare(int x)
{
    int minh = INT_MAX;
    for (int i = 0; i < muchii.size(); i++)
    {
        if (muchii[i].x == x)
        {
            // daca flow=capacitate nu inaltam
            if (muchii[i].flow == muchii[i].capacity)
                continue;
            // daca inaltimea vecinului e mai mica facem update
            if (noduri[muchii[i].y].h < minh)
            {
                minh = noduri[muchii[i].y].h;
                // asa ne asiguram ca crestem inaltimea lui x ca sa putem pompa
                noduri[x].h = minh + 1;
            }
        }
    }
}
// marele algorithm
int Graph::getMaxFlow(int start, int finish)
{
    // pompam din start si de acolo plecam
    preflux(start);

    // cat timp exista overflow din noduri
    while (overflowNod(noduri) != -1)
    {
        // un nod care are overflow
        int u = overflowNod(noduri);
        // daca nu putem pompa din acel nod
        if (!push(u))
        {
            // il inaltam
            inaltare(u);
        }
    }
    // ultimul nod este finish si excesul va fi maxFlow final
    return noduri.back().flowExcess;
}
void PREFLUXALG()
{
    ifstream f("in.txt");
    int V, E;
    f >> V >> E;
    Graph graph(V);
    for (int i = 0; i < E; i++)
    {
        int x, y, w;
        f >> x >> y >> w;
        graph.addMuchie(x, y, w);
    }
    int s = 0, t = V - 1;
    ofstream g("out.txt");
    g << graph.getMaxFlow(s, t);
}
int main(int argc, char **argv)
{
    // fordFulkerson();
    PREFLUXALG();
    // Eulerian();
    return 0;
}