#include "tsp.h"

int main(){
    for(int i=5; i <=20; i++){
        TSP tsp("../data/matrix_"+std::to_string(i)+".txt");
        tsp.sequential();
    }
}