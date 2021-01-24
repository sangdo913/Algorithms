def solution(l):
    dp = [[1]*len(l) , [0]*len(l) , [0]*len(l)]
    for i in range(1, 3):
        for id,n in enumerate(l):
            for j in range(id):
                if not n%l[j]:
                    dp[i][id] += dp[i-1][j]
    return sum(dp[2])
    # Your code here


r = solution([1, 1, 1])
print(r)