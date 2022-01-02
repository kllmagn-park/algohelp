#include "ListGraph.h"

ListGraph::ListGraph(int verts_num) { verts.resize(verts_num); }

ListGraph::ListGraph(const IGraph &g) {
    verts.resize(g.VerticesCount());
    for (int i = 0; i < g.VerticesCount(); i++) verts[i] = g.GetNextVertices(i);
}

ListGraph::~ListGraph() {}

std::vector<int> ListGraph::GetNextVertices(int vtx) const {
    std::vector<int> res(verts[vtx].begin(), verts[vtx].end());
    return res;
}

std::vector<int> ListGraph::GetPrevVertices(int vtx) const {
    std::vector<int> res;
    for (int parent = 0; parent < verts.size(); parent++) {
        for (auto &vert: verts[parent]) {
            if (vert == vtx) {
                res.push_back(parent);
                break;
            }
        }
    }
    return res;
}

void ListGraph::AddEdge(int from, int to) { verts[from].push_back(to); }

int ListGraph::VerticesCount() const { return verts.size(); }