//https://leetcode.com/problems/perfect-rectangle/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        vector<int> range;
        
        int n = rectangles.size();
        vector<int> X(n*2); 
        
        for(int i = 0; i < n; i++){
            X[2*i] = rectangles[i][0];
            X[2*i+1] = rectangles[i][2];
        }
        sort(X.begin(), X.end());
        X.resize(unique(X.begin(), X.end())- X.begin());
        int m = X.size();
        vector<vector<pair<int,int>>> lines[2];
        lines[0].resize(m);
        lines[1].resize(m);
        range.resize(X.back()-X[0]+1);
        for(int i = 0; i < X.size(); ++i){
            range[X[i]-X[0]] = i;
        }
        
        for(int i = 0; i < n; ++i){
            pair<int,int> l = {rectangles[i][1], rectangles[i][3]};
            int idx = range[rectangles[i][0]-X[0]];
            lines[0][idx].push_back(l);
            
            idx = range[rectangles[i][2]-X[0]];
            lines[1][idx].push_back(l);
        }
        vector<vector<pair<int,int>>> line2[2];
        line2[0].resize(m);
        line2[1].resize(m);
        for(int i = 0; i < m; ++i){
            sort(lines[0][i].begin(), lines[0][i].end());
            sort(lines[1][i].begin(), lines[1][i].end());
            int j = 0;
            while(j < lines[0][i].size()){
                pair<int, int> l = lines[0][i][j++];
                while(j < lines[0][i].size() && lines[0][i][j].first == l.second) {
                    l.second = lines[0][i][j].second;
                    ++j;
                }
                line2[0][i].push_back(l);
            }
            j = 0; 
            while(j < lines[1][i].size()){
                pair<int, int> l = lines[1][i][j++];
                while(j < lines[1][i].size() && lines[1][i][j].first == l.second) {
                    l.second = lines[1][i][j].second;
                    ++j;
                }
                line2[1][i].push_back(l);
            }
        }
        if(line2[0][0].size()!= 1) return false;
        if(line2[1][m-1].size()!= 1) return false;
        if(line2[0][0][0] != line2[1][m-1][0]) return false;
        
        for(int i = 1; i < m-1; ++i){
            if(line2[0][i].size() != line2[1][i].size()) {
                return false;
            }
            for(int j = 0; j < line2[0][i].size(); ++j){
                if(line2[0][i][j] != line2[1][i][j]) {
                    return false;
                }
            }
        }
        
        return true;
    }
};