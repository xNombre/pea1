#pragma once

#include <iostream>

#include "Array.hpp"
#include "Edge.hpp"

using std::size_t;

#define RST  "\x1B[0m"
#define KRED  "\x1B[41m"
#define KBLU  "\x1B[44m"

class ListGraph {
public:
    struct AdjacentEdge {
        size_t edge;
        size_t weight;

        AdjacentEdge(size_t edge, size_t weight) : edge(edge), weight(weight) { }
        AdjacentEdge() { }
    };

    ListGraph(bool isDirected = true) : isDirected(isDirected) { }
    const size_t &getEdgesCount() const;
    const size_t &getVertexCount() const;
    void addEdge(const size_t &fromVertex, const size_t &toVertex, const size_t &weight);
    const Array<AdjacentEdge> &getVerticesAdjacentTo(const size_t &vertex) const;
    void print() const;
    void clear();

private:
    Array<Array<AdjacentEdge>> edges;
    size_t edgesCount = 0;
    bool isDirected;
};