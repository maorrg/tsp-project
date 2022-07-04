#include "tsp.h"

int main(){
    /*
    // PARA LAS MATRICES DE PRUEBA //
    for(int i=5; i <=20; i++){
        TSP tsp("../data/matrix_"+std::to_string(i)+".txt");
        tsp.sequential();
    }*/

    // PARA LOS DISTRITOS DE LIMA //
    TSP tsp("../data/lima_matrix/total_cost_matrix.txt");
    tsp.sequential();
}