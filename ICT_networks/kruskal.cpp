#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    //skladowe krawedzi; dwa wierzcholki oraz waga
    int vertice1,vertice2,weight;
};
struct Graph {
	//reprezentacja grafu
	int vertices;
	int edges;
	Edge* edge;
};

//tworzy graf z V liczba wierzcholkow oraz E liczba krawedzi
Graph* createGraph(int v, int e) {
	Graph* graph = new Graph;
	graph -> vertices = v;
	graph -> edges = e;
    //dodawanie nowych krawedzi do drzewa
	graph -> edge = new Edge[e];
	return graph;
}

struct Disjoint {
	//inicjowanie struktury zbiorow rozlacznych
	//nie posiadajacych czesci wspolnych do
	//przechowywania wierzcholkow grafu
	int p;
	int rank;
};

//szukamy czy wierzcholki znajduja sie we wczesniej
//zdefioniowanych rozlacznych zbiorach
int find(Disjoint ds[], int i) {
	if (ds[i].p != i) {
		ds[i].p = find(ds, ds[i].p);
	}
	return ds[i].p;
}
//laczy podzbiory zawierajace wierzcholki w nowy podzbior
void union_set(Disjoint ds[], int x, int y) {
	int set_x = find(ds, x);
	int set_y = find(ds, y);

	if (ds[set_x].rank < ds[set_y].rank) {
		ds[set_x].p = set_y;
    } else if (ds[set_x].rank > ds[set_y].rank) {
		ds[set_y].p = set_x;
    }else {
		ds[set_y].p = set_x;
		ds[set_x].rank++;
	}
}

//porownanie ze soba wag dwoch wierzcholkow
int compare(const void* edge1, const void* edge2) {
	Edge* e1 = (Edge*)edge1;
	Edge* e2 = (Edge*)edge2;
	return e1 -> weight > e2 -> weight;
}

void kruskal_algorithm(Graph* graph)
{
	int vertice = graph -> vertices;
	Edge result[vertice];
	int e = 0;
	int i = 0;
    //sortowanie wag rosnaco
	qsort(graph -> edge, graph -> edges, sizeof(graph -> edge[0]), compare);
	Disjoint*ds = new Disjoint[(vertice* sizeof(Disjoint))];

	for (int i=0; i<vertice; ++i){
		ds[i].p = i;
		ds[i].rank = 0;
	}

    //dodawanie krawedzi do drzewa
	while (e<vertice-1 && i<graph->edges)
	{
		Edge next = graph -> edge[i++];
		int x = find(ds, next.vertice1);
		int y = find(ds, next.vertice2);
        //jezeli krawedz nie tworzy cyklu z juz obecnymi
        //krawedziami to dodajemy ja do zbioru
		if (x != y) {
			result[e++] = next;
			union_set(ds, x, y);
		}
	}

	int minimum = 0;

	cout << "-minimalne drzewo rozpinajace-" << endl;
	cout << endl;
	cout << endl;
	cout << "wierzcholek 1 ------>  wierzcholek 2   waga wierzcholka:" << endl;
	for (i=0; i<e; ++i){
		cout << "     " << result[i].vertice1 << "          ->        " << result[i].vertice2 << "                " << result[i].weight << endl;
		minimum += result[i].weight;
	}
	cout << endl;
	cout << "suma wag: " << minimum << endl;
}

int main()
{
	int vertices = 5;
	int edges = 5;
	Graph* graph = createGraph(vertices, edges);
	graph -> edge[0].vertice1 = 0;
	graph -> edge[0].vertice2 = 2;
	graph -> edge[0].weight = 4;

	graph -> edge[1].vertice1 = 0;
	graph -> edge[1].vertice2 = 3;
	graph -> edge[1].weight = 2;

	graph -> edge[2].vertice1 = 1;
	graph -> edge[2].vertice2 = 3;
	graph -> edge[2].weight = 2;

	graph -> edge[3].vertice1 = 2;
	graph -> edge[3].vertice2 = 3;
	graph -> edge[3].weight = 6;

	graph -> edge[4].vertice1 = 2;
	graph -> edge[4].vertice2 = 4;
	graph -> edge[4].weight = 14;

	kruskal_algorithm(graph);

	return 0;
}
