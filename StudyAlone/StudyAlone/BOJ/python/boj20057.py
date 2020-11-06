from collections import deque
n = int(input())
arr = [list(map(int, input().split())) for _ in range(n)]

pos = [(2,0),(1,-1),(1,1),(0,-2),(0,-1),(0,1),(0,2),(-1,-1),(-1,1),(1,0)]
ratio = [0.05, 0.1,0.1, 0.02, 0.07, 0.07, 0.02, 0.01,0.01]
dr = (-1,0,1,0)
dc = (0,-1,0,1)

dq = deque()

d = 0
darr = [[-1]*n for _ in range(n)]
dq.append((n//2,n//2))
res = 0

while dq:
    x,y = dq.popleft()
    if((x,y) == (0,0)): break
    darr[x][y] = d
    rd = (d+1)%4
    rx, ry = x + dr[rd], y + dc[rd]
    if darr[rx][ry] == -1:
        d = rd
    darr[x][y] = d
    nx,ny = x+dr[d], y + dc[d]
    now = arr[nx][ny]
    for p in range(len(ratio)):
        mr, mc = nx + dr[d]*pos[p][0] + (not dr[d])*pos[p][1], ny + dc[d]*pos[p][0] + (not dc[d])*pos[p][1] 
        mm = int(now*ratio[p])
        
        if mr < 0 or mc < 0 or mr >= n or mc >= n: res += mm
        else: arr[mr][mc] += mm
        arr[nx][ny] -= mm
    mr, mc = nx + dr[d]*pos[-1][0] + (not dr[d])*pos[-1][1], ny + dc[d]*pos[-1][0] + (not dc[d])*pos[-1][1]
    if mr < 0 or mc < 0 or mr >= n or mc >= n: res += arr[nx][ny]
    else: arr[mr][mc] += arr[nx][ny]
    arr[nx][ny] = 0
    dq.append((nx,ny))
    
print(res)