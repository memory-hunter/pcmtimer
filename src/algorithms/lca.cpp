#include "algorithm_module.h"

#include <set>

class lca : public algorithm_module {

    class random_tree {

        // using Prufer's algorithm to create random tree
        static std::vector<std::vector<int>> getTreeEdges(std::vector<int> prufer, int m) {
            int nodes = m + 2;
            std::vector<int> node_set(nodes, 0);
            std::vector<std::vector<int>> randomTree(nodes);

            for (int i = 0; i < nodes - 2; i++)
                node_set[prufer[i]-1]++;

            for (int i = 0; i < nodes - 2; i++) {
                for (int j = 0; j < nodes; j++) {
                    if (node_set[j] == 0) {
                        node_set[j] = -1;
                        randomTree[j+1].push_back(prufer[i]);
                        randomTree[prufer[i]].push_back(j+1);
                        node_set[prufer[i]-1]--;
                        break;
                    }
                }
            }

            int j = 0; int lastNode = -1; int lastNode1 = -1;
            // For the last element
            for (int i = 0; i < nodes; i++) {
                if (node_set[i] == 0 && j == 0) {
                    lastNode = i+1;
                    j++;
                } else if (node_set[i] == 0 && j == 1) {
                    lastNode1 = i+1;
                }
            }

            randomTree[lastNode].push_back(lastNode1);
            randomTree[lastNode1].push_back(lastNode);

            return randomTree;
        }

        static int ran(int l, int r) {
            return l + (rand() % (r - l + 1));
        }

        static std::vector<std::vector<int>> getRandomTree(int n) {
            srand(time(0));
            int length = n - 2;
            std::vector<int> arr(length);

            for (int i = 0; i < length; i++) {
                arr[i] = ran(0, length + 1) + 1;
            }
            return getTreeEdges(arr, length);
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

    int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big,
            std::mt19937 &gen)

    override {
        int nodes = dist_big(gen);
        // TO-DO
    }
};