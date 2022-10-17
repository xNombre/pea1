#include "ListGraph.hpp"

const size_t &ListGraph::getEdgesCount() const
{
    return edgesCount;
}

const size_t &ListGraph::getVertexCount() const
{
    return edges.size();
}

void ListGraph::addEdge(const size_t &fromVertex, const size_t &toVertex, const size_t &weight)
{
    // Add more vertices if necessary
    const auto &max = std::max(fromVertex, toVertex) + 1;
    if (max > edges.size())
        edges.resize(max);

    edges[fromVertex].push_back(AdjacentEdge(toVertex, weight));

    // Dont add mirrored edge when graph is directed or edge is a cycle over same vertex
    if (!isDirected && fromVertex != toVertex)
        edges[toVertex].push_back(AdjacentEdge(fromVertex, weight));

    edgesCount++;
}

auto ListGraph::getVerticesAdjacentTo(const size_t &vertex) const -> const Array<AdjacentEdge> &
{
    return edges[vertex];
}

void ListGraph::print() const
{
    if (edges.size() == 0) {
        std::cout << KRED << "Graf jest pusty!" << RST << std::endl;
        return;
    }

    for (size_t i = 0; i < edges.size(); i++) {
        std::cout << KBLU << i << RST << ": ";

        for (size_t j = 0; j < edges[i].size(); j++) {
            std::cout << "[" << edges[i][j].edge << ", " << edges[i][j].weight << "] ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void ListGraph::clear()
{
    edgesCount = 0;
    edges = Array<Array<AdjacentEdge>>();
}
