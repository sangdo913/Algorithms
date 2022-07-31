import heapq

class meeting:
    def __init__(self,info):
        self.st, self.ed = info
    def __lt__(self, other):
        if self.ed != other.ed:
            return self.ed < other.ed
        return self.st < other.st

n = int(input())
info = []

for i in range(n):
    info.append(meeting(list(map(int,input().split()))))

heapq.heapify(info)
last = -1
res = 0

while info:
    m = heapq.heappop(info)
    st, ed = m.st, m.ed
    if last <= st:
        res += 1
        last = ed
print(res)