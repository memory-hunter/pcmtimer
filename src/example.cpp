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
        srand(time(nullptr));
        std::fstream file("test_cases.txt", std::ios::out);
        int testCases = 1000;
        std::vector<std::pair<std::chrono::nanoseconds, int>> v;
        std::vector<std::pair<int, Node>> v1;
        while (testCases--)
        {
            int n = rand() % 1000000;
            auto start = std::chrono::high_resolution_clock::now();
            Node *root = nullptr;
            for (int k = 0; k < n; k++)
            {
                root = insert(root, rand() % INT_MAX);
            }
            for (int k = 0; k < 10000; k++)
            {
                int op = rand() % 3;
                if (op == 1)
                    bool x = search(root, rand() % 2147483647);
                if (op == 2)
                    root = insert(root, rand() % 2147483647);
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

            v.push_back(std::make_pair(duration, n));
            v1.push_back(std::make_pair(n, *root));
            delete root;
        }
        sort(v.begin(), v.end());
        for (int k = 0; k < v.size(); k++)
            if (v1[k].first == v[v.size()-1].second){
                std::cout << "Slowest run found! Running PCM...\n";
                pcm_runner(&v1[k].second);
                std::cout << "Done!\n";
            }
            
        for (int k = 0; k < v1.size(); k++)
            if (abs(v1[k].first-v[v.size()-1].second) < 3) {
                std::cout << "Neighbouring N within 50 found! Running PCM...\n";
                pcm_runner(&v1[k].second);
                std::cout << "Done!\n";
            }
            
                
        file << v[v.size() - 1].second << " " << v[v.size() - 1].first.count() << std::endl;
        file << v[0].second << " " << v[0].first.count() << std::endl;
        file.close();
    }

    void pcm_runner(Node* root)
    {
        static pcm::PCM *m = pcm::PCM::getInstance();

        if (m->program() != pcm::PCM::Success)
        {
            std::cout << "Failed to start PCM" << std::endl;
            exit(1);
        }

        auto start = std::chrono::high_resolution_clock::now();

        pcm::SystemCounterState before_sstate = pcm::getSystemCounterState();

        for (int k = 0; k < 10000; k++)
        {
            int op = rand() % 3;
            if (op == 1)
                bool x = search(root, rand() % 2147483647);
            if (op == 2)
                root = insert(root, rand() % 2147483647);
        }

        pcm::SystemCounterState after_sstate = pcm::getSystemCounterState();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

        std::cout << "Runtime was: " << duration.count() << "\n";

        printer::printSystemCounterStateDiff(before_sstate, after_sstate);

        m->cleanup();
    }
};