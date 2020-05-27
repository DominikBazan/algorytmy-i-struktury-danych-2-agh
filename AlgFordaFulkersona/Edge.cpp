#include "Edge.h"

using namespace std;

Edge::Edge(int v1, int v2, int p) {
    this->v1 = v1;
    this->v2 = v2;
    this->p = p;
}

int Edge::getV1() const {
    return v1;
}

int Edge::getV2() const {
    return v2;
}

int Edge::getP() const {
    return p;
}
