#ifndef EVALUATE_H
#define EVALUATE_H
#include <set>
#include "Graph.h"

int calculate_cut(Graph graph, set<int> X, set<int> Y);

int evaluate(Graph graph, string partition_name);

#endif