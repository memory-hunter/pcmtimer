#include "algorithm_module.h"

#include <set>

class dijkstra : public algorithm_module
{
    std::vector<long> dijkstra_seek(int &start, std::vector<std::vector<std::pair<long, long>>> &g)
    {
        std::vector<long> dist(g.size(), INT64_MAX);
        std::set<std::pair<long, long>> st;

        dist[start] = 0;
        for (int i = 0; i < dist.size(); i++)
        {
            st.insert({dist[i], i});
        }

        while (!st.empty())
        {
            std::pair<long, long> fr = (*st.begin());
            st.erase(st.begin());
            long v = fr.second;

            for (int k = 0; k < g[v].size(); k++)
            {
                long to = g[v][k].first;

                if (dist[v] + g[v][k].second < dist[to])
                {
                    st.erase({dist[to], to});
                    dist[to] = dist[v] + g[v][k].second;
                    st.insert({dist[to], to});
                }
            }
        }
        return dist;
    }

public:
    int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big,
            std::mt19937 &gen) override
    {
        int vertex = dist_big(gen);
        int nodes = dist_big(gen);

        std::vector<std::vector<std::pair<long, long>>> g;
        g.resize(vertex);

        for (int i = 0; i < nodes; i++)
        {
            int f = dist_big(gen) % vertex;
            int s = dist_big(gen) % vertex;
            int price = dist_small(gen);
            g[f].push_back({s, price});
            g[s].push_back({f, price});
        }

        int start = dist_small(gen) % vertex;

        dijkstra_seek(start, g);

        return vertex;
    }
};