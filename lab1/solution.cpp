#include "solution.h"

void Solution::read_benchmark(Graph &graph, string benchmark_name) {
    ifstream file(benchmark_name);

    if(!file.is_open()) {
        cerr << "Failed to open the file!" << endl;
        exit(-1);
    }

    int edge_num, node_num;
    string line;
    getline(file >> ws, line);
    istringstream iss(line);
    iss >> edge_num;
    iss >> node_num;

    
    for(int i = 0; i < edge_num; i++) {
        getline(file, line);
        istringstream iss(line);
        int node_id;
        
        Net *net = graph.add_net(i);

        while(iss >> node_id) {
            Node *node = graph.get_or_create_node(node_id);
            node->add_net(net);
            net->add_node(node);
        }
        
    }

    file.close();
}