#pragma once
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T>
class Edge {
public:
    int from;
    int to;
    T w;
    int no;

    Edge() : from(-1), to(-1), w(T{}), no(-1) {}

    Edge(const int from, const int to, const T w = 1, const int no = -1) : from(from), to(to), w(w), no(no) {}
};

template <typename T = int>
class Graph {
public:
    const int num_nodes;
    int num_edges;
    std::vector<std::vector<Edge<T>>> graph;
    std::unordered_map<int, std::pair<int, int>> no_edge;

    explicit Graph(const int num_nodes) : num_nodes(num_nodes), num_edges(0) { this->graph.resize(num_nodes); }

    void add_directed_edge(const int u, const int v, const T& w, const int no) {
        this->no_edge[no] = {u, this->graph[u].size()};
        this->graph[u].emplace_back(Edge(u, v, w, no));
        ++this->num_edges;
    }

    void add_directed_edge(const int u, const int v, const T& w = T{1}) {
        const int no = num_edges;
        this->add_directed_edge(u, v, w, no);
    }

    Edge<T>& get_edge(const int no) {
        const auto [u, i] = this->no_edge.at(no);
        return this->graph[u][i];
    }

    std::vector<Edge<T>>& operator[](const int u) { return this->graph[u]; }
};
