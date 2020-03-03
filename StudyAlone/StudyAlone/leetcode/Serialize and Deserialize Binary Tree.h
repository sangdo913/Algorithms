#include<iostream>
#include<string>
using namespace std;

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
string tostr(int i){
    string s; 
    s.resize(4);
    s[0] = i &0xff;
    s[1] = (i>>8) & 0xff;
    s[2] = (i>>16) & 0xff;
    s[3] = (i >> 24) & 0xff;
    return s;
}

#define LSFT(x,a) (((unsigned int)(x) << (a)))
int toint(string a){
    return (a[3]&0xff)  | LSFT(a[2], 8) | LSFT(a[1], 16) | LSFT(a[0],24); 
}

TreeNode* mydeserialize(string &data) {
    int val = toint(string(data.rbegin(), data.rbegin()+4));
    TreeNode *nn = new TreeNode(val);
    data.pop_back();
    data.pop_back();
    data.pop_back();
    data.pop_back();
    char next = data.back();
    data.pop_back();
    if(next == 'a' || next == 'l'){nn->left = mydeserialize(data); }
    if(next == 'a' || next == 'r') nn->right = mydeserialize(data);
    return nn;
}

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return string();
        string ret = "";
        if(root->right) ret += serialize(root->right); 
        if(root->left) ret += serialize(root->left);
        if(root->right && root->left) ret +=string("a");
        else if(!root->right && !root->left) ret += string("n");
        else if(root->left) ret += string("l");
        else ret += string("r");
        ret += tostr(root->val);
        
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "") return 0;
        return mydeserialize(data);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));