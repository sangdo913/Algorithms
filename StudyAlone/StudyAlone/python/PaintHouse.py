li = [[17,2,17], [16,16,5], [14,3,19]]

class Solution:

    def minCost(self, costs):
        dp = [[0x3f3f3f3f for i in range(len(costs))] for i in range(3)]
        dp[0][0] = costs[0][0]
        dp[1][0] = costs[0][1]
        dp[2][0] = costs[0][2]
        for j in range(1, len(costs)):
            for i in range(3):
                for k in range(3):
                    if i == k: continue
                    dp[i][j] = min(dp[k][j-1] + costs[j][i], dp[i][j])
                
        m = len(costs)-1
        return min(dp[0][m], dp[1][m], dp[2][m])

print(Solution().minCost(li))