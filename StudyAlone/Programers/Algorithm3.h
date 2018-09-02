#include <iostream>
#include<vector>
using namespace std;

vector<vector<int> > solution(int n, vector<vector<int> > signs)
{
    //�÷��̵�-�ͼ�
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                signs[i][j] |= signs[i][k] && signs[k][j];
            }
        }
    }
    
    return signs;
}