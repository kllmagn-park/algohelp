#include "SetGraph.h"

SetGraph::SetGraph(int verts_num) { verts.resize(verts_num); }

SetGraph::SetGraph(const IGraph &g) {
    verts.resize(g.VerticesCount());
    for (int i = 0; i < g.VerticesCount(); i++) {
        std::vector<int> tmp = g.GetNextVertices(i);
        for (auto &vert: tmp) verts[i].insert(vert);
    }
}

std::vector<int> SetGraph::GetNextVertices(int vtx) const {
    std::vector<int> res;
    for (auto vert: verts[vtx]) res.push_back(vert);
    return res;
}

std::vector<int> SetGraph::GetPrevVertices(int vtx) const {
    std::vector<int> res;
    for (int i = 0; i < verts.size(); i++) for (auto vert : verts[i]) if (vert == vtx) res.push_back(i);
    return res;
}

void SetGraph::AddEdge(int from, int to) { verts[from].insert(to); }

int SetGraph::VerticesCount() const { return verts.size(); }