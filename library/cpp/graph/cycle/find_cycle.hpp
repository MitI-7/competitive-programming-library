#pragma once
#include "library/cpp/graph/graph.hpp"

template<typename T>
bool find_cycle_dfs(const int u, const Edge<T> &prev, std::vector<int> &state, std::vector<Edge<T>> &edges, const Graph<T> &graph) {
    state[u] = 1;
    for (const auto e: graph.graph[u]) {
        if (e.no == prev.no) {
            continue;
        }

        // 探索済み
        if (state[e.to] == 2) {
            continue;
        }

        edges.emplace_back(e);
        // find cycle
        if (state[e.to] == 1 or find_cycle_dfs(e.to, e, state, edges, graph)) {
            return true;
        }
        edges.pop_back();
    }

    state[u] = 2;
    return false;
}

// 有向グラフのサイクルをひとつ見つける
// 単純グラフでなくてもいい
// O(N + M)
// 辺番号をいれておくこと
template<typename T>
std::vector<Edge<T>> find_cycle(const Graph<T> &graph) {
    std::vector<Edge<T>> edges;
    std::vector<int> state(graph.num_nodes, 0);// 0: 未探索， 1: 探索中，2: 探索済み

    // u を始点とし，閉路を探索
    std::vector<Edge<T>> cycle;
    for (int u = 0; u < graph.num_nodes; ++u) {
        if (state[u] != 0) {
            continue;
        }
        if (find_cycle_dfs(u, Edge<T>{-1, -1, T{}, -1}, state, edges, graph)) {
            auto cycle_start = edges.back().to;
            bool in_cycle = false;
            for (auto e: edges) {
                // cycle の開始ノードを見つけた
                if (e.from == cycle_start) {
                    in_cycle = true;
                }
                if (in_cycle) {
                    cycle.emplace_back(e);
                }
            }
            break;
        }
    }

    return cycle;
}