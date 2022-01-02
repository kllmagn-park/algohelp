#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verts_num) {
    verts.resize(verts_num);
    for (auto &vert : verts) vert.resize(verts_num, false);
}

MatrixGraph::MatrixGraph(const IGraph &g) {
    verts.resize(g.VerticesCount());
    for (int i = 0; i < g.VerticesCount(); i++) {
        verts[i].resize(g.VerticesCount(), false);
        for(auto &vert : g.GetNextVertices(i)) verts[i][vert] = true;
    }
}

std::vector<int> MatrixGraph::GetNextVertices(int vtx) const {
    std::vector<int> res;
    for(int i = 0; i < verts[vtx].size(); i++) if (verts[vtx][i]) res.push_back(i);
    return res;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vtx) const {
    std::vector<int> res;
    for(int i = 0; i < verts.size(); i++) if (verts[i][vtx]) res.push_back(i);
    return res;
}

void MatrixGraph::AddEdge(int from, int to) { verts[from][to] = true; }

int MatrixGraph::VerticesCount() const { return verts.size(); }