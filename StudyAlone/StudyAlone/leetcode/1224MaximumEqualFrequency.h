#include<vector>
#include<iostream>
using namespace std;

#define rint register int

int cntcnt[100001];

int cnt[100001];
int maxcount;

class Solution {
public:
	int maxEqualFreq(vector<int>& nums) {
		for (rint i = 1; i <= 100000; ++i) cnt[i] = 0;
		maxcount = 1;
		int maxcountidx;
		for (int i = 0; i <= nums.size(); ++i) cntcnt[i] = 0;
		
		cnt[nums[0]]++;
		cntcnt[1] = 1;

		for (rint i = 1; i < nums.size(); ++i) {
			if(cnt[nums[i]]) cntcnt[cnt[nums[i]]]--;
			cnt[nums[i]]++;
			cntcnt[cnt[nums[i]]]++;
			if (maxcount < cnt[nums[i]]) {
				maxcount = cnt[nums[i]];
			}
			if (cntcnt[1]) {
				cntcnt[1]--;
				if (cntcnt[maxcount] * maxcount == i) maxcountidx = i+1;
				cntcnt[1]++;
			}
			if (cntcnt[maxcount] == 1 && (cntcnt[maxcount - 1]+1) * (maxcount-1) == i) maxcountidx = i+1;
		}
		return maxcountidx;
	}
};

int main() {
	int n,a ;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; ++i) cin >> nums[i];
	cout << Solution().maxEqualFreq(nums) << endl;
	return 0;
}