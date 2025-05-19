#ifndef FPGA_H
#define FPGA_H

#include <map>
#include <vector>

using namespace std;

class FpgaTile;

class FPGA{
public:
    FPGA(int gridSize, int W);
    virtual ~FPGA();

private:
    int N;
    int W;
    map<int, map<int, FpgaTile *>> tileMap;
    vector<FpgaTile *> tiles;

public:
    FpgaTile &getTile(int x, int y) { return *(tileMap[x][y]); }
    vector<FpgaTile *> &getTiles() { return tiles; }

    int getN() { return N; }
    int getW() { return W; }
    int getNumSegmentsUsed();
};

#endif