#include <iostream>
#include "Algorithm.h"

using namespace std;

Algorithm::Algorithm(Graph graph){
    this->graph = graph;
}

struct EdgeElement {
    int v2, weight;
    EdgeElement* next;
};

void Algorithm::calculateResult() {

    const int BIG_NUMBER = 2000000000;
    bool noChange;

    int v = graph.getStartVertice();
    int n = graph.getNumOfVertices();

    EdgeElement** neighbors = new EdgeElement * [n];  // macierz sąsiedztwa
    long long* d = new long long [n];              // koszty dojścia
    int* p = new int [n];                    // poprzedniki

    for(int i = 0; i < n; i++) {
        d[i] = BIG_NUMBER;
        p[i] = -1;
        neighbors[i] = NULL;
    }

    for (const Edge & edge : graph.getListOfEdges()) {
        EdgeElement* ee = new EdgeElement;
        ee->v2 = edge.getV2();
        ee->weight = edge.getP();
        ee->next = neighbors[edge.getV1()];
        neighbors[edge.getV1()] = ee;
    }

    //algorytm BF
    d[v] = 0;       // koszt dojścia do wierzchołka początkowego = 0
    for(int i = 1; i < n; i++) {
        noChange = true;
        for(int j = 0; j < n; j++)      //dla każdego
            for(EdgeElement* ee = neighbors[j]; ee; ee = ee->next) {    // dla każdego sąsiada wierzchołka
                if (d[ee->v2] > d[j] + ee->weight) {       //główny warunek
                    noChange = false;       // oznaczenie wystąpienia zmiany
                    d[ee->v2] = d[j] + ee->weight;        //relaksacja
                    p[ee->v2] = j;
                }
            }
        if(noChange) break;         // Jeśli nie było zmian, to kończymy
    }

    // sprawdzam istnienie ujemnego cyklu
    if(!noChange) {     //jeśli nastąpiła jakaś zmiana bo jak nie to nie ma sensu sprawdzać drugi raz
        for (int i = 0; i < n; i++)
            for (EdgeElement* ee = neighbors[i]; ee; ee = ee->next)
                if (d[ee->v2] > d[i] + ee->weight) {
                    cout << "Ujemny cykl!" << endl;
                    return;
                }
    }

    //Wypisywanie wyniku
    int* stack = new int [n];
    int stackIterator = 0;

    for(int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = i; j != -1; j = p[j]) {
            stack[stackIterator] = j;            // w kolejności od ostatniego do pierwszego
            stackIterator++;
        }

        while (stackIterator) {
            stackIterator--;
            cout << stack[stackIterator] << ">";
        }
        cout << " Koszt: " << d[i] << endl;
    }
    delete [] stack;
    delete [] d;
    delete [] p;

    for(int i = 0; i < n; i++) {
        EdgeElement* j = neighbors[i];
        while(j) {
            EdgeElement* tmp = j;
            j = j->next;
            delete tmp;
        }
    }

    delete [] neighbors;
}

/*
void Algorithm::testing(){
    cout << "Testowanie wypisywania grafu!" << endl;
    cout << "6 " << graph.getNumOfVertices() << endl;
    cout << "11 " << graph.getNumOfEdges() << endl;
    cout << "0 " << graph.getStartVertice() << endl;

    for (const Edge & edge : graph.getListOfEdges()) {
        cout << edge.getV1() << " " << edge.getV2() << " " << edge.getP() << endl;
    }
}
*/
