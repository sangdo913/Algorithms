#include<iostream>
#include<vector>
using namespace std;
struct NODE{
    int idx;
    NODE *l, *r;
    NODE *p;
    NODE *n, *m;
};
vector<NODE> vec;
vector<bool> check1;
vector<bool> check2;
int nid = 0;

NODE* getTree(vector<int>&v, int l, int r){
    if(l > r) return 0;
    
    NODE& node = vec[nid++];
    node.idx = l;
    
    for(int i = l+1; i <= r; ++i){
        if(v[node.idx] < v[i]){
            node.idx = i;
        }
    }
    node.l = getTree(v, l, node.idx - 1);
    if(node.l) node.l->p = &node;
    node.r = getTree(v, node.idx+1, r);
    if(node.r) node.r->p = &node;
    return &node;
}

void print(NODE* root){
    if(!root) return;
    cout << root->idx;
    print(root->l);
    print(root->r);
}

NODE* getnext(NODE* node, vector<bool>& check){
    while(true){
        if(!node) return 0;
        if(!check[node->idx]){
            return node;
        }
        if(node->r && !check[node->r->idx]) node = node->r;
        else if(node->l && !check[node->l->idx]) node = node->l;
        else node = node->p;
    }
}

bool isbig(vector<int>&v1, vector<int>&v2){
    for(int i = 0; i < v1.size(); ++i){
        if(v1[i] < v2[i]) return true;
        else if(v1[i] > v2[i]) return false;
    }
    return false;
}
void vecprint(vector<int> &vec){
    for(auto it : vec){
        cout <<it << ' ' ;
    }
    cout << endl;
}
bool cmp(vector<int> &v1, vector<int>&v2, int i, int j){
    while(i < v1.size() && j < v2.size() && v1[i] == v2[j]){
        ++i, ++j;
    }
    if(i == v1.size()) return true;
    if(j == v2.size()) return false;
    return v1[i] < v2[j];
}
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        nid= 0;
        check1.clear(); check2.clear(); check1.resize(nums1.size()), check2.resize(nums2.size());
        vec.clear(); vec.resize(nums1.size() + nums2.size());
        
        NODE* r1 = getTree(nums1, 0, nums1.size()-1);
        NODE* r2 = getTree(nums2, 0, nums2.size()-1);
        vector<vector<int>> n1(nums1.size() > k ? k+1 : nums1.size()+1);
        vector<vector<int>> n2(nums2.size() > k ? k+1 : nums2.size()+1);
        for(int i = 1; i < n1.size() && i <= k; ++i){
            check1[r1->idx] = 1;
            r1 = getnext(r1,check1);
            for(int j = 0; j < nums1.size(); ++j){
                if(check1[j]) n1[i].push_back(nums1[j]);
            }
        }
        for(int i = 1; i < n2.size() && i <= k; ++i){
            check2[r2->idx] = 1;
            r2 = getnext(r2,check2);
            for(int j = 0; j < nums2.size(); ++j){
                if(check2[j]) n2[i].push_back(nums2[j]);
            }
        }
        int st = n2.size()-1 > k ? 0 : k - n2.size()+1;
        int ed = n1.size();
        
        vector<int> res(k);
        vector<int> temp(k);
        
        for(int i = st; i < ed; ++i){
            int l = 0, r= 0;
            int n = 0;
            int i2 = k-i;
            while(l < i && r < k-i){
                temp[n++] = cmp(n1[i], n2[i2], l, r) ? n2[i2][r++] : n1[i][l++];
            }
            while(l <i) temp[n++] = n1[i][l++];
            while(r<i2) temp[n++] = n2[i2][r++];
            if(isbig(res, temp)) res = temp;
        }
        
        return res;
    }
};