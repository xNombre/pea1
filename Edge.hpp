#pragma once

struct Edge {
    Edge(const size_t &fromVertex, const size_t &toVertex, const size_t &weight) : from(fromVertex), to(toVertex), weight(weight) { };

    Edge(const Edge &edge) : from(edge.from), to(edge.to), weight(edge.weight) { };

    Edge() { };

    size_t from, to;
    size_t weight;

    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
    bool operator>(const Edge &other) const
    {
        return weight > other.weight;
    }
    bool operator==(const Edge &other) const
    {
        return weight == other.weight;
    }
};