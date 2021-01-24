from collections import deque

def solution(arr):
    dist = [[[0x3f3f3f3f]*len(arr[0]) for _ in range(len(arr))] for _ in range(2)]
    Q = deque([[0,0,0]])
    dist[0][0][0] = 1
    dest = (len(arr)-1, len(arr[0])-1)
    # print(dist)
    dx = [-1,0,1,0]
    dy = [0,1,0,-1]
    # for li in arr:
    #     print(li)
    while Q:
        x,y,s = Q.popleft()
        if dest[0] == x and dest[1] == y: return dist[s][x][y]

        for nx, ny in [(x + dx[d],y + dy[d]) for d in range(4)]:
            if nx < 0 or nx == len(arr) or ny < 0 or ny == len(arr[0]): continue
            if arr[nx][ny] == 1:
                if s: continue
                if dist[1][nx][ny] <= dist[s][x][y] + 1: continue
                dist[1][nx][ny] = dist[s][x][y] + 1
                Q.append([nx,ny,1])
            else:
                if dist[s][nx][ny] <= dist[s][x][y]: continue
                dist[s][nx][ny] = dist[s][x][y] + 1
                Q.append([nx,ny,s])

print(solution([[0, 1, 1, 0], [0, 0, 0, 1], [1, 1, 0, 0], [1, 1, 1, 0]]))