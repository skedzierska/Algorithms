//Sonia Kedzierska, s173656
#include <bits/stdc++.h>

using namespace std;

#define vertices 5

int min_key(int key[], bool tree_set[]) {
    // znajdowanie minimalnej wartosci
    // ze zbioru wierzcholkow spoza minimalnego
    //drzewa rozpinajacego
    int min = INT_MAX, min_index;

    for (int i=0; i<vertices; i++) {
        if(tree_set[i] == false && key[i] < min) {
            min = key[i], min_index = i;
        }
    }
    return min_index;
}

void print_tree(int parent[], int graph[vertices][vertices]) {
    int minimum = 0;
    cout << "-minimalne drzewo rozpinajace-" << endl;
	cout << endl;
	cout << endl;
	cout << "wierzcholek 1 ------>  wierzcholek 2   waga wierzcholka:" << endl;
    for (int i=1; i<vertices; i++) {
        cout << "     " << parent[i]+1 << "          ->        " << i+1 << "             " << graph[i][parent[i]] << endl;
        minimum += graph[i][parent[i]];
    }
    cout << endl;
    cout << "suma wag: " << minimum << endl;
}

// konstruowanie mdr przy uzyciu reprezentacji macierzy sasiedztwa V x V
void prim_algorithm(int graph[vertices][vertices]) {

    int parent[vertices];
    int key[vertices];
    bool tree_set[vertices];

    for (int i=0; i<vertices; i++) {
        // inicjalizujemy wszystkie klucze jako infinite zeby
        //moc wybrac  krawêdŸ o najni¿szym koszcie spoœród wszystkich krawêdzi
        //prowadz¹cych od wybranych ju¿ wierzcho³ków do
        //wierzcho³ków jeszcze niewybranych
        key[i] = INT_MAX, tree_set[i] = false;
    }
    //wybieramy pierwszy wierzcholek
    key[0] = 0;
    parent[0] = -1;
    //ilosc wierzcholkow bedzie n-1 gdzie n
    // jest liczba krawedzi
    for (int i=0; i<vertices-1; i++) {
        int u = min_key(key, tree_set);
        tree_set[u] = true;

        for (int j=0; j<vertices; j++) {
            if (graph[u][j] && tree_set[j] == false && graph[u][j] < key[j]) {
                //ajmniejszy klucz jest aktualizoawy gdy graph[u][j] jest mniejszy od biezacego klucza
                parent[j] = u, key[j] = graph[u][j];
            }
        }
    }
    print_tree(parent, graph);
}

int main()
{
    //macierz sasiedztwa V x V
    int graph[vertices][vertices] = {{0, 1, 2, 2, 6},
                                     {1, 0, 0, 4, 5},
                                     {2, 0, 0, 3, 0},
                                     {2, 4, 3, 0, 3},
                                     {6, 5, 0, 3, 0}};
    prim_algorithm(graph);
    return 0;
}
