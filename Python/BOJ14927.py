n = int(input())
# 자기 자신의 위치까지 포함해서 5개
di = [0,-1,0,1,0]
dj = [0,0,1,0,-1]

# 초기 전구
bulb_init = [list(map(int,input().split())) for _ in range(n)]
bulb = [[0]*(n) for _ in range(n)]
# 모든 전구를 끄기 위한 최소 횟수
min_count = 0x3f3f3f3f

# 좌표가 범위를 벗어나는지 체크하기 위한 함수
check = lambda i,j: 0 <= i < n and 0 <= j < n

# 맨 위의 버튼을 하나씩 다 눌러보기 (비트를 이용한 완전 탐색)
for push in range(1<<n):
    count = 0

    for i in range(n):
        bulb[i][:] = bulb_init[i][:]
    
    for j in range(n):
        # 제일 위의 j번째 전구를 눌렀을 경우 처리
        if push & (1 << j):
            count += 1
            for ni, nj in [(di[d], j + dj[d]) for d in range(5)]:
                if check(ni, nj):
                    bulb[ni][nj] ^= 1

    # 제일 위의 전구들은 이미 처리했기 때문에, 
    # 위의 전구가 아직 켜져 있다면 아래 전구의 상태를 변경해야 합니다.
    for i,j in [(i,j) for i in range(1,n) for j in range(n)]:
        if bulb[i-1][j]:
            count += 1
            for ni,nj in [(i + di[d], j + dj[d]) for d in range(5)]:
                if check(ni,nj):
                    bulb[ni][nj] ^= 1

    # 끝에 있는 모든 전구는 꺼져있어야 합니다.
    # 중간에 있는 전구는 모두 꺼져있는 상태로 유지했기 때문에 신경쓰지 않아도 됩니다.
    if sum(bulb[-1]) == 0:
        min_count = min(min_count, count)

print(-1 if min_count == 0x3f3f3f3f else min_count)