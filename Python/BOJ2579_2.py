n = int(input())
stair = []

def getScore(n):
    return max(getScore(n-2) + stair[n], getScore(n-1), stair[n-1])

for i in range(n):
    stair.append(int(input()))

score = [0]*n
score[0] = stair[0]

if n > 1:
    score[1] = stair[1]

if n > 2:
    score[2] = stair[0] + stair[2]

for i in range(3, n):
    score[i] = max(score[i-3] + stair[i-2] + stair[i], score[i-2] + stair[i])

if n > 1:
    score[-1] = max(score[-1], score[-2] + stair[-1])
print(score[-1])