#ifndef TSP_FUNCTIONS_H
#define TSP_FUNCTIONS_H

#include <iostream>
#include <algorithm>
#include <stack>
#include <climits>
#include "data_processor.h"

int n;
int costMatrix[N][N];
Trip *cheapestTrip;

Trip *createTrip(vector<int> &nodes, int totalCost) {
    Trip *node = new Trip;
    node->nodes = nodes;
    node->totalCost = totalCost;
    return node;
}

void addNode(Trip *&trip, int node) {
    trip->totalCost += costMatrix[trip->nodes.back()][node];
    trip->nodes.push_back(node);
}

void removeNode(Trip *&trip, int node) {
    trip->nodes.pop_back();
    trip->totalCost -= costMatrix[trip->nodes.back()][node];
}

void pushTrip(stack<Trip *> &stack, Trip *&trip) {
    Trip *tmpTrip = createTrip(trip->nodes, trip->totalCost);
    stack.push(tmpTrip);
}

bool isCheapestTrip(Trip *&trip) {
    int currentConectionCost = trip->totalCost + costMatrix[trip->nodes.back()][trip->nodes.front()];
    if (currentConectionCost < cheapestTrip->totalCost) return true;
    return false;
}

void updateCheapestTrip(Trip *&trip) {
    cheapestTrip->nodes = trip->nodes;
    cheapestTrip->totalCost = trip->totalCost + costMatrix[trip->nodes.back()][trip->nodes.front()];
}

bool wasVisited(Trip *&trip, int neighbour) {
    if (find(trip->nodes.begin(), trip->nodes.end(), neighbour) != trip->nodes.end()) return false;
    int currentTripCost = trip->totalCost + costMatrix[trip->nodes.back()][neighbour];
    bool lowerCost = (currentTripCost < cheapestTrip->totalCost);
    return lowerCost;
}

#endif