#pragma once

#include "IGraph.h"

class ListGraph : public IGraph {
private:
    std::vector<std::vector<int>> verts;
public:
    explicit ListGraph(int verts_num);
    explicit ListGraph(const IGraph &g);
    ~ListGraph() override;
    std::vector<int> GetNextVertices(int vtx) const override;
    std::vector<int> GetPrevVertices(int vtx) const override;
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
};