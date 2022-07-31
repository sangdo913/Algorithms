from collections import deque

n, k = map(int, input().split())

# -- 주의점 -- #
# 10만 보다 큰 지점으로 순간이동한 후에 -1로 이동하면서 도착지점을 찾는게 빠를 수 있습니다.
t = [0x3f3f3f3f] * 200000

dq = deque([n])

t[n] = 0

# 조건을 deque나 리스트를 넣으면, 자료 구조에 데이터가 있을 경우 True
while dq:
    now = dq.popleft()
    if now*2 < len(t) and t[now*2] > t[now]:
        t[now*2] = t[now]
        dq.append(now*2)
    
    for move in [1,-1]:
        next = now + move
        if 0 <= next < len(t) and t[next] > t[now]+1:
            t[next] = t[now]+1
            dq.append(next)

print(t[k])