//Record Keeping
//https://www.acmicpc.net/problem/9872
    #include<iostream>
    #include<map>
    #include<string>
    #include<algorithm>
    #include<vector>
    #include<map>

    using namespace std;

    map<string, int> se;

    int MAX(int a, int b){return a < b ? b : a;}

    int Do(){
        int n, ans = 0;
        cin >> n;

        while(n--){
            string in[3];
            cin >> in[0] >> in[1] >> in[2];
            vector<string> ve;
            
            ve.push_back(in[0]); ve.push_back(in[1]), ve.push_back(in[2]);
            sort(ve.begin(), ve.end());

            int num;
            in[0] = ve[0] +' '+ ve[1]+' ' + ve[2];

            if(se.find(in[0]) == se.end()){
                se.insert({in[0], 1});
                num = 1;
            } 
            else {
                num = ++se.find(in[0])->second;
            }
            ans = MAX(ans, num);
        }

        cout << ans;
        return 0;
    }