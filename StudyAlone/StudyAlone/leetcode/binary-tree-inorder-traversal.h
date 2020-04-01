#include<iostream>
#include<vector>

using namespace std;

// * Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

vector<int> res;

void inorder(TreeNode* node){
    if(node->left){ inorder(node->left); }
    res.push_back(node->val);
    if(node->right) inorder(node->right);
}

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(!root) return vector<int>();
        res.clear();
        inorder(root);
        return res;
    }
};