from collections import deque
n, q = tuple(map(int,input().split()))
arr = [list(map(int, input().split())) for _ in range(1<<n)]
queries = list(map(int,input().split()))

dr = (-1,0,1,0)
dc = (0,1,0,-1)

def rotate(n, arr, r,c, num):
    l = 1<<n

    while num:
        num-=1
        temp = [[arr[r+l-1-j][c+i] for j in range(l)] for i in range(l)]
        for i in range(l):
            arr[r+i][c:c+l] = temp[i][:]

def simulate(arr):
    ret = 0
    l = len(arr)
    update = []
    
    for i in range(l):
        for j in range(l):
            if arr[i][j] == 0: continue
            nonzero = 0
            for d in range(4):
                ni,nj = i + dr[d], j + dc[d]
                if(ni < 0 or nj < 0 or ni == l or nj == l): continue
                if(arr[ni][nj] == 0) : continue
                nonzero += 1

            if nonzero < 3: 
                update.append((i,j))
            ret += arr[i][j]

    for i,j in update:
        arr[i][j] -=1

    return ret - len(update)

def bfs(arr, i, j, visit):
    l = len(arr)
    dq = deque()
    
    ret = 0
    dq.append((i,j))
    visit[i][j] = 1
    while dq:
        ret+=1
        i,j = dq.popleft()
        for d in range(4):
            ni, nj = i + dr[d], j + dc[d]
            if(ni < 0 or  nj < 0 or ni == l or nj == l): continue
            if arr[ni][nj] == 0: continue
            if visit[ni][nj]: continue
            visit[ni][nj] = 1
            dq.append((ni,nj))
    return ret

l = 1<<n
num = 0
tc = 0
visit = [[0]*l for _ in range(l)]
for q in queries:
    tc+=1
    for i in range(0,l,1<<q):
        for j in range(0,l,1<<q):
            rotate(q, arr, i, j, 1)
    num = simulate(arr)

maxice = 0

for (i,j) in ((i,j) for i in range(l) for j in range(l)):
    if visit[i][j] != tc and arr[i][j]:
        ice = bfs(arr,i,j,visit)
        maxice = max(ice,maxice)

print(num)
print(maxice)