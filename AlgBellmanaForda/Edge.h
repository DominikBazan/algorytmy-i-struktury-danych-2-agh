#pragma once

using namespace std;

class Edge {
public:
    Edge(int v1, int v2, int p);
    int getV1() const;
    int getV2() const;
    int getP() const;
protected:
private:
    int v1, v2, p;
};
