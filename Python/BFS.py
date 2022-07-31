# deque를 사용하기 위한 라이브러리
from collections import deque

def check(num):
    return num == 7

def BFS():
    adj = [[1,2,3], [4,5], [6], [],[7],[],[],[]]
    first = 0

    # 파이썬에선 deque 사용
    queue = deque()

    # 시작 지점 삽입
    queue.append(first)

    # 처음 길이 = 0
    distance = 0

    while len(queue) != 0:
        # 현재 큐의 길이 확인
        count = len(queue)
        
        while count != 0:
            count -= 1

            # 큐에서 데이터 추출
            now = queue.popleft()
            if check(now):  #데이터 전달
                return distance

            # 다음 노드들 결정
            for next in adj[now]:
                queue.append(next)

        # 너비 탐색 완료 후 길이 1 증가
        distance += 1

    return -1

print(BFS())