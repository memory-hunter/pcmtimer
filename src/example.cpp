#include "algorithm_container.hpp"

class example_algorithm : public algorithm_container
{
    class Node
    {
    public:
        int key;
        Node *left;
        Node *right;
        int height;
    };

    // A utility function to get maximum
    // of two integers
    // A utility function to get the
    // height of the tree
    int height(Node *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    // A utility function to get maximum
    // of two integers
    int max_func(int a, int b)
    {
        return (a > b) ? a : b;
    }
    /* Helper function that allocates a
       new node with the given key and
       nullptr left and right pointers. */
    Node *newNode(int key)
    {
        Node *node = new Node();
        node->key = key;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1; // new node is initially
        // added at leaf
        return (node);
    }

    // A utility function to right
    // rotate subtree rooted with y

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max_func(height(y->left),
                             height(y->right)) +
                    1;
        x->height = max_func(height(x->left),
                             height(x->right)) +
                    1;

        // Return new root
        return x;
    }

    // A utility function to left
    // rotate subtree rooted with x
    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max_func(height(x->left),
                             height(x->right)) +
                    1;
        y->height = max_func(height(y->left),
                             height(y->right)) +
                    1;

        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(Node *N)
    {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node *insert(Node *node, int key)
    {
        /* 1. Perform the normal BST insertion */
        if (node == nullptr)
            return (newNode(key));

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else // Equal keys are not allowed in BST
            return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max_func(height(node->left),
                                    height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    bool search(Node *root, int val)
    {
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
    example_algorithm() = default;
    ~example_algorithm() = default;

    void run() override
    {
        Node *root = nullptr;
        for (int k = 0; k < 1000000; k++)
        {
            root = insert(root, rand() % 2147483647);
        }
        for (int k = 0; k < 10000; k++)
        {
            int op = rand() % 3;
            if (op == 1)
                bool x = search(root, rand() % 2147483647);
            if (op == 2)
                root = insert(root, rand() % 2147483647);
        }
    }
};