#include "Graph.h"

int main() {
    int v, n; // количество вершин и ребер соответственно
    std::cin >> v >> n;
    Graph lg = Graph(v);
    int from, to, size;
    for (int i = 0; i < n; i++) {
        std::cin >> from >> to; // информация о ребре
        lg.AddEdge(from, to);
    }
    int u, w; // пара вершин для запроса
    std::cin >> u >> w;
    std::cout << traversal(lg, u, w);
    return 0;
}
