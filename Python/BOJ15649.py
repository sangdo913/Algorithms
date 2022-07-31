n, m = map(int, input().split())

# 이미 선택된 수인지 체크
visit = [0]*(n+1)
res = []

def permutation(len):
    # 현재 선택된 배열의 길이
    # base case: 배열이 처음에 주어진 m만큼 선택
    if len == m:
        for i in res:
            print(i, end=' ')
        print()
        return
    
    for i in range(n):
        # 1 ~ n 까지의 수 선택
        v = i+1

        # 이미 선택된 수면 다른 수 선택
        if visit[v] == 1:
            continue
        visit[v] = 1
        res.append(v)

        # 다음 수 선택
        permutation(len+1)

        # 이전에 선택된 수 체크 해재 후 선택된 수를 배열에서 제거
        visit[v] = 0
        res.pop()

permutation(0)