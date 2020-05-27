#include <iostream>
#include "Graph.h"
#include "FileLoader.h"
#include "Algorithm.h"
#include <string>

using namespace std;

int getFMaxOfGraph(string path) {
    FileLoader fileLoader(path);
    fileLoader.extractValues();

    Graph graph;
    graph.setNumOfVertices(fileLoader.getNumOfVertices());
    graph.setNumOfEdges(fileLoader.getNumOfEdges());
    graph.setStartVertice(fileLoader.getStartVertice());
    graph.setStopVertice(fileLoader.getStopVertice());
    graph.setListOfEdges(fileLoader.getListOfEdges());

    Algorithm algorithm(graph);
    //testowanie przekazania grafu do algorytmu
//    algorithm.testing();
//    algorithm.testIterowania();

    algorithm.calculateFMax();
    int fMax = algorithm.getFMax();

    return fMax;
}

int getFMaxOfGraphWithNewAlgo(string path, int mode){
    FileLoader fileLoader(path);
    fileLoader.extractValues();

    Graph graph;
    graph.setNumOfVertices(fileLoader.getNumOfVertices());
    graph.setNumOfEdges(fileLoader.getNumOfEdges());
    graph.setStartVertice(fileLoader.getStartVertice());
    graph.setStopVertice(fileLoader.getStopVertice());
    graph.setListOfEdges(fileLoader.getListOfEdges());

    Algorithm algorithm(graph);
    //testowanie przekazania grafu do algorytmu
//    algorithm.testing();
//    algorithm.testIterowania();

    if(mode == 1){
        algorithm.calucateFMaxNewTableAlgo();
        return algorithm.getFMaxNewTable();
    } else if(mode == 2){
        algorithm.calucateFMaxNewListAlgo();
        return algorithm.getFMaxNewList();
    } else return 0;
}

int main() {

    string path1 =  "../grafy/graf1_fromVideo_wynik_19.txt";
    string path2 =  "../grafy/graf_from_internet_wynik_18.txt";
//    string path3 =  "../grafy/graf_from_internet2_wynik_400.txt";

//    string path2 =  "../grafy/graf_losowy_1.txt";
//    string path3 =  "../grafy/graf_losowy_2.txt";

    cout << "Old algorithm:" << endl;

    cout << "Graph file: \"" << path1.substr(9) << endl << "FMax = " << getFMaxOfGraph(path1) << endl << endl;  //OK
    cout << "Graph file: \"" << path2.substr(9) << endl << "FMax = " << getFMaxOfGraph(path2) << endl << endl;  //OK
//    cout << "Graph file: \"" << path3.substr(9) << endl << "FMax = " << getFMaxOfGraph(path3) << endl << endl; //TO DO dlaczego 0? a nie 400

    //    cout << "Graph file: \"" << path2.substr(9) << endl << "FMax = " << getFMaxOfGraph(path2) << endl << endl;
    //    cout << "Graph file: \"" << path3.substr(9) << endl << "FMax = " << getFMaxOfGraph(path3) << endl << endl;


    cout << "New algorithms:" << endl;
    cout << "Table:" << endl;

    cout << "Graph file: \"" << path1.substr(9) << endl << "FMax from table algorithm = " << getFMaxOfGraphWithNewAlgo(path1, 1) << endl << endl;  //OK
    cout << "Graph file: \"" << path2.substr(9) << endl << "FMax from table algorithm = " << getFMaxOfGraphWithNewAlgo(path2, 1) << endl << endl;  //OK

    cout << "List:" << endl;

    cout << "Graph file: \"" << path1.substr(9) << endl << "FMax from list algorithm = " << getFMaxOfGraphWithNewAlgo(path1, 2) << endl << endl;  //OK
    cout << "Graph file: \"" << path2.substr(9) << endl << "FMax from list algorithm = " << getFMaxOfGraphWithNewAlgo(path2, 2) << endl << endl;  //OK

    return 0;
}