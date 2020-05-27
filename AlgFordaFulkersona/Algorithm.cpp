#include <iostream>
#include "Algorithm.h"
#include "Graph.h"
#include "Edge.h"
#include <list>
#include <string.h>
#include <queue>

using namespace std;

Algorithm::Algorithm(Graph graph){
    this->graph = graph;
    this->finalFMax = NULL;
    this->finalFMaxNewTable = NULL;
    this->finalFMaxNewList = NULL;
}

void Algorithm::calculateFMax(){

    list<int> Q;                    // Kolejka
    int ** C;                       // Macierz przepustowości
    int ** F;                       // Macierz przepływów netto
    int * P;                        // Tablica poprzedników
    int * CFP;                      // Tablica przepustowości rezydualnych
    int n,s,t,fmax,cp,x,y,i,j;      // Zmienne proste algorytmu
    bool esc;                       // Do wychodzenia z zagnieżdżonych pętli

    n = graph.getNumOfVertices();

    C = new int * [n];
    F = new int * [n];

    for(i = 0; i < n; i++) {
        C[i] = new int [n];
        F[i] = new int [n];
    }

    P = new int [n];
    CFP = new int [n];

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) C[i][j] = F[i][j] = 0;

    for (const Edge & edge : graph.getListOfEdges())
        C[edge.getV1()][edge.getV2()] = edge.getP();

    s = graph.getStartVertice();
    t = graph.getStopVertice();

    fmax = 0;

    while(true) {
        for(i = 0; i < n; i++) P[i] = -1;

        P[s] = -2;
        CFP[s] = BIG_NUMBER;

        while(!Q.empty()) Q.pop_front();

        Q.push_back(s);
        esc = false;

        while(!Q.empty()) {
            x = Q.front();
            Q.pop_front();

            for(y = 0; y < n; y++) {
                cp = C[x][y] - F[x][y];
                if(cp && (P[y] == -1))                 {
                    P[y] = x;
                    CFP[y] = CFP[x] > cp ? cp : CFP[x];
                    if(y == t) {
                        fmax += CFP[t];
                        i = y;
                        while(i != s) {
                            x = P[i];
                            F[x][i] += CFP[t];
                            F[i][x] -= CFP[t];
                            i = x;
                        }
                        esc = true;
                        break;
                    }
                    Q.push_back(y);
                }
            }
            if(esc) break;
        }
        if(!esc) break;
    }

    finalFMax = fmax;
}

bool bfsTable(int n, int* rGraph, int s, int t, int parent[]) {
    bool visited[n];

    for(int i=0; i<n; i++)
        visited[i] = false;

    queue <int> queue;
    queue.push(s);
    visited[s] = true;
    parent[s] = -1;

    // pętla do BFS
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();

        // dla u wybranego przez BFS sprawdzam każde v czy jest tam odpowiednie połączenie
        // i czy już tam nie byłem
        for (int v=0; v<n; v++){
            if (visited[v]==false && *(rGraph+u*n+v) > 0){
                queue.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    if (visited[t] == true) return true;
    else return false;
}

void Algorithm::calucateFMaxNewTableAlgo() {    // zlozoność liniowa w algo -- i -- (n^2) w BFS
    int s = graph.getStartVertice();
    int t = graph.getStopVertice();
    int numOfVertices = graph.getNumOfVertices();
    int orGraph[numOfVertices][numOfVertices];
    int rGraph[numOfVertices][numOfVertices];
    int parent[numOfVertices];
    int max_flow = 0;

    for(int i=0; i<numOfVertices; i++){
        for(int j=0; j<numOfVertices; j++){
            orGraph[i][j] = 0;
            rGraph[i][j] = 0;
        }
    }

    for (const Edge & edge : graph.getListOfEdges()) {
        orGraph[edge.getV1()][edge.getV2()] = edge.getP();
        rGraph[edge.getV1()][edge.getV2()] = edge.getP();
    }

    while ( bfsTable(numOfVertices, (int*)rGraph, s, t, parent) ) {
        int currentFlow = BIG_NUMBER;

        // wyznaczanie minimalnego przepływu na ścieżce
        for (int v=t; v!=s; v=parent[v]){
            int u = parent[v];
            currentFlow = min(currentFlow, rGraph[u][v]);
        }

        // aktualizowanie grafu rezydualnego
        for (int v=t; v != s; v=parent[v]){
            int u = parent[v];
            rGraph[u][v] -= currentFlow;
            rGraph[v][u] += currentFlow;
        }

        // dodawanie aktualnego przepływu do sumy przepływów
        max_flow += currentFlow;
    }
    finalFMaxNewTable = max_flow;
}

bool bfsList(int nE, int* rGraph, int nV, int s, int t, int parent[]) {

    bool visited[nV];

    for(int i=0; i<nV; i++)
        visited[i] = false;

    queue <int> queue;
    queue.push(s);
    visited[s] = true;
    parent[s] = -1;

    // pętla do BFS
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();

        // dla u wybranego przez BFS sprawdzam każde v czy jest tam odpowiednie połączenie
        // i czy już tam nie byłem poprzez iterowanie po liście
        for (int v=0; v<nV; v++){
            if(visited[v] == false){
                bool ifExistAndBigerThan0 = false;
                for(int i=0; i<nE; i++){
                    int a = *(rGraph+i*3+0);
                    int b = *(rGraph+i*3+1);
                    int c = *(rGraph+i*3+2);

                    if(a==u && b==v && c>0){
                        ifExistAndBigerThan0 = true;
                        break;
                    }
                }
                if (ifExistAndBigerThan0) {
                    queue.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
    }
    // sprawdzanie czy udało się wyznaczyć ścieżkę
    if (visited[t] == true) return true;
    else return false;
}

void Algorithm::calucateFMaxNewListAlgo() {     // zlozoność kwadratowa w algo -- i --- (n^3) w BFS
    int s = graph.getStartVertice();
    int t = graph.getStopVertice();
    int numOfVertices = graph.getNumOfVertices();
    int numOfEdges = graph.getNumOfEdges();

    int orGraph[numOfEdges][3];
    int rGraph[numOfEdges][3];

    int parent[numOfVertices];
    int max_flow = 0;

    //niekoniecznie potrzebne
    for(int i=0; i<numOfVertices; i++)
        parent[i] = -2;

    int iterator = 0;
    for (const Edge & edge : graph.getListOfEdges()) {
        orGraph[iterator][0] = edge.getV1();
        orGraph[iterator][1] = edge.getV2();
        orGraph[iterator][2] = edge.getP();
        rGraph[iterator][0] = edge.getV1();
        rGraph[iterator][1] = edge.getV2();
        rGraph[iterator][2] = edge.getP();
        iterator++;
    }

    while ( bfsList(numOfEdges, (int*)rGraph, numOfVertices, s, t, parent) ) {
        int currentFlow = BIG_NUMBER;

        // wyznaczanie minimalnego przepływu na ścieżce
        for (int v=t; v!=s; v=parent[v]){
            int u = parent[v];
            int value = 0;
            for(int i=0; i<numOfEdges; i++){
                if(rGraph[i][0]==u && rGraph[i][1]==v){
                    value = rGraph[i][2];
                    break;
                }
            }
            currentFlow = min(currentFlow, value);
        }

        // aktualizowanie grafu rezydualnego
        for (int v=t; v != s; v=parent[v]){
            int u = parent[v];
            for(int i=0; i<numOfEdges; i++){
                if(rGraph[i][0]==u && rGraph[i][1]==v){
                    rGraph[i][2] -= currentFlow;
                    break;
                }
            }
            for(int i=0; i<numOfEdges; i++){
                if(rGraph[i][0]==v && rGraph[i][1]==u){
                    rGraph[i][2] += currentFlow;
                    break;
                }
            }
        }

        // dodawanie aktualnego przepływu do sumy przepływów
        max_flow += currentFlow;
    }
    finalFMaxNewList = max_flow;
}

void Algorithm::testing(){
    cout << "Testowanie wypisywania grafu!" << endl;
    cout << "6 " << graph.getNumOfVertices() << endl;
    cout << "9 " << graph.getNumOfEdges() << endl;
    cout << "0 " << graph.getStartVertice() << endl;
    cout << "5 " << graph.getStopVertice() << endl;

    cout << "0 1 10 1 2 4 2 5 10 1 3 2 1 4 8 4 2 6 0 3 10 3 4 9 4 5 10" << endl;

    //sprawdziłem w debugerze bo wypisywanie coś nie dizałąło ale nie amm czasu żeby sprawdzać dlaczego
    for(list<Edge>::iterator i=graph.getListOfEdges().begin(); i!=graph.getListOfEdges().end(); ++i) {
//        cout << i->v1 << " " << i->v2 << " " << i->p << " ";
    }
}

int Algorithm::getFMax() const {
    return finalFMax;
}
int Algorithm::getFMaxNewTable() const {
    return finalFMaxNewTable;
}
int Algorithm::getFMaxNewList() const {
    return finalFMaxNewList;
}

void Algorithm::testIterowania() {

//    for(list<Edge>::const_iterator i=graph.getListOfEdges().begin(); i != graph.getListOfEdges().end(); ++i){
////        liczba += *i;
//        cout << "#";
//    }

    for (const Edge & edge : graph.getListOfEdges()) {
        cout << edge.getV1() << " " << edge.getV2() << " " << edge.getP() << endl;
    }

}
