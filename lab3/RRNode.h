#ifndef RRNODE_H
#define RRNODE_H

#include <ostream>
#include <vector>

using namespace std;

class RRNode;
class Net;

class RRNode{
public:
    enum rrType { H_WIRE, V_WIRE, CB_WIRE };
    const char *rrTypeStr[3] = {"H_WIRE", "V_WIRE", "CB_WIRE"};

    RRNode(rrType type, int x, int y, int idx);
    virtual ~RRNode();

private:
    vector<RRNode *> connections;
    rrType type;
    int x;
    int y;
    int idx;
    Net *net;

public:
    void connect(RRNode &node);
    bool isConnected(RRNode &node);
    rrType getType() { return type; }
    int getX() { return x; }
    int getY() { return y; }
    int getIdx() { return idx; }

    bool isUsed() { return net != nullptr; }
    void setNet(Net &net);
    Net *getNet() { return net; }
    std::vector<RRNode *> &getConnections() { return connections; }

    friend std::ostream &operator<<(std::ostream &out, RRNode const &node) {
        out << "RRNode (" << node.x << ", " << node.y << ")."
            << node.rrTypeStr[node.type] << "." << node.idx;
        return out;
    }
};

#endif