#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include "Net.h"
#include "Node.h"
#include "Graph.h"
#include "evaluate.cpp"
#include "solution.h"

using namespace std;

int main(int argc, char **argv) {

    Solution solution;

    if(argc != 2) {
        cout << "Usage: ./main.exe benchmark_file" << endl;
        exit(-1);
    }
    string benchmark_name = argv[1];
    Graph graph;

    solution.read_benchmark(graph, benchmark_name);    

    cout << "Num nodes: " << graph.get_node_num() << endl;
    cout << "Num nets: " << graph.get_net_num() << endl;

    // TODO: finish your partition algorithm
    // for example
    // solution.my_partition_algorithm(Graph graph, set<int> &X, set<int> &Y);

    // cout << evaluate(graph, "./ibm01_partition.txt") << endl;

    return 0;
}