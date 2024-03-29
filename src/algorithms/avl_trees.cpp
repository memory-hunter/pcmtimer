#include "algorithm_module.h"

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
        y->height = max(height(y->left), height(y->right)) + 1;
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
    
    Node *root = nullptr;
    int n{};

public:
    avl_trees() : algorithm_module() {}

    ~avl_trees() = default;

    int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) override {
        for (int j = 0; j < n; j++)
            search(root, dist_big(gen));
        return n;
    }

    void setup(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) override {
        n = dist_big(gen);
        for (int j = 0; j < n; j++)
            root = insert(root, dist_big(gen));
    }
};