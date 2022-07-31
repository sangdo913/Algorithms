from collections import deque
n, m = map(int, input().split())

dr = (-1,0,1,0)
dc = (0,1,0,-1)

arr = [input().strip() for _ in range(n)]
chk = [[0]*m for _ in range(n)]

def isIn(r,c):
    return 0 <= r < n and 0 <= c < m

def addCross(arr, chk, r,c):
    match = True
    len = 0
    nr = [r,r,r,r]
    nc = [c,c,c,c]
    while match: 
        for d in range(4):
            nr[d] += dr[d]
            nc[d] += dc[d]
            
            if not isIn(nr[d], nc[d]) or arr[nr[d]][nc[d]] == '.':
                match = False
                break
        if match: len+=1
            
    if len > 0:
        chk[r][c] = 1
        for d in range(4):
            for i in range(len):
                nr = r + (i+1)*dr[d]
                nc = c + (i+1)*dc[d]
                chk[nr][nc] = 1
    return len

def canMake(arr, chk):
    for i in range(n):
        for j in range(m):
            if arr[i][j] == '*' and chk[i][j] == 0:
                return False
    return True

res = []
for i in range(n):
    for j in range(m):
        if arr[i][j] == '*':
            ret = addCross(arr,chk, i,j)
            if ret > 0: 
                res.append((i+1,j+1, ret))

if canMake(arr, chk):
    print(len(res))
    for x, y, s in res:
        print(x, y, s)
else: print(-1)