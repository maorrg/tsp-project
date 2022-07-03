#include "tsp.h"
#include "utils/tsp_functions.h"

void TSP::sequential() {
    int expectedTrip[N+1];
    int expectedCost;

    read(this->matrixFile, &n, &expectedCost, costMatrix, expectedTrip);
    stack<Trip *> stack;
    auto startTime = chrono::high_resolution_clock::now();
    vector<int> rootOfcheapestTrip;
    cheapestTrip = createTrip(rootOfcheapestTrip, INT_MAX);

    vector<int> rootNodes;
    rootNodes.push_back(0);
    Trip *root = createTrip(rootNodes, 0);
    stack.push(root);

    while (!stack.empty()) {
        Trip *currentTrip = stack.top();
        stack.pop();
        if (currentTrip->nodes.size() == n) {
            if (isCheapestTrip(currentTrip)) updateCheapestTrip(currentTrip);
        } else {
            for (int i = n - 1; i > 0; i--) {
                if (wasVisited(currentTrip, i)) {
                    addNode(currentTrip, i);
                    pushTrip(stack, currentTrip);
                    removeNode(currentTrip, i);
                }
            }
        }
        delete currentTrip;
    }
    auto stopTime = chrono::high_resolution_clock::now();
    int ansTSP[N+1];
    for (int i = 0; i < cheapestTrip->nodes.size(); i++) {
        ansTSP[i] = cheapestTrip->nodes[i];
    }
    ansTSP[N] = cheapestTrip->nodes[0];
    printObtainedResults(cheapestTrip);
    auto finalTime = chrono::duration_cast<chrono::nanoseconds>(stopTime - startTime).count();
    validateResult(ansTSP, expectedTrip, cheapestTrip->totalCost, expectedCost);
    printSequentialTime(finalTime);
}