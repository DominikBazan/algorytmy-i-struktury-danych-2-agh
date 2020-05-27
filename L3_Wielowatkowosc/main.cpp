#include <omp.h>
#include <iostream>

using namespace std;

const int liczbaPunktowZasianych = 20000000;
double punktyZasiane[liczbaPunktowZasianych][2];
double r = 0.5;
double poleKwadratu = 4*r*r;

double f(double x) {
    return 1/(1+x*x);
}

void calkaNierownolegla() {
    double a = 0, b = 1;
    double dx = 0.000001;
    double m = (b-a)/dx;
    double w = 0;

    for(long i = 0; i<m; i++) {
        w += f(a + i * dx) * dx;
    }

    cout << "Wynik: " << w*4 << endl;
}

void calkaRownoleglaDzielenie() {
    double a = 0, b = 1;
    double dx = 0.000001;
    double m = (b-a)/dx;
    double sum = 0;

    double tab[4] = {0,0,0,0};

    #pragma omp parallel
    {
        int n = omp_get_num_threads();
        int k = omp_get_thread_num();
        double w = 0;
        for(long i=k; i<m; i+=n){
            w += f(a + i * dx) * dx;
        }
        tab[k] = w;
    }

    sum = tab[0]+tab[1]+tab[2]+tab[3];

    cout << "Wynik: " << sum*4 << endl;
}

void calkaRownoleglaZReduction() {
    double a = 0, b = 1;
    double dx = 0.000001;
    long m = (b-a)/dx;
    double w = 0;

    #pragma omp parallel for reduction(+:w)
    for(long i=0; i<m; i++){
        w += f(a + i * dx) * dx;
    }

    cout << "Wynik: " << w*4 << endl;
}

void koloNierownolegle() {
    int liczbaPunktowWKole = 0;
    for(int i = 0; i < liczbaPunktowZasianych; i++){
        double x = punktyZasiane[i][1];
        double y = punktyZasiane[i][2];
        if(r*r >= x*x+y*y) {
            liczbaPunktowWKole++;
        }
    }
    cout << "Wynik: " << /*poleKwadratu*/ 4 * (double)liczbaPunktowWKole / (double)liczbaPunktowZasianych << endl;
}

void koloRownolegle() {
    int liczbaPunktowWKole = 0;
    #pragma omp parallel for reduction(+:liczbaPunktowWKole)
    for(int i = 0; i < liczbaPunktowZasianych; i++){
        double x = punktyZasiane[i][1];
        double y = punktyZasiane[i][2];
        if(r*r >= x*x+y*y) {
            liczbaPunktowWKole++;
        }
    }
    cout << "Wynik: " << /*poleKwadratu*/ 4 * (double)liczbaPunktowWKole / (double)liczbaPunktowZasianych << endl;
}

int main (int argc, char *argv[]) {

    cout.precision(15);

    cout << "Liczba pi: 3,14159265358979" << endl << endl;

    // wersja nierównoległa liczenia całki
    cout << "#### Całka nierównoległa ####" << endl;
    double start_time = omp_get_wtime();
    calkaNierownolegla();
    double time = omp_get_wtime() - start_time;
    cout << "Czas: " << time << endl;
    cout << "#############################" << endl << endl;

    // wersja równoległa liczenia całki gdzie sami dzielimy
    cout << "#### Całka równoległa - dzielenie ####" << endl;
    start_time = omp_get_wtime();
    calkaRownoleglaDzielenie();
    time = omp_get_wtime() - start_time;
    cout << "Czas: " << time << endl;
    cout << "######################################" << endl << endl;

    // wersja równoległa z redection
    cout << "#### Całka równoległa z reduction ####" << endl;
    start_time = omp_get_wtime();
    calkaRownoleglaZReduction();
    time = omp_get_wtime() - start_time;
    cout << "Czas: " << time << endl;
    cout << "######################################" << endl << endl;

    cout << "Pole koła: 0.7853981633" << endl << endl;

    // losowaniepunktów w kole
    /*
        -> koło jest o promieniu r
        -> kwadrat jest o boku 2r
        -> środek układu współżędnych umieszczam
           w środku koła i w punkcie symetrii kwadratu
        -> bok kwadratu jest prostopadły lub równoległy do osi X lub Y
    */
    for(int i = 0; i < liczbaPunktowZasianych; i++) {
        punktyZasiane[i][0] = (double)(rand() % 10000) / 10000 - r;
        punktyZasiane[i][1] = (double)(rand() % 10000) / 10000 - r;
    }

    // wersja nierównoległa dla koła
    cout << "#### Koło - nierównolegle ####" << endl;
    start_time = omp_get_wtime();
    koloNierownolegle();
    time = omp_get_wtime() - start_time;
    cout << "Czas: " << time << endl;
    cout << "##############################" << endl << endl;

    // wersja równoległa dla koła
    cout << "#### Koło - równolegle ####" << endl;
    start_time = omp_get_wtime();
    koloRownolegle();
    time = omp_get_wtime() - start_time;
    cout << "Czas: " << time << endl;
    cout << "###########################";

    return 0;
}