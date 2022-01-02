#pragma once

#include <iostream>
#include <vector>

class IGraph {
public:
    virtual ~IGraph() = default;

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vtx) const = 0;

};