#ifndef NET_H
#define NET_H

#include <set>

using namespace std;

class RRNode;

class Net{
public:
    Net(RRNode &source, int idx);
    virtual ~Net();

private:
    RRNode &source;
    int idx;
    set<RRNode *> sinks;
    set<RRNode *> usedRRs;

public:
    void addSink(RRNode &dest);
    RRNode &getSource() { return source; }
    std::set<RRNode *> &getSinks() { return sinks; }
    void finalizeRouting();

    void clearPath() { usedRRs.clear(); }
    void addRRToPath(RRNode &node) { usedRRs.insert(&node); }
    std::set<RRNode *> &getPath() { return usedRRs; }
    int getIdx() { return idx; }
    bool verifyRouting();
};

#endif