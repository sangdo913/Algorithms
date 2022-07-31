n, m = map(int, input().split())

dr = [-1,-1,-1, 0,0, 1,1,1]
dc = [-1,0,1, -1,1, -1,0,1]
arr = []
# *주의점 체스판 위에는 30만 까지의 수가 써 있을 수 있습니다.
position = [() for _ in range(300001)]
ball = [1] * (300001)
nums = []

for i in range(n):
    arr.append(list(map(int, input().split())))
    for j in range(m):
        position[arr[i][j]] = (i,j)
        nums.append(arr[i][j])

# 들어있는 수를 큰 순서대로 찾을 수 있도록 정렬합니다.
nums.sort(reverse=True)

for num in nums:
    r, c = position[num]
    # Tip 체스판 위 공의 다음 이동 방향은 인접한 8방향 중에서 가장 작은 숫자가 써있는 방향입니다.
    # 만약, 현재 위치에 써있는 숫자와 8방향에 써있는 숫자 중에서 가장 최소의 수를 찾았는데 자기 자신의 수가 나오면 공은 이동하지 않습니다.
    next = num
    for d in range(8):
        nr, nc = r + dr[d], c + dc[d]
        if 0 <= nr < n and 0 <= nc < m:
            next = min(next, arr[nr][nc])

    if next != num:
        ball[next] += ball[num]
        ball[num] = 0

for i in range(n):
    for j in range(m):
        num = arr[i][j]
        print(ball[num], end=' ')
    print()