n = int(input())

house = []
for i in range(n):
    house.append(list(map(int, input().split())))

# 다음 파이프의 위치
di = [0,1,1]
dj = [1,0,1]

# 0 = 가로, 1 = 세로, 2 = 대각선
# 빈공간 체크
# 가로는 오른쪽 한 칸만 빈공간이면 된다.
# 세로는 아래 한 칸만 빈공간이면 된다.
# 대각선 아래는 오른쪽, 아래 오른쪽 아래 대각선 칸이 빈 공간이어야 한다.
checkI = [[0],[1],[0,1,1]]
checkJ = [[1],[0],[1,0,1]]

# 가로 파이프는 대각선 방향과 가로 방향 파이프를 이어서 놓을 수 있다.
# 세로 파이프는 대각선 방향과 세로 방향 파이프를 이어서 놓을 수 있다.
# 대각선 파이프는 대각선 방향과 세로 방향, 가로 방향 파이프를 모두 놓을 수 있다.
nextPipeLen = [2, 2, 3]
nextPipe = [[0,2], [1,2], [0,1,2]]

def isIn(house, x,y, p):
    for dx, dy in zip(checkI[p], checkJ[p]):
        cx = x + dx
        cy = y + dy
        if not (0 <= cx < n and 0 <= cy < n) or house[cx][cy] == 1: return False
    return True

pipe = [[[0]*n for _ in range(n)] for _ in range(3)]
pipe[0][0][1] = 1

for i in range(n):
    for j in range(n):
        if house[i][j] == 1: continue
        for p in range(3):
            for np in nextPipe[p]:
                if isIn(house, i,j, np):
                    ni = i + di[np]
                    nj = j + dj[np]
                    pipe[np][ni][nj] += pipe[p][i][j]
print(pipe[0][-1][-1] + pipe[1][-1][-1] + pipe[2][-1][-1])