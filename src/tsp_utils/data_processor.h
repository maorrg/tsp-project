#ifndef READFILES_H
#define READFILES_H

#include <iostream>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

struct Trip {
    vector<int> nodes;
    int totalCost;
};

#define N 110

void read(string filename, int *n, int *cost, int costMatrix[][N], int result[N+1]){
    const char * charFileName = filename.c_str();
    freopen(charFileName, "r", stdin);

    cin >> *n;
    cout << "Archivo leido: " << filename << endl;
    cout << "\n\n\n---------- MATRIZ DE  " << *n <<" NODOS ---------- " << endl;
    for (size_t i = 0; i <= *n; i++) {
        cin >> result[i];
    }

    cin >> *cost;

    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *n; j++)
            cin >> costMatrix[i][j];
    
    cout << "\n---------- RESULTADOS ESPERADOS ---------- " << endl;
    cout << "El número de nodos (ciudades) es: " << *n << endl;
    cout << "El mejor Trip (recorrido) esperado: [ ";
    for (size_t i = 0; i <= *n; i++){
        cout << result[i] << " ";
    }
    cout << "]" << endl;
    cout << "El mejor totalCosto (costo mínimo de viaje) esperado: " << *cost << endl;
}

void printSequentialTime(double time) {
    cout << "\n--------------- TIEMPOS --------------- " << endl;
    cout << fixed << setprecision(0);
    cout << "El tiempo tomado es: " << time << " nanosegundos (ns)" << endl;
    cout << fixed << setprecision(6);
    cout << "El tiempo tomado es: " << time * pow(10, -6) << " milisegundos (ms)" << endl;
    cout << fixed << setprecision(9);
    cout << "El tiempo tomado es: " << time * pow(10, -9) << " segundos (s)" << endl;
}

void writeObtainedResultsParallel(string fileName, double time, const char* numberOfThreads,int n) {
    std::ofstream outfile;
    outfile.open("../results/"+fileName, std::ios_base::app);
    outfile << endl << to_string(time * pow(10, -6)) << "," << numberOfThreads << "," << to_string(n);
}

void writeObtainedResultsSequential(string fileName, double time, int n) {
    std::ofstream outfile;
    cout << fixed << setprecision(6);
    outfile.open("../results/"+fileName, std::ios_base::app);
    outfile << endl << to_string(time * pow(10, -6)) << "," << to_string(n);
}

void printParallelTime(double time) {
    cout << "\n--------------- TIEMPOS --------------- " << endl;
    cout << fixed << setprecision(0);
    cout << "El tiempo tomado es: " << time * pow(10, 9) << " nanosegundos (ns)" << endl;
    cout << fixed << setprecision(6);
    cout << "El tiempo tomado es: " << time * pow(10, -6) << " milisegundos (ms)" << endl;
    cout << fixed << setprecision(9);
    cout << "El tiempo tomado es: " << time << " segundos (s)" << endl;
}

void printObtainedResults(Trip *cheapestTrip){
    cout << "\n---------- RESULTADOS OBTENIDOS ---------- " << endl;
    cout << "El mejor Trip (recorrido) obtenido: [ ";
    for (size_t i = 0; i < cheapestTrip->nodes.size(); i++) {
        cout << cheapestTrip->nodes[i] << " ";
    }
    cout << cheapestTrip->nodes[0] << " ]";
    cout << "\nEl mejor totalCost (costo mínimo de viaje) obtenido: " << cheapestTrip->totalCost << endl;
}

void validateResult(int result[], int resultToCompare[], int n, int cost, int costToCompare){
    bool isPathCorrect = true;
    bool isCostCorrect = true;

    for(int i=0; i < n; i++){
        if(result[i] != resultToCompare[i]){
            isPathCorrect = false;
        }
    }

    if(cost != costToCompare) isCostCorrect = false;
    string boolIsPathCorrect = isPathCorrect ? "true" : "false";
    string boolIsCostCorrect = isCostCorrect ? "true" : "false";
    cout << "\n------------ VALIDACIONES ------------ " << endl;
    cout << "El Trip obtenido es correcto: " << boolIsPathCorrect;
    cout << "\nEl totalCost es correcto: " << boolIsCostCorrect;
    cout << endl;
}

#endif