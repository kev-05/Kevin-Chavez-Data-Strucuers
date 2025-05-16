//
//  main.cpp
//  Assignment 9
//
//  Created by Kevin Chavez on 04/22/25.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>

using namespace std;

template <typename Key>
class BTreeNode {
public:
    bool isLeaf;
    vector<Key> keys;
    vector<shared_ptr<BTreeNode>> children;
    const int t;  // Minimum degree

    BTreeNode(int _t, bool _isLeaf) : t(_t), isLeaf(_isLeaf) {
        if (t < 2) throw invalid_argument("Minimum degree must be at least 2");
        keys.reserve(2*t-1);
        if (!_isLeaf) {
            children.reserve(2*t);
        }
    }

    int findKey(const Key& k) const {
        auto it = lower_bound(keys.begin(), keys.end(), k);
        return distance(keys.begin(), it);
    }

    void insertNonFull(const Key& k) {
        int idx = findKey(k);
        
        // Check for duplicate key
        if (idx < keys.size() && keys[idx] == k) {
            return; // Key already exists
        }
        
        if (isLeaf) {
            keys.insert(keys.begin() + idx, k);
        } else {
            // Ensure child exists
            if (idx > children.size()) {
                throw out_of_range("Child index out of range");
            }

            // Handle full child
            if (children[idx]->keys.size() == 2*t-1) {
                splitChild(idx);
                // After split, decide which child to go to
                if (idx < keys.size() && keys[idx] < k) {
                    idx++;
                }
            }

            // Final bounds check
            if (idx >= children.size()) {
                throw out_of_range("Child index out of range after operation");
            }

            children[idx]->insertNonFull(k);
        }
    }

    void splitChild(int idx) {
        if (idx < 0 || idx >= children.size()) {
            throw out_of_range("Invalid child index for splitting");
        }

        auto y = children[idx];
        if (!y || y->keys.size() != 2 * t - 1) {
            throw logic_error("Attempt to split invalid child node");
        }

        auto z = make_shared<BTreeNode>(y->t, y->isLeaf);

        // Save middle key before modifying y
        Key midKey = y->keys[t - 1];

        // Move t-1 keys from y to z
        move(y->keys.begin() + t, y->keys.end(), back_inserter(z->keys));
        y->keys.resize(t - 1);

        // Move children if not leaf
        if (!y->isLeaf) {
            move(y->children.begin() + t, y->children.end(), back_inserter(z->children));
            y->children.resize(t);
        }

        // Insert new child and middle key
        children.insert(children.begin() + idx + 1, z);
        keys.insert(keys.begin() + idx, midKey);
    }

};

template <typename Key>
class BTree {
private:
    shared_ptr<BTreeNode<Key>> root;
    const int t;

    void printHelper(const shared_ptr<BTreeNode<Key>>& node, int indent) const {
        if (!node) return;
        
        cout << string(indent, ' ');
        for (const auto& key : node->keys)
            cout << key << " ";
        cout << endl;

        if (!node->isLeaf) {
            for (const auto& child : node->children) {
                printHelper(child, indent + 4);
            }
        }
    }

public:
    BTree(int _t) : t(_t) {
        if (t < 2) throw invalid_argument("Minimum degree must be at least 2");
    }

    void insert(const Key& k) {
        try {
            if (!root) {
                root = make_shared<BTreeNode<Key>>(t, true);
                root->keys.push_back(k);
                return;
            }

            // Handle full root
            if (root->keys.size() == 2*t-1) {
                auto newRoot = make_shared<BTreeNode<Key>>(t, false);
                newRoot->children.push_back(root);
                newRoot->splitChild(0);

                // Decide which child to insert into
                int idx = 0;
                if (newRoot->keys[0] < k) {
                    idx = 1;
                }
                newRoot->children[idx]->insertNonFull(k);

                root = newRoot;
            } else {
                root->insertNonFull(k);
            }
        } catch (const exception& e) {
            cerr << "Error during insertion: " << e.what() << endl;
            throw;
        }
    }

    void print() const {
        printHelper(root, 0);
    }
};

int main() {
    try {
        BTree<int> btree(3);  // Minimum degree 3

        // Test sequences
        vector<vector<int>> testSequences = {
            {10, 20, 5, 6, 12, 30, 7, 17},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            {50, 40, 30, 20, 10, 5, 1},
            {5, 5, 5, 5, 5}  // Test duplicates
        };

        for (size_t i = 0; i < testSequences.size(); i++) {
            cout << "\nTest sequence " << i+1 << ":\n";
            BTree<int>(3);  // Fresh tree for each sequence
            
            for (int key : testSequences[i]) {
                cout << "Inserting " << key << endl;
                btree.insert(key);
                btree.print();
                cout << "-----\n";
            }
        }

    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
