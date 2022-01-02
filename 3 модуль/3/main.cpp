#include "Graph.h"

int main() {
    int N; // количество городов
    int M; // количество дорог
    std::cin >> N >> M;
    Graph lg = Graph(N);
    int from, to, time; // откуда, куда, время в пути
    for (int i = 0; i < M; i++) {
        std::cin >> from >> to >> time;
        lg.AddEdge(from, to, time);
    }
    int st, e; // параметры маршрута
    std::cin >> st >> e;
    std::cout << traversal(lg, st, e);
    return 0;
}

