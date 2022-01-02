#pragma once

#include "IGraph.h"
#include <iostream>
#include <vector>

#include <queue>

class Graph : public IGraph {
private:
    std::vector<std::vector<int>> verts;
public:
    explicit Graph(int n) { verts.resize(n); };
    ~Graph() override = default;
    std::vector<int> GetNextVertices(int vtx) const override {
        std::vector<int> res(verts[vtx].begin(), verts[vtx].end());
        return res;
    };
    void AddEdge(int from, int to) override {
        verts[from].push_back(to);
        verts[to].push_back(from);
    };
    int VerticesCount() const override { return verts.size(); };
};

int traversal(const IGraph &g, int st, int e) {
    std::queue<int> q;
    std::vector<int> v1(g.VerticesCount(), INT32_MAX - 1);
    std::vector<int> v2(g.VerticesCount(), 0);
    q.push(st);
    v1[st] = 0;
    v2[st] = 1;
    while (!q.empty()){
        int cur = q.front();
        q.pop();
        std::vector<int> verts = g.GetNextVertices(cur);
        for (auto vert: verts) {
            if (v1[vert] == v1[cur] + 1){
                v2[vert] += v2[cur];
            } else if (v1[vert] > v1[cur] + 1){
                v1[vert] = v1[cur] + 1;
                v2[vert] = v2[cur];
                q.push(vert);
            }
        }
    }
    return v2[e];
}