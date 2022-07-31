import requests as rq
import json

def kakao(pid=1):
    url= 'https://huqeyhi95c.execute-api.ap-northeast-2.amazonaws.com/prod'
    token = 'd551728405254cb7c903a62e574c9f82'
    header = {'X-Auth-Token':token,'Content-Type':'application/json'}
    player = [30,900][pid-1]
    bonus = [1,2,4,8,16]
    win = [0]*(player+1)
    lose = [0]*(player+1)

    def waitingLine():
        ret = rq.get(url=url + '/waiting_line',headers=header)
        return ret.json()['waiting_line']

    def gameResult():
        ret = rq.get(url=url+'/game_result', headers = header)
        return ret.json()['game_result']

    def userInfo():
        ret = rq.get(url=url+'/user_info', headers = header)
        return ret.json()['user_info']

    def gameMatch(data):
        data = json.dumps({'pairs':data})
        ret = rq.put(url= url +'/match', headers=header, data=data)
        return ret.json()

    def changeGrade(data):
        data = json.dumps({'commands': data})
        ret = rq.put(url=url+'/change_grade', headers=header,data = data)

    #start API

    auth = rq.post(url+'/start', headers=header, data= json.dumps({'problem':pid})).json()['auth_key']
    header = {'Authorization':auth, 'Content-Type': 'application/json'}
    grade = [0]*(player+1)
    t = 0

    data = []
    for i in range(1, len(grade)):
        data.append({'id':i, 'grade': 4000})
        grade[i] = 4000
    changeGrade(data)
    info = userInfo()
    time = 0
    matching = []
    nowGame = [0]*len(grade)

    while time < 595 :
        result = gameMatch(matching)
        status, time = result['status'], result['time']
        wait = waitingLine()
        nowWait = -1
        matching = []
        info = [(w['from'], w['id'], grade[w['id']]) for w in wait]
        info.sort(key=lambda x: x[2])
        print(info)

        for i in range(0, len(info)-1):
            if nowGame[i] == time: continue
            id1 = info[i][1]
            id2 = info[i+1][1]
            g1 = info[i][2]
            g2 = info[i+1][2]
            matching.append([id1, id2])
            nowGame[id1] = time
            nowGame[id2] = time
                
        result = gameResult()
        if(result): print('result: ', result)
        change = []

        for p in result:
            w = p['win']
            l = p['lose']
            taken = p['taken']
            g1 = float(grade[w])
            g2 = float(grade[l])
            dest = (g1 + g2) / 2
            diff = min(1,40- taken)*100
            possible = 0.8 if g1 + g2 == 0.0 else (g1/(g1+g2)) 

            wdiff = (diff + dest - grade[w])*possible
            ldiff = (dest-diff-grade[l])*possible
            
            grade[w] = int(max(min(9999, (wdiff) + grade[w]),0))
            grade[l] = int(max(min(9999,ldiff + grade[l]),0))
            
            change.append({'id': w, 'grade':grade[w]})
            change.append({'id': l, 'grade':grade[l]})
        changeGrade(change)
    gameMatch([])
    print(userInfo())
    #finish
    print(rq.get(url=url+'/score', headers=header).text)
    return

kakao(pid=2)