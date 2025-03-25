#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

class Solution{
    public:
        void read_benchmark(Graph &graph, string benchmark_name);
        // void my_partition_algorithm(Graph graph, set<int> &X, set<int> &Y);
};

#endif