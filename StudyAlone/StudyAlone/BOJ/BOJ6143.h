#include<iostream>

using namespace std;

char mystr[30001];
int myorder[30001];
char res[30001];
int n;

int makeorder(int l, int r, int p) {
    if(l > r) return -1;
    char ret = 0;
    if(mystr[l] < mystr[r]){
        myorder[l] = p;
        return -1;
    }
    else if(mystr[l] > mystr[r]){
        myorder[r] = p;
        return 1;
    }
    else{
        ret = makeorder(l+1,r-1, p); 
        if(ret == 1){
            myorder[r] =p;
        }
        else myorder[l] = p;
        return ret;
    }
    return -100;
}

int main(){
    freopen("0Text.txt","r",stdin);
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> mystr[i];

    int l = 0, r = n-1;
    int rlen = 0;
    int p = 0;
    while(l <= r){
        if(mystr[l] < mystr[r]) res[rlen++] = mystr[l++];
        else if(mystr[l] > mystr[r]) res[rlen++] = mystr[r--];
        else {
            makeorder(l,r,++p);
            if(myorder[l] < myorder[r]) res[rlen++] = mystr[r--];
            else res[rlen++] = mystr[l++];
        }
    }
    for(int i = 0; i < n;){
        int cnt = 80;
        while(i < n && cnt--){
            cout << res[i++];
        }
        cout << endl;
    }
    return 0;
}