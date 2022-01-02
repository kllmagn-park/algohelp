#pragma once

#include "IGraph.h"
#include <unordered_set>

class SetGraph : public IGraph {
private:
    std::vector<std::unordered_set<int>> verts;
public:
    explicit SetGraph(int verts_num);
    explicit SetGraph(const IGraph &g);
    ~SetGraph() override = default;
    std::vector<int> GetNextVertices(int vtx) const override;
    std::vector<int> GetPrevVertices(int vtx) const override;
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
};