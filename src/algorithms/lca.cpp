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

    std::vector<std::vector<int>> _tree;

    std::vector<int> _parent;
    std::vector<int> _time_in, _time_out;

    std::vector<std::vector<int>> _dp;

    int timer{}, lg{};

    void DFS(int v, int p) {
        _parent[v] = p;
        _dp[v][0] = p;

        for (int k = 1; k <= lg; k++) {
            _dp[v][k] = _dp[_dp[v][k - 1]][k - 1];
        }

        _time_in[v] = timer++;

        for (int k = 0; k < _tree[v].size(); k++) {
            int to = _tree[v][k];
            if (to == p) continue;
            DFS(to, v);
        }

        _time_out[v] = timer++;
    }

    bool subtree(int a, int b) {
        return (_time_in[a] <= _time_in[b] && _time_out[b] <= _time_out[a]);
    }

    int LCA(int a, int b) {
        if (subtree(a, b))
            return a;
        if (subtree(b, a))
            return b;

        for (int k = lg; k >= 0; k--) {
            if (_dp[a][k] == 0)
                continue;
            if (subtree(_dp[a][k], b))
                continue;
            a = _dp[a][k];
        }

        return _parent[a];
    }

    int nodes{}, a{}, b{};


public:

    int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) override {
        int lca = LCA(a, b);
        return nodes;
    }

    void setup(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) override {
        nodes = dist_big(gen);

        lg = log2(nodes+1);

        _dp.resize(nodes+1);
        for (int k=0; k<=nodes; k++) {
            _dp[k].resize(lg+1);
        }

        _time_in.resize(nodes+1);
        _time_out.resize(nodes+1);
        _parent.resize(nodes+1);

        _tree = random_tree::getRandomTree(nodes, dist_big, gen);
        DFS(1, 0);
        a = dist_big(gen) % nodes + 1;
        b = dist_big(gen) % nodes + 1;
    }
};