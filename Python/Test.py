global N
global resultNum
global atomList
global removeList

# 간단하게 전역변수로 설정
N = [[0] * 4001 for i in range(4001)]
resultNum = [0]
atomList = []
removeList = []


# 원자 클래스 생성
class Atom:
    def __init__(self, x, y, direction, value):
        self.x = x
        self.y = y
        self.direction = direction
        self.value = int(value)
        # 충돌, 혹은 최대거리 이상 이동 후 다음 단계에서 사라질수 있도록 shutDown 추가
        self.shutDown = False
        # 2차원배열
        N[y][x] += 1

    def move(self):

        # 현재 있던 공간에서 움직임
        N[self.y][self.x] -= 1

        if self.direction == 0:
            self.y -= 1
        elif self.direction == 1:
            self.y += 1
        elif self.direction == 2:
            self.x -= 1
        elif self.direction == 3:
            self.x += 1

        # 최대 거리를 벗어났는지 확인
        self.baam()

        # 충돌한 상태면, 다음 위치로 이동하지(그 위치에 추가하지) 않고
        # 원자 큐에서 사라짐

        if self.shutDown == True:
            removeList.append(self)
            # atomList.remove(self)

        # 충돌하지 않았으면 이동
        elif self.shutDown == False:
            N[self.y][self.x] += 1

    # 충돌체크 함수. 같은 좌표에 다른 원자가 있으면 자신의 값을 최종값에 더하고
    # 상태를 종료 상태로 바꿈
    def boom(self):
        if (N[self.y][self.x] > 1):
            print('' + str(self.x) + ' ' + str(self.y) + ' ' + str(self.value))
            resultNum[0] += self.value
            self.shutDown = True

    # 최대거리 체크 함수.
    def baam(self):
        if (self.x > 4000 or self.x < 0 or self.y > 4000 or self.y < 0):
            self.shutDown = True

    def remove(self):
        if self.shutDown == True:
            print('remove : ' + str(self.x) + ' ' + str(self.y) + ' ' + str(self.value))
            removeList.append(self)
            # atomList.remove(self)


T = int(input())

for test_case in range(1, T + 1):
    C = int(input())
    atomList = []
    for case in range(0, C):
        x, y, d, v = map(int, input().split())

        atomList.append(Atom((x * 2) + 2000, 2000 - (y * 2), d, v))

    while (len(atomList) > 0):

        for atom in atomList:
            atom.move()

        for atom in removeList:
            atomList.remove(atom)

        for btom in atomList:
            btom.boom()

    result = "#" + str(test_case) + " " + str(int(resultNum[0]))
    print(result)
    resultNum[0] = 0