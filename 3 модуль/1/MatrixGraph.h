#pragma once

#include "IGraph.h"

class MatrixGraph : public IGraph {
private:
    std::vector<std::vector<bool>> verts;
public:
    explicit MatrixGraph(int verts_num);
    explicit MatrixGraph(const IGraph &g);
    ~MatrixGraph() override = default;
    std::vector<int> GetNextVertices(int vtx) const override;
    std::vector<int> GetPrevVertices(int vtx) const override;
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
};