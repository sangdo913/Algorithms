import heapq

class MyComp:
    def __init__(self, p):
        self.p = p

    def __lt__(self, other):
        return self.p > other.p

n = int(input())
hq = []

# 10000일 까지 가능합니다.
lectures = [[] for _ in range(10001)]

for i in range(n):
    p,d = map(int,input().split())
    lectures[d].append(p)

res = 0
# 10000일 부터 현재 가능한 강의들 중에서 가장 비싼 강의를 진행합니다.
for d in range(10000, 0, -1):
    for p in lectures[d]:
        heapq.heappush(hq, MyComp(p))
    res += heapq.heappop(hq).p if hq else 0

print(res) 


