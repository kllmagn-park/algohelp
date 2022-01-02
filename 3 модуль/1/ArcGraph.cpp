#include "ArcGraph.h"

ArcGraph::ArcGraph(int verts_num) { verts.resize(verts_num); }

ArcGraph::ArcGraph(const IGraph &g) {
    for (int i = 0; i < g.VerticesCount(); i++) {
        std::vector<int> tmp = g.GetNextVertices(i);
        for (auto &vert: tmp) {
            std::pair<int, int> tmp(i, vert);
            verts.push_back(tmp);
        }
    }
}

std::vector<int> ArcGraph::GetPrevVertices(int vtx) const {
    std::vector<int> res;
    for(auto &tmp : verts) if (tmp.second == vtx) res.push_back(tmp.first);
    return res;
}

std::vector<int> ArcGraph::GetNextVertices(int vtx) const {
    std::vector<int> res;
    for (auto &tmp : verts) if (tmp.first == vtx) res.push_back(tmp.second);
    return res;
}

void ArcGraph::AddEdge(int from, int to) {
    std::pair<int, int> tmp(from, to);
    verts.push_back(tmp);
}

int ArcGraph::VerticesCount() const {
    std::unordered_set<int> tmp;
    for(auto &p : verts){
        tmp.insert(p.first);
        tmp.insert(p.second);
    }
    return tmp.size();
}