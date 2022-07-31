n = int(input())

ropes = []
for i in range(n):
    ropes.append(int(input()))

ropes.sort(reverse=True)

res = 0
for i in range(n):
    res = max(res, (i+1)*ropes[i])
print(res)