
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 

int pa[101];
int depth[101];

void makenode(int pi, TreeNode *p, int k){
    pa[p->val]= pi;
    depth[p->val] = k;
    if(p->left) makenode(p->val, p->left, k+1);
    if(p->right) makenode(p->val, p->right, k+1);
}

class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        makenode(-1, root, 0);
        return pa[x] != pa[y] && depth[x] == depth[y];
    }
};