import sys
sys.setrecursionlimit(1000)

n = int(input())
stair = []

for num in range(n):
    stair.append(int(input()))

# 1. Top Down
cache = [[-1]*n for _ in range(3)]

def score_memoization(n, step):
    if n < 0: return 0
    if cache[step][n] != -1: return cache[step][n]
    cache[step][n] = stair[n] + max(score_memoization(n-1, 1) if step == 2 else -0x3f3f3f3f, score_memoization(n-2, 2))
    return cache[step][n]

print(score_memoization(n-1, 2))

# 2. Bottom Up
score = [[0]*n for _ in range(3)]
score[1][0] = stair[0]
score[2][0] = -0x3f3f3f3f

if n > 1:
    score[2][1] = stair[1]
    score[1][1] = stair[0] + stair[1]

for i in range(2, n):
    score[1][i] = stair[i] + score[2][i-1]
    score[2][i] = stair[i] + max(score[1][i-2], score[2][i-2])
print(score)
print(max(score[1][n-1], score[2][-1]))