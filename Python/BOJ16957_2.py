from collections import deque

n,m = map(int, input().split())

dr = [-1,-1,-1,0,0,1,1,1]
dc = [-1,0,1,-1,1,-1,0,1]

arr = []
for i in range(n):
    arr.append(list(map(int,input().split())))

ball = [[[1]*m for _ in range(n)], [[0]*m for _ in range(n)]]

Q = deque([(i,j) for i in range(n) for j in range(m)])
count = 0
time = 0
update = 1
while update and Q:
    update = 0
    count = len(Q)
    time ^= 1
    while count:
        count -=1
        r,c = Q.popleft()

        next = arr[r][c]
        nextR, nextC = r,c
        for d in range(8):
            nr = r + dr[d]
            nc = c + dc[d]

            if 0 <= nr < n and 0 <= nc < m and arr[nr][nc] < next:
                next = arr[nr][nc]
                nextR, nextC = nr, nc

        if next != arr[r][c]:
            update = 1
        if ball[time][nextR][nextC] == 0:
            Q.append((nextR, nextC))       
        ball[time][nextR][nextC] += ball[time^1][r][c]
        ball[time^1][r][c] = 0
for arr in ball[time]:
    for v in arr:
        print(v, end= ' ')
    print()