def solution(total_lambs):
    mmin, mmax = 0,0
    temp = total_lambs
    i = 1
    while temp - i >= 0:
        temp -= i
        i <<= 1
        mmin += 1

    if total_lambs == 1: mmax = 1
    elif total_lambs == 2: mmax = 2
    l1, l2 = 1,1
    mmax = 2
    total_lambs -= 2
    while(total_lambs - l1 - l2 >= 0):
        total_lambs -= l1 + l2
        mmax+=1
        l1, l2  = l2, l1+l2
        # print(l1,l2)
    print(mmax, mmin)
    return mmax - mmin

print(solution(2))