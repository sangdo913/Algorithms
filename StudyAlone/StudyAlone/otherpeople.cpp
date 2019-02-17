#include <iostream>
#include <tuple>
#include <cstring>
#include <vector>
#include <string>
#include <queue>
using namespace std;
int dist[1000][1000];
bool check[1000][1000][4];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int main() {
    int n, m, len;
    cin >> n >> m >> len;
    vector<string> a(n);
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }
    int x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1 -= 1; y1 -= 1; x2 -= 1; y2-= 1;
    memset(dist,-1,sizeof(dist));
    queue<pair<int,int>> q;
    dist[x1][y1] = 0;
    q.push(make_pair(x1,y1));
    while (!q.empty()) {
        int x, y;
        tie(x, y) = q.front(); q.pop();
        for (int k=0; k<4; k++) {
            for (int l=1; l<=len; l++) {
                int nx = x+dx[k]*l;
                int ny = y+dy[k]*l;
                
                if (0 <= nx && nx < n && 0 <= ny && ny < m) {
                    if (a[nx][ny] =='#') break;
                    if (check[nx][ny][k]) continue;
                    check[nx][ny][k] = true;
                    if (dist[nx][ny] == -1 || dist[nx][ny] > dist[x][y]) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.push(make_pair(nx,ny));
                    }
                } else {
                    break;
                }
            }
        }
    }
    cout << dist[x2][y2] << '\n';
    return 0;
}