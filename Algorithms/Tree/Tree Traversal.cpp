#include <iostream>

// Definition of a TreeNode
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Class representing a Binary Tree
class BinaryTree {
private:
    TreeNode* root;

    // Utility function for inorder traversal
    void inorderUtil(TreeNode* root) {
        if (root != nullptr) {
            inorderUtil(root->left);
            std::cout << root->val << " ";
            inorderUtil(root->right);
        }
    }

    // Utility function for preorder traversal
    void preorderUtil(TreeNode* root) {
        if (root != nullptr) {
            std::cout << root->val << " ";
            preorderUtil(root->left);
            preorderUtil(root->right);
        }
    }

    // Utility function for postorder traversal
    void postorderUtil(TreeNode* root) {
        if (root != nullptr) {
            postorderUtil(root->left);
            postorderUtil(root->right);
            std::cout << root->val << " ";
        }
    }

public:
    // Constructor
    BinaryTree() : root(nullptr) {}

    // Function to perform inorder traversal
    void inorderTraversal() {
        inorderUtil(root);
    }

    // Function to perform preorder traversal
    void preorderTraversal() {
        preorderUtil(root);
    }

    // Function to perform postorder traversal
    void postorderTraversal() {
        postorderUtil(root);
    }

    // Function to get the root of the tree
    TreeNode* getRoot() {
        return root;
    }

    // Function to set the root of the tree
    void setRoot(TreeNode* node) {
        root = node;
    }
};

int main() {
    BinaryTree tree;

    // Constructing a sample binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    tree.setRoot(root);

    std::cout << "Inorder traversal: ";
    tree.inorderTraversal();
    std::cout << std::endl;

    std::cout << "Preorder traversal: ";
    tree.preorderTraversal();
    std::cout << std::endl;

    std::cout << "Postorder traversal: ";
    tree.postorderTraversal();
    std::cout << std::endl;

    return 0;
}
