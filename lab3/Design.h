#ifndef DESIGN_H
#define DESIGN_H

#include <map>
#include <string>
#include <Vector>

using namespace std;

class Net;
class RRNode;

class Design {
public:
    Design();
    virtual ~Design();

private:
    vector<Net *> nets;

public:
    void addNet(Net &net);
    int getNumNets() { return nets.size(); }
    Net &getNet(int idx) { return *(nets[idx]); }
    vector<Net*> &getNets() { return nets; }
    bool verifyRouting();
};

#endif