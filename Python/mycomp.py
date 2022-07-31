import heapq

class MyComp:
    def __init__(self, price, duedate):
        self.price = price
        self.duedate = duedate
    
    def __lt__(self, other):
        if self.price != other.price: return self.price > other.price
        return self.duedate < other.duedate
    
    def __repr__(self):
        return 'priced: ' + str(self.price) + ' duedate: ' + str(self.duedate)

n = int(input())
hq = []
for i in range(n):
    p,d = map(int, input().split())
    heapq.heappush(hq, MyComp(p,d))

while hq:
    print(heapq.heappop(hq))