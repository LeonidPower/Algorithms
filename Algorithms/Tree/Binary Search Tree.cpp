#include <iostream>

// Definition of a TreeNode
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Class representing a Binary Search Tree
class BST {
private:
    TreeNode* root;

    // Utility function to insert a value into the BST
    TreeNode* insertUtil(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }
        
        if (val < root->val) {
            root->left = insertUtil(root->left, val);
        } else {
            root->right = insertUtil(root->right, val);
        }
        
        return root;
    }
    
    // Utility function to find the minimum value node in a subtree
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Utility function to delete a value from the BST
    TreeNode* deleteUtil(TreeNode* root, int val) {
        if (root == nullptr) {
            return root;
        }
        
        if (val < root->val) {
            root->left = deleteUtil(root->left, val);
        } else if (val > root->val) {
            root->right = deleteUtil(root->right, val);
        } else {
            // Node with only one child or no child
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            TreeNode* temp = minValueNode(root->right);
            
            // Copy the inorder successor's content to this node
            root->val = temp->val;
            
            // Delete the inorder successor
            root->right = deleteUtil(root->right, temp->val);
        }
        return root;
    }

    // Utility function to search for a value in the BST
    bool searchUtil(TreeNode* root, int val) {
        if (root == nullptr) {
            return false;
        }
        
        if (val == root->val) {
            return true;
        } else if (val < root->val) {
            return searchUtil(root->left, val);
        } else {
            return searchUtil(root->right, val);
        }
    }

public:
    // Constructor
    BST() : root(nullptr) {}

    // Function to insert a value into the BST
    void insert(int val) {
        root = insertUtil(root, val);
    }
    
    // Function to delete a value from the BST
    void remove(int val) {
        root = deleteUtil(root, val);
    }
    
    // Function to search for a value in the BST
    bool search(int val) {
        return searchUtil(root, val);
    }
};

int main() {
    BST bst;

    // Inserting values into the BST
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    // Searching for a value in the BST
    std::cout << "Searching for 60: " << (bst.search(60) ? "Found" : "Not found") << std::endl;

    // Deleting a value from the BST
    bst.remove(20);

    // Searching for a value after deletion
    std::cout << "Searching for 20: " << (bst.search(20) ? "Found" : "Not found") << std::endl;

    return 0;
}
