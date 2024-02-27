#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cstring>

class Node {
    int key;
    bool color; // Black: true, Red: false
    Node *parent, *left, *right;

    friend class RBTree;

public:
    Node(int key = 0) : key(key), color(false), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RBTree {
    Node *root;
    Node *neel;

    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void insertFixUp(Node *z);
    void deleteFixUp(Node *x);
    Node* search(int key) const;
    Node* minimum(Node *node) const;
    void transplant(Node *u, Node *v);
    Node* treeSuccessor(Node *x) const;

public:
    RBTree();
    ~RBTree();

    void insert(int key);
    void remove(int key);
    void printInOrder() const;
    // Additional utility functions can be added here
};

// Implementations of RBTree methods...

int main() {
    RBTree rbTree;
    std::fstream infile("input.txt", std::ios::in);
    if (!infile) {
        std::cerr << "The file cannot be opened!\n";
        return 1;
    }

    int times, function, num;
    while (infile >> times) {
        for (int i = 0; i < times; ++i) {
            infile >> function >> num;
            if (function == 1) {
                // Insert operation
                int value;
                for (int j = 0; j < num; ++j) {
                    infile >> value;
                    rbTree.insert(value);
                }
                rbTree.printInOrder();
            } else if (function == 2) {
                // Delete operation
                int value;
                for (int j = 0; j < num; ++j) {
                    infile >> value;
                    rbTree.remove(value);
                }
                rbTree.printInOrder();
            }
        }
    }

    infile.close();
    return 0;
}
