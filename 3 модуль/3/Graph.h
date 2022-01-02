#pragma once

#include "IGraph.h"
#include <iostream>
#include <vector>

#include <utility>
#include <queue>
#include <unordered_set>
#include <set>

class Graph : public IGraph {
private:
    std::vector<std::vector<std::pair<int, int>>> verts;
public:
    explicit Graph(int n) { verts.resize(n); };
    ~Graph() override = default;
    std::vector<std::pair<int, int>> GetNextVertices(int vtx) const override {
        std::vector<std::pair<int, int>> res(verts[vtx].begin(), verts[vtx].end());
        return res;
    };
    void AddEdge(int from, int to, int w) override {
        verts[from].push_back(std::make_pair(to, w));
        verts[to].push_back(std::make_pair(from, w));
    };
    int VerticesCount() const override {return verts.size();};
};

int traversal(const IGraph &g, int st, int e) {
    std::vector<int> vs(g.VerticesCount(), INT32_MAX-1);
    std::set<std::pair<int, int>> q;
    vs[st] = 0;
    q.insert(std::make_pair(0, st));
    while (!q.empty()) {
        int cour = q.begin()->second;
        q.erase(q.begin());
        std::vector<std::pair<int, int>> verts = g.GetNextVertices(cour);
        for (auto &vert: verts) {
            if (vs[vert.first] > vs[cour] + vert.second) {
                vs[vert.first] = vs[cour] + vert.second;
                q.insert(std::make_pair(vs[vert.first], vert.first));
            }
        }
    }
    return vs[e];
}

bool handle(std::pair<int, int> &pair, int cour, std::vector<int> &vs) {
    if (vs[pair.first] > vs[cour] + pair.second) {
        vs[pair.first] = vs[cour] + pair.second;
        return true;
    }
    return false;
}