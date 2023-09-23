#include "algorithm_module.h"

#include <set>

class lca : public algorithm_module {

    class random_tree {
    public:
        static std::vector<std::vector<int>> getRandomTree(int n, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) {
            std::vector<int> elems;
            std::vector<int> used {1};
            std::vector<std::vector<int>> tree(n+1);

            for (int i = 2; i <= n; i++)
                elems.emplace_back(i);
            std::shuffle(elems.begin(), elems.end(), gen);

            tree[1].emplace_back(elems[0]);
            tree[elems[0]].emplace_back(1);
            used.emplace_back(elems[0]);

            for (int i = 1; i < elems.size(); i++) {
                int parent = used[(dist_big(gen) % used.size())];
                tree[parent].emplace_back(elems[i]);
                tree[elems[i]].emplace_back(parent);
                used.emplace_back(elems[i]);
            }

            return tree;
        }
    };

    std::vector<std::vector<int>> tree;

    std::vector<int> parent;
    std::vector<int> time_in, time_out;

    std::vector<std::vector<int>> dp;

    int timer;
    int lg;

    void DFS(int v, int p) {
        parent[v] = p;
        dp[v][0] = p;

        for (int k = 1; k <= lg; k++) {
            dp[v][k] = dp[dp[v][k - 1]][k - 1];
        }

        time_in[v] = timer++;

        for (int k = 0; k < tree[v].size(); k++) {
            int to = tree[v][k];
            if (to == p) continue;
            DFS(to, v);
        }

        time_out[v] = timer++;
    }

    bool subtree(int a, int b) {
        return (time_in[a] <= time_in[b] && time_out[b] <= time_out[a]);
    }

    int LCA(int a, int b) {
        if (subtree(a, b))
            return a;
        if (subtree(b, a))
            return b;

        for (int k = lg; k >= 0; k--) {
            if (dp[a][k] == 0)
                continue;
            if (subtree(dp[a][k], b))
                continue;
            a = dp[a][k];
        }

        return parent[a];
    }

public:

    int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) override {
        int nodes = dist_big(gen);
        tree = random_tree::getRandomTree(nodes, dist_big, gen);
        DFS(1, 0);
        int a = dist_big(gen);
        int b = dist_big(gen);
        int lca = LCA(a, b);
        return nodes;
    }
};