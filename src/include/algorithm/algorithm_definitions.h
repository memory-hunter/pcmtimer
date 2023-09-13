#pragma once

#ifndef PCMTIMER_ALGORITHM_DEFINITIONS_H
#define PCMTIMER_ALGORITHM_DEFINITIONS_H

#include <algorithm>
#include <array>
#include <vector>
#include <set>

#include "algorithm_module.h"

namespace algorithms {
    // Given N vertices of the weighed graph. Some of them are connected by the edge. Given start vertex. Find the minimum distance to every vertex from start

    class Dijkstra : public algorithm_module {
        long MAX_VALUE = UINT32_MAX;

        std::vector<long> dijsktra(int &start,  std::vector<std::vector<std::pair<long, long>>> &g) {
            std::vector<long> dist(g.size(), MAX_VALUE);
            std::set<std::pair<long,long>> st;

            dist[start] = 0;
            for (int i = 0; i < dist.size(); i++) {
                st.insert({dist[i],i});
            }

            while (!st.empty()) {
                std::pair < long, long > fr=(*st.begin());
                st.erase(st.begin());
                long v=fr.second;

                for (int k=0; k<g[v].size(); k++) {
                    long to=g[v][k].first;

                    if (dist[v] + g[v][k].second < dist[to]) {
                        st.erase({dist[to],to});
                        dist[to]=dist[v] + g[v][k].second;
                        st.insert({dist[to],to});
                    }
                }
            }
            return dist;
        }


    public:
        int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big,
                std::mt19937 &gen) override {
            int vertex = dist_big(gen);
            int nodes = dist_big(gen);

            std::vector<std::vector<std::pair<long, long>>> g;
            g.resize(vertex);

            for (int i = 0; i < nodes; i++) {
                int f = dist_big(gen);
                int s = dist_big(gen);
                int price = dist_small(gen);
                g[f].push_back({s,price});
                g[s].push_back({f,price});
            }

            int start = dist_small(gen);

            dijsktra(start, g);

            return vertex;
        }
    };

    class quick_sort : public algorithm_module {
        int partition(int *arr, int low, int high) {
            int pivot = arr[high];
            int i = low - 1;
            for (int j = low; j < high; j++) {
                if (arr[j] < pivot) {
                    i++;
                    std::swap(arr[i], arr[j]);
                    // Was to count upto 10 on each swap
                }
            }
            std::swap(arr[i + 1], arr[high]);
            return i + 1;
        }

        void quick_sort_impl(int *arr, int low, int high) {
            if (low < high) {
                int pi = partition(arr, low, high);
                quick_sort_impl(arr, low, pi - 1);
                quick_sort_impl(arr, pi + 1, high);
            }
        }

    public:
        quick_sort() : algorithm_module() {}

        ~quick_sort() = default;

        int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big,
                std::mt19937 &gen) override {
            int n = dist_big(gen);
            int *arr = new int[n];
            for (int j = 0; j < n; j++)
                arr[j] = dist_big(gen);
            quick_sort_impl(arr, 0, n - 1);
            delete[] arr;
            return n;
        }
    };


    class avl_trees : public algorithm_module {
        class Node {
        public:
            int key;
            Node *left;
            Node *right;
            int height;
        };

        int height(Node *N) {
            if (N == nullptr)
                return 0;
            return N->height;
        }

        Node *newNode(int key) {
            Node *node = new Node();
            node->key = key;
            node->left = nullptr;
            node->right = nullptr;
            node->height = 1;
            return node;
        }

        Node *rightRotate(Node *y) {
            Node *x = y->left;
            Node *T2 = x->right;
            x->right = y;
            y->left = T2;
            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left), height(x->right)) + 1;
            return x;
        }

        Node *leftRotate(Node *x) {
            Node *y = x->right;
            Node *T2 = y->left;
            y->left = x;
            x->right = T2;
            x->height = max(height(x->left), height(x->right)) + 1;
            y->height = max(height(y->left), height(y->right)) +1;
            return y;
        }

        int getBalance(Node *N) {
            if (N == nullptr)
                return 0;
            return height(N->left) - height(N->right);
        }

        Node *insert(Node *node, int key) {
            if (node == nullptr)
                return (newNode(key));
            if (key < node->key)
                node->left = insert(node->left, key);
            else if (key > node->key)
                node->right = insert(node->right, key);
            else
                return node;
            node->height = 1 + max(height(node->left), height(node->right));
            int balance = getBalance(node);
            if (balance > 1 && key < node->left->key)
                return rightRotate(node);
            if (balance < -1 && key > node->right->key)
                return leftRotate(node);
            if (balance > 1 && key > node->left->key) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if (balance < -1 && key < node->right->key) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            return node;
        }

        bool search(Node *root, int val) {
            if (root == nullptr)
                return false;
            if (root->key == val)
                return true;
            if (root->key < val)
                search(root->left, val);
            else
                search(root->right, val);
            return false;
        }

    public:
        avl_trees() : algorithm_module() {}

        ~avl_trees() = default;

        int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big,
                std::mt19937 &gen) override {
            int n = dist_big(gen);
            Node *root = nullptr;
            for (int j = 0; j < n; j++)
                root = insert(root, dist_big(gen));
            for (int j = 0; j < n; j++)
                search(root, dist_big(gen));
            return n;
        }
    };
}

#endif //PCMTIMER_ALGORITHM_DEFINITIONS_H