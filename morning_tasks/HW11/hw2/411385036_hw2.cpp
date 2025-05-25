#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int val) {
        root = insertHelper(root, val);
    }

    TreeNode* search(int val) {
        return searchHelper(root, val);
    }

private:
    TreeNode* root;

    TreeNode* insertHelper(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }

        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        }

        return node;
    }

    TreeNode* searchHelper(TreeNode* node, int val) {
        if (node == nullptr || node->val == val) {
            return node;
        }

        if (val < node->val) {
            return searchHelper(node->left, val);
        } else {
            return searchHelper(node->right, val);
        }
    }
};

int main() {
    BinarySearchTree bst;

    cout << "Enter numbers: ";
    string input;
    getline(cin, input);

    istringstream iss(input);
    int num;
    while (iss >> num) {
        bst.insert(num);
    }

    while (true) {
        cout << "Enter the number you want: ";
        int searchNum;
        cin >> searchNum;
        if (searchNum == -1) {
            break;
        }

        TreeNode* result = bst.search(searchNum);
        if (result != nullptr) {
            cout << "Left: " << (result->left ? to_string(result->left->val) : "null")
                 << " Right: " << (result->right ? to_string(result->right->val) : "null") << endl;
        } else {
            cout << "The value is not in this binary search tree." << endl;
        }
    }

    return 0;
}