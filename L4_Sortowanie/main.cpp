#include <omp.h>
#include <iostream>

using namespace std;

const int N = 60000000;
const int liczbaWatkow = 4;
const int odciecie = 100;

void quick_sort_sek(int *tab, int lewy, int prawy) {
    int i = lewy, j = prawy;
    int tmp;
    int pivot = tab[(lewy + prawy) / 2];

    while (i <= j) {
        while (tab[i] < pivot)
            i++;
        while (tab[j] > pivot)
            j--;
        if (i <= j) {
            tmp = tab[i];
            tab[i] = tab[j];
            tab[j] = tmp;
            i++;
            j--;
        }
    }

    if (lewy < j) {
        quick_sort_sek(tab, lewy, j);
    }
    if (i< prawy) {
        quick_sort_sek(tab, i, prawy);
    }
}

void quick_sort_row_inner(int* tab, int lewy, int prawy) {
    int i = lewy, j = prawy;
    int tmp;
    int pivot = tab[(lewy + prawy) / 2];

    while (i <= j) {
        while (tab[i] < pivot)
            i++;
        while (tab[j] > pivot)
            j--;
        if (i <= j) {
            tmp = tab[i];
            tab[i] = tab[j];
            tab[j] = tmp;
            i++;
            j--;
        }
    }

    if ( (prawy-lewy) < odciecie ){
        if (lewy < j) {
            quick_sort_row_inner(tab, lewy, j);
        }
        if (i < prawy) {
            quick_sort_row_inner(tab, i, prawy);
        }
    } else {

#pragma omp task
        {
            quick_sort_row_inner(tab, lewy, j);
        }
#pragma omp task
        {
            quick_sort_row_inner(tab, i, prawy);
        }
    }

}
// single - tylko jeden wątek

void quick_sort_row_main(int *tab) {
#pragma omp parallel num_threads(liczbaWatkow)
    {
#pragma omp single nowait
        {
            quick_sort_row_inner(tab, 0, N-1);
        }
    }
}

int main() {
    cout.precision(22);

    int *tabSek, *tabRow;
    tabSek = new int [N];
    tabRow = new int [N];

    for(int i=0;i<N;i++) {
        int val = rand() % 10;
        tabSek[i] = val;
        tabRow[i] = val;
    }

    double start_t1 = omp_get_wtime();
    quick_sort_sek(tabSek, 0, N - 1);
    double t1 = omp_get_wtime() - start_t1;

    double start_t2 = omp_get_wtime();
    quick_sort_row_main(tabRow);
    double t2 = omp_get_wtime() - start_t2;

    cout << "Czas sekwencyjnie:\t" << t1 <<  endl;
    cout << "Czas rownolegle:\t" << t2 <<  endl;
    cout << "Stosunek (sek/row): " << t1/t2 << endl;

    // wypisywanie
//    cout << "Sek\tRow" << endl;
//    for(int i=0;i<N;i++) cout << " " << tabSek[i] << "\t" << " " << tabSek[i] << endl;

    delete tabSek;
    delete tabRow;

    return 0;
}