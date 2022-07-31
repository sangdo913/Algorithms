datas = [n for n in range(4)]

def permutation(datas, now, select):
    # base case
    # 데이터를 모두 선택한 경우
    if now == select:
        print(datas[:select])
        return

    for idx in range(now, len(datas)):
        # 데이터 자리 교환
        datas[now], datas[idx] = datas[idx], datas[now]
        permutation(datas, now+1, select)
        # 데이터 위치 초기화
        datas[now], datas[idx] = datas[idx], datas[now]

permutation(datas, 0, 3) 