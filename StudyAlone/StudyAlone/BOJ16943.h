#include<iostream>
#include<vector> 
#include<algorithm>

using namespace std;

int len, a, b;
int nums[10], in;
int until[10];
vector<int> li;
void dfs(int depth, int num, bool issame){
    if(depth == len){
        li.push_back(num);
        return;
    }

    int imax = issame ? until[depth]+1 : 10;
    for(int i = depth ==0;i < imax; i++){
        if(nums[i]){
            nums[i]--;
            num*=10; num+=i;
            dfs(depth+1, num, issame && (i == until[depth]));
            num/=10;
            nums[i]++;
        }
    }
}

int getlen(int n){
    int res = 0;
    while(n){
        res++;
        n/=10;
    }
    return res;
}

int Do(){
    cin >> a >> b;

    while(a){
        nums[a%10]++;
        a/=10;
        len++;
    }
    int temp = b;
    for(int i = 0; i < len;i++){
        until[len-1-i] = temp%10;
        temp/=10;
    }
    dfs(0,0, false);
    
    li.push_back(-1);
    sort(li.begin(), li.end());
    auto fi = lower_bound(li.begin(), li.end(), b);
    cout << *(--fi);
    return 0;
}