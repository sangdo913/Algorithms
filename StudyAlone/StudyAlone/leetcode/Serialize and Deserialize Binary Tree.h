#include<iostream>
#include<vector>
#include<string>
using namespace std;

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

/**
 * Definition for a binary tree node.
* struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#define LSFT(x,cur,a) (((unsigned int)((x)[cur]) << (a)))
vector<TreeNode> nodes(10000, TreeNode(0));
int nid = 0;

TreeNode* mydeserialize(string &data, int &i) {
    TreeNode *nn = &nodes[nid++];
    nn->val = LSFT(data,i+3, 24) | LSFT(data,i+2,16) | LSFT(data, i+1, 8) | data[i]&0xff; 
    i+=4;
    char next = data[i++];
    if(next == 'a' || next == 'l') nn->left = mydeserialize(data,i);
    else nn->left = 0;
    if(next == 'a' || next == 'r') nn->right = mydeserialize(data, i);
    else nn->right = 0;
    return nn;
}

void myserialize(string &ret, TreeNode* root) {
    if(!root) return;
    int i = root->val;
    ret.push_back(i &0xff);
    ret.push_back((i>>8) & 0xff);
    ret.push_back((i>>16) & 0xff);
    ret.push_back((i >> 24) & 0xff);
    
    if(root->right && root->left) ret.push_back('a');
    else if(!root->right && !root->left) ret.push_back('n');
    else if(root->left) ret.push_back('l');
    else ret.push_back('r');
    if(root->left) myserialize(ret, root->left);
    if(root->right) myserialize(ret, root->right);
}

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string str("");
        str.reserve(10000);
        myserialize(str, root);
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "") return 0;
        nid= 0;
        int cur =0;
        return mydeserialize(data,cur);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));