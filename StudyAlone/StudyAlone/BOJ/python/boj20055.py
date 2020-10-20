from collections import deque
(n, k) = list(map(int,input().split()))
belt = list(map(int, input().split()))
robots = [0]*(2*n)
pos = deque()
psize = 0
l = 2*n

# print(belt)
cnt = 0
cur = 0
while(k > 0):
    # print(pos)
    # print(robots)
    # print(belt)
    # print('===')
    cur-=1
    cnt+=1
    size = psize
    #print('after cur', robots[cur%l:] + robots[:cur%l])
    while size:
        size-= 1
        p = pos.popleft()
        psize-=1
        b = (p - cur) %n
        if b == n-1 : 
            robots[p] = 0
            continue  

        nxt = (p+1)%l

        if belt[nxt] > 0 and robots[nxt] == 0:
            belt[nxt]-=1
            k -= int(belt[nxt] == 0)
            robots[nxt] = 1
            robots[p] = 0
            b = (nxt-cur)%n
            if b == n-1: 
                robots[nxt] = 0
                continue 

            p = nxt

        pos.append(p)
        psize+=1

    p = cur%l
    if belt[p] > 0:
        belt[p]-=1
        k -= int(belt[p]==0)
        pos.append(p) 
        psize+=1
        robots[p] = 1
    #print('after move', robots[cur%l:] + robots[:cur%l])
print(cnt)