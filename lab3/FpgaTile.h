#ifndef FPGATILE_H
#define FPGATILE_H

#include <assert.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class RRNode;

class FpgaTile{
public:
    FpgaTile(int r, int c, int W);
    virtual ~FpgaTile();

private:
    int x;
    int y;
    int W;

    FpgaTile *left;
    FpgaTile *right;
    FpgaTile *up;
    FpgaTile *down;

    map<int, RRNode *> logicPin;
    vector<RRNode *> vWires;
    vector<RRNode *> hWires;

    vector<RRNode *> rrNodes;

public:
    int getX() { return x; }
    int getY() { return y; }

    vector<RRNode *> &getRRNodes() { return rrNodes; }

    FpgaTile *getDown() const { return down; }
    void setDown(FpgaTile *down) { this->down = down; }

    FpgaTile *getUp() const { return up; }
    void setUp(FpgaTile *up) { this->up = up; }

    FpgaTile *getLeft() const { return left; }
    void setLeft(FpgaTile *left) { this->left = left; }

    FpgaTile *getRight() const { return right; }
    void setRight(FpgaTile *right) { this->right = right; }

    void generateContents();
    void populateSwitchbox();

    RRNode &getLogicPin(int idx) {
        assert(logicPin.find(idx) != logicPin.end());
        return *(logicPin[idx]);
    }

    RRNode &getVWire(int idx) {
        assert((size_t) idx < vWires.size());
        return *(vWires[idx]);
    }

    RRNode &getHWire(int idx) {
        assert((size_t) idx < hWires.size());
        return *(hWires[idx]);
    }

};

#endif