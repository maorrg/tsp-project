#include "tsp_utils/tsp_functions.h"
#include <omp.h>

int main(int argc, char *argv[]) {
    int expectedTrip[N+1], expectedCost;
    read("../data/matrix_19.txt", &n, &expectedCost, costMatrix, expectedTrip);
    stack<Trip *> stackTSP;

    int threadCount = strtol(argv[1], NULL, 10);
    omp_set_num_threads(threadCount);

    vector<int> rootOfCheapestTrip;
    cheapestTrip = createTrip(rootOfCheapestTrip, INT_MAX);

    vector<int> rootNodes;
    rootNodes.push_back(0);

    double startTime = omp_get_wtime();

#pragma omp parallel private(stackTSP) 
{
    #pragma omp for
        for (int i = 1; i < n; i++) {
            Trip *branchTrip = createTrip(rootNodes, 0);
            addNode(branchTrip, i);
            stackTSP.push(branchTrip);
        }
        while (!stackTSP.empty()) {
            Trip *currentTrip = stackTSP.top();
            stackTSP.pop();
            if (currentTrip->nodes.size() == n) {
                if (isCheapestTrip(currentTrip)) {
                    #pragma omp critical 
                    {
                        if (isCheapestTrip(currentTrip))
                        {
                            updateCheapestTrip(currentTrip);
                        }
                    }
                }
            } else {
                for (int neighbour = n - 1; neighbour > 0; neighbour--) {
                    if (wasVisited(currentTrip, neighbour)) {
                        addNode(currentTrip, neighbour);
                        pushTrip(stackTSP, currentTrip);
                        removeNode(currentTrip, neighbour);
                    }
                }
            }
            delete currentTrip;
        }
    }

    double stopTime = omp_get_wtime();
    int result_tsp[N + 1];
    for (size_t i = 0; i < cheapestTrip->nodes.size(); i++) {
        result_tsp[i] = cheapestTrip->nodes[i];
    }
    result_tsp[N] = cheapestTrip->nodes[0];
    printObtainedResults(cheapestTrip);
    double time = stopTime - startTime;
    validateResult(result_tsp, expectedTrip, n, cheapestTrip->totalCost, expectedCost);
    printParallelTime(time);
    writeObtainedResultsParallel("parallel_threads_times.csv",time,argv[1],n);
    return 0;
}