//
//  main.cpp
//  Assignment 8
//
//  Created by Kevin Chavez on 04/12/25.
//

#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Helper function to find and return pointer to a node with given value
TreeNode* findNode(TreeNode* root, int value) {
    if (root == nullptr) return nullptr;
    if (root->data == value) return root;
    if (value < root->data) return findNode(root->left, value);
    return findNode(root->right, value);
}

// Left Rotation
int leftrotation(int nodeValue, TreeNode* root) {
    TreeNode* node = findNode(root, nodeValue);
    if (node == nullptr || node->right == nullptr) {
        cout << "Left rotation not possible at node " << nodeValue << endl;
        return root->data;
    }

    TreeNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    // This is a local rotation, so unless node is root, root remains the same
    if (node == root)
        root = newRoot;

    return root->data;
}

// Right Rotation
int Rightrotation(int nodeValue, TreeNode* root) {
    TreeNode* node = findNode(root, nodeValue);
    if (node == nullptr || node->left == nullptr) {
        cout << "Right rotation not possible at node " << nodeValue << endl;
        return root->data;
    }

    TreeNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    // This is a local rotation, so unless node is root, root remains the same
    if (node == root)
        root = newRoot;

    return root->data;
}

int main() {
    TreeNode* root = new TreeNode(30);
    root->right = new TreeNode(40);

    cout << "Before Left Rotation, Root: " << root->data << endl;
    int newRootVal = leftrotation(30, root);
    cout << "After Left Rotation, New Root Value: " << newRootVal << endl;

    return 0;
}

