//
//  main.cpp
//  Assignment 7
//
//  Created by Kevin Chavez on 4/09/25.
//

#include <iostream>

// BST Node structure
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Function to insert a value into BST
TreeNode* InsertBST(int x, TreeNode* T) {
    if (T == nullptr) {
        return new TreeNode(x);
    }
    
    if (x < T->val) {
        T->left = InsertBST(x, T->left);
    } else if (x > T->val) {
        T->right = InsertBST(x, T->right);
    }
    // If x == T->val, we don't insert duplicates
    
    return T;
}

// Helper function to find the minimum value node in a subtree
TreeNode* findMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Function to delete a value from BST
TreeNode* DeleteBST(int x, TreeNode* T) {
    if (T == nullptr) {
        return nullptr;
    }
    
    if (x < T->val) {
        T->left = DeleteBST(x, T->left);
    } else if (x > T->val) {
        T->right = DeleteBST(x, T->right);
    } else {
        // Node to delete found
        
        // Case 1: Node with only one child or no child
        if (T->left == nullptr) {
            TreeNode* temp = T->right;
            delete T;
            return temp;
        } else if (T->right == nullptr) {
            TreeNode* temp = T->left;
            delete T;
            return temp;
        }
        
        // Case 2: Node with two children
        // Get the inorder successor (smallest in the right subtree)
        TreeNode* temp = findMin(T->right);
        
        // Copy the inorder successor's content to this node
        T->val = temp->val;
        
        // Delete the inorder successor
        T->right = DeleteBST(temp->val, T->right);
    }
    return T;
}

// Utility function to print BST in-order
void inOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->val << " ";
        inOrderTraversal(root->right);
    }
}

// Utility function to visualize BST structure
void printBST(TreeNode* root, int space = 0, int height = 10) {
    if (root == nullptr) return;
    
    space += height;
    printBST(root->right, space);
    std::cout << std::endl;
    for (int i = height; i < space; i++) std::cout << ' ';
    std::cout << root->val << std::endl;
    printBST(root->left, space);
}

int main() {
    TreeNode* root = nullptr;
    
    // Insert values into BST
    std::cout << "Inserting values: 50, 30, 70, 20, 40, 60, 80\n";
    root = InsertBST(50, root);
    root = InsertBST(30, root);
    root = InsertBST(70, root);
    root = InsertBST(20, root);
    root = InsertBST(40, root);
    root = InsertBST(60, root);
    root = InsertBST(80, root);
    
    // Print BST in-order
    std::cout << "In-order traversal: ";
    inOrderTraversal(root);
    std::cout << "\n\nBST structure:\n";
    printBST(root);
    
    // Delete a leaf node (20)
    std::cout << "\nDeleting 20 (leaf node)\n";
    root = DeleteBST(20, root);
    std::cout << "In-order traversal after deletion: ";
    inOrderTraversal(root);
    std::cout << "\n\nBST structure after deletion:\n";
    printBST(root);
    
    // Delete a node with one child (30)
    std::cout << "\nDeleting 30 (node with one child)\n";
    root = DeleteBST(30, root);
    std::cout << "In-order traversal after deletion: ";
    inOrderTraversal(root);
    std::cout << "\n\nBST structure after deletion:\n";
    printBST(root);
    
    // Delete a node with two children (50)
    std::cout << "\nDeleting 50 (node with two children)\n";
    root = DeleteBST(50, root);
    std::cout << "In-order traversal after deletion: ";
    inOrderTraversal(root);
    std::cout << "\n\nBST structure after deletion:\n";
    printBST(root);
    
    return 0;
}
