#include<iostream>
#include<queue>

using namespace std;
priority_queue<int> pq;

int arr[20000];
int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    long long res = 0;
    while(n--){
        int x;
        cin >> x;
        pq.push(-x);
        res -= x;
    }
    while(pq.size() > 1){
        int n1 = -pq.top(); pq.pop();
        int n2 = -pq.top(); pq.pop();

        res += n1 + n2;
        pq.push(-(n1+n2));
    }
    cout << res - pq.top();
    return 0; 
}