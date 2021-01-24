def getdp(dp,n,r):
    if len(dp[n][r]): return dp[n][r]
    if n == r:
        dp[n][r] = [[i] for i in range(n)]
        return dp[n][r]
    elif r == 1:
        dp[n][r] = [[0] for _ in range(n)]
        return dp[n][r]
    base,remain = getdp(dp,n-1,r), getdp(dp, n-1, r-1)
    height = max(max(base))
    dp[n][r].append([i for i in range(height+1)])
    for row in base:
        dp[n][r].append([i for i in row])
    for i in range(len(remain)):
        nextrow = [k for k in remain[i]]
        for j in range(len(nextrow)):
            nextrow[j] += height+1
        dp[n][r][i+1] += nextrow
    return dp[n][r]
    
def solution(num_buns, num_required):
    if not num_required: return [[] for _ in range(num_buns)]
    dp = [[[] for _ in range(num_required+1)] for _ in range(num_buns + 1)]
    return getdp(dp, num_buns, num_required)

print(solution(5,3))