#include<iostream>
#include<string>

using namespace std;


// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     TreeNode(): val(0), left(NULL), right(NULL){}
 };

enum RESULT  {NEED, NOTNEED, CAM};

int ans;
 int dfs(TreeNode *root){
     if(!root) return NOTNEED;
     int left = dfs(root->left);
     int right = dfs(root->right);
     if(left == NEED || right == NEED){
         ans++; 
         return CAM;
     }
     else if(left == CAM || right == CAM){
         return NOTNEED;
     }

     return NEED;
 }

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        ans = 0;
        if(dfs(root) == NEED) ++ans;
        return ans;
    }
};
TreeNode mynodes[1000];
int num;
int nid;

void maketc(TreeNode *root){
    string s("null");
    if(nid != num)cin >> s;
    root->left = root->right = 0;
    if(s == "0"){
        root->left = &mynodes[nid++];
    }

    if(nid != num)cin >> s;
    if(s == "0"){
        root->right = &mynodes[nid++];
    }
    if(root->left)maketc(root->left);
    if(root->right)maketc(root->right);
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> num;
    string s;
    cin >> s;
    nid = 0;
    if(s == "0"){
        maketc(&mynodes[nid++]);
    }
    cout << Solution().minCameraCover(&mynodes[0]);

    return 0;
}