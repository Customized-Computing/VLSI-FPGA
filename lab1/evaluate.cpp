#include <set>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "evaluate.h"

using namespace std;

#define BIPARTITION_RATIO 0.02

int calculate_cut(Graph graph, set<int> X, set<int> Y) {
    int size_X = X.size();
    int size_Y = Y.size();
    int size = size_X + size_Y;
    if(!(((size_X * 1.0 / size >= 0.5-BIPARTITION_RATIO) && (size_X * 1.0 / size <= 0.5+BIPARTITION_RATIO)) \
        && ((size_Y * 1.0 / size >= 0.5-BIPARTITION_RATIO) && (size_Y * 1.0 / size <= 0.5+BIPARTITION_RATIO)))) {
        cerr << "The size of partition X and Y doesn't satisfy the requirement!" << endl;
        return -1;
    }

    int cut = 0;
    vector<Net *> nets = graph.get_nets();
    for(const auto& net : nets) {
        bool in_X = false, in_Y = false;
        for(const auto node : net->get_nodes()) {
            int index = node->get_index();
            if(X.find(index) != X.end())    in_X = true;
            if(Y.find(index) != Y.end())    in_Y = true;
        }
        if(in_X && in_Y)    cut++;
    }
    return cut;
}

int evaluate(Graph graph, string partition_name) {
    set<int> X;
    set<int> Y;
    string line;
    ifstream partition_file(partition_name);
    int i = 1;
    while(getline(partition_file, line)) {
        istringstream iss(line);
        int partition;
        iss >> partition;
        if(partition == 0){
            X.insert(i);
        }
        else{
            Y.insert(i);
        }
        i++;
    }
    
    return calculate_cut(graph, X, Y);
}