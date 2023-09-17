#include "algorithm_module.h"

#include <set>

class dijkstra : public algorithm_module {
    void dijkstra_seek(int &start) {
        std::vector<long> dist(g.size(), INT64_MAX);
        std::set<std::pair<long, long>> st;

        dist[start] = 0;
        for (int i = 0; i < dist.size(); i++) {
            st.insert({dist[i], i});
        }

        while (!st.empty()) {
            std::pair<long, long> fr = (*st.begin());
            st.erase(st.begin());
            long v = fr.second;

            for (int k = 0; k < g[v].size(); k++) {
                long to = g[v][k].first;
                if (dist[v] + g[v][k].second < dist[to]) {
                    st.erase({dist[to], to});
                    dist[to] = dist[v] + g[v][k].second;
                    st.insert({dist[to], to});
                }
            }
        }
    }

    int start{}, nodes{}, edges{};
    std::vector<std::vector<std::pair<long, long>>> g{};

public:

    int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) override {
        dijkstra_seek(start);
        return nodes;
    }

    void setup(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big,
        std::mt19937 &gen) override {
        nodes = dist_big(gen);
        edges = dist_big(gen) % (nodes*(nodes-1)/2);

        g.clear();
        g.resize(nodes);

        for (int i = 0; i < edges; i++) {
            int f = dist_big(gen) % nodes;
            int s = dist_big(gen) % nodes;
            int price = dist_small(gen);
            g[f].push_back({s, price});
            g[s].push_back({f, price});
        }

        start = dist_big(gen) % nodes;
    }
};