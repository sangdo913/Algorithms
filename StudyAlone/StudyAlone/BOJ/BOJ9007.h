#include<iostream>

using namespace std;
int arr[4][1000];
int merge[2][1000000];
int temp[1000000];
#define abs(a) ((a) > 0 ? (a) : -(a))
#define min(a,b) ((a) > (b) ? (b) : (a))

void mer(int *arr, int l, int r) {
    int s = l, m = (l+r)/2, e = m;
    int k = l;

    while(s < m && e < r) {
        if(arr[s] < arr[e]) temp[k++] =  arr[s++];
        else temp[k++] = arr[e++];
    }
    while(s <m) temp[k++] = arr[s++];
    while(e < r) temp[k++] = arr[e++];

    for(int i = l; i < e; ++i) {
        arr[i] = temp[i];
    }
}

void mergesort(int *arr, int l, int r) {
    if(l+1 == r) {
        return;
    }
    int m = (l+r)/2;
    mergesort(arr, l,m);
    mergesort(arr, m,r);
    mer(arr, l,r);
}

/*
int s =0;
int e = arr.size();
[)

bool parametric(parameter, condition) {
    bool ret = false;;

    ...

    return ret;
}

while(s < e) {
    int m = (s+e)/2;

    if(parametric(......)) {
        s = m+1;
    }
    else {
        e = m;
    }

}

while()
*/

bool parametric(int a,int b, int k) {
    return a + b < k;
}

int binary_search(int n, int k) {
        int s = 0;
        int e = n*n-1;
        int v = 0x3f3f3f3f;
        int answer = -1;
        //n^2 (log n)
        for(int i = 0; i < n*n; ++i) {
            int a = merge[0][i];
            int s = 0;
            int e = n*n-1;

            while(s < e) {
                int m = (s+e)/2;
                //ture
                //a + b = k -> upper bound
                if(parametric(a,merge[1][m],k)) {
                    s = m + 1;
                }
                //false
                else e = m;
            }
////////////////////////////////////////////

            if(s > 0) {
                if(v >= abs(a + merge[1][s-1] - k)) {
                    v = abs(a+merge[1][s-1] - k);
                    answer = a + merge[1][s-1];
                }
            }
            if(v > abs(a+merge[1][s] - k)) {
                v = abs(a+merge[1][s] - k);
                answer = a + merge[1][s];
            }
        }
        return answer;
}

int two_pointer(int n, int k) {
    int s = 0;
    int e = n*n-1;
    int v = 0x3f3f3f3f;
    int answer = 0x3f3f3f3f;
    while(s < n*n && e >= 0) {
        int sum = merge[0][s] + merge[1][e];
        if(abs(sum-k) < v) {
            v = abs(sum-k);
            answer = sum;
        }
        else if(abs(sum-k) == v) {
            answer = min(answer, sum);
        }
        if(sum < k) ++s;
        else --e;
    }
    return answer;
}

int main() {
    freopen("0Text.txt", "r",stdin);
    int t,n,k;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cin >> k >> n;
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < n; ++j) {
                cin >> arr[i][j];
            }
        }

        for(int l = 0; l < 2; ++l) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    merge[l][i*n+j] = arr[l*2][i]+arr[l*2+1][j];
                }
            }
        }
        mergesort(merge[0], 0, n*n);
        mergesort(merge[1], 0, n*n);
        cout << two_pointer(n,k) << endl;
    }
    
    return 0;
}