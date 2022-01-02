#pragma once

#include "IGraph.h"
#include <unordered_set>

class ArcGraph : public IGraph {
private:
    std::vector<std::pair<int, int>> verts;
public:
    explicit ArcGraph(int verts_num);
    explicit ArcGraph(const IGraph &g);
    ~ArcGraph() override = default;
    std::vector<int> GetNextVertices(int vtx) const override;
    std::vector<int> GetPrevVertices(int vtx) const override;
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
};