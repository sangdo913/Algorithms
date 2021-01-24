def solution(l):
    l.sort()
    li = [[] , [] , []]
    for i in l:
        li[i%3].append(i)

    s = sum(l)
    if s%3 == 0: l = li[0] + li[1] + li[2]
    elif s%3 == 1: l = li[0] + li[1][1:] + li[2] if li[1] else li[0] + li[1] + li[2][2:]
    else: l = li[0] + li[1] + li[2][1:] if li[2] else li[0] + li[1][2:] + li[2]
    if not len(l): return 0
    return int(''.join(list(map(str, sorted(l,reverse=True)))))
     

print(solution([3,1,4,1,5,9]))