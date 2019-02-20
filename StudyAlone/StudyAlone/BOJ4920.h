#include<iostream>
#include<cstring>

using namespace std;

int table[13][4][2]={
    {{0,0},{1,0},{2,0},{3,0}},
    {{0,0},{0,1},{0,2},{0,3}},
    ///ÀÏÀÚ
    {{0,0},{0,1},{1,1},{1,2}},
    {{1,0},{0,1},{1,1},{2,0}},
    //Z
    {{0,0},{0,1},{0,2},{1,2}},
    {{0,1},{1,1},{2,1},{2,0}},
    {{0,0},{1,0},{1,1},{1,2}},
    {{0,0},{0,1},{1,0},{2,0}},
    //¤¡
    {{0,0},{0,1},{0,2},{1,1}},
    {{0,1},{1,1},{1,0},{2,1}},
    {{0,1},{1,1},{1,0},{1,2}},
    {{0,0},{1,0},{2,0},{1,1}},

    {{0,0},{1,0},{1,1},{0,1}},
    //¤±
};
int arr[200][200];

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    
    int n;
    int tc = 1;
    cin >> n;
    while(n){
        for(int i = 0;i < n; i++){
            for(int j = 0;j < n; j++){
                cin >> arr[i][j]; 
            }
        }

        int res = -0x3f3f3f3f;
        
        for(int i = 0; i < n; i++){
            for(int j = 0;j < n; j++){
                for(int b = 0; b < 13; b++){
                    int temp = 0;
                    for(int id = 0; id < 4; id++){
                        int r = i + table[b][id][0];
                        int c = j + table[b][id][1];

                        if(r >= n || c >= n){
                            temp = -0x3f3f3f3f; break;
                        }

                        temp += arr[r][c];
                    }
                    res = res > temp ? res : temp;
                }
            }
        }
        cout << tc++ << ". " << res << '\n';
        cin >> n;
    }
    return 0;
}