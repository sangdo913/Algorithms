import requests
import random
import json

scom = ['not', 'up', 'right', 'down','left', 'in', 'out']
dr = [0,-1,0,1,0,0,0]
dc = [0,0,1,0,-1,0,0]
tcommand = {scom[i] : i for i in range(7)}

class truck:
    def __init__(self):
        self.p = 0
        self.load = 0
    
    def __str__(self):
        return str(self.p)+ ' ' + str(self.load)

    def __repr__(self):
        return '(' + str(self.p) + ' '+ str( self.load) +')'

def getlocation(url, headers, bycycle):
    path = 'locations'
    req = requests.get('/'.join([url,path]),headers=headers)

    j = req.json()

    for id, cnt in [(i['id'], i['located_bikes_count']) for i in j['locations']]:
        bycycle[id] = cnt
    
    return bycycle
    
def gettrucks(url, headers, trucks):
    path = 'trucks'
    req = requests.get('/'.join([url,path]), headers=headers)    


    j = req.json()
    for id, p, cnt in [(i['id'], i['location_id'], i['loaded_bikes_count']) for i in j['trucks']] :
        trucks[id].p = p
        trucks[id].load = cnt

    return trucks

def simulate(url, header, data):
    path = 'simulate'
    req = requests.put('/'.join([url,path]), headers = header, data=data)

    return req.json()

def getdist(loc, f, t):
    dcom = [tcommand['up'] for i in range(abs(loc[f][0] - loc[t][0])) if loc[f][0] > loc[t][0]]
    dcom.extend( [tcommand['down'] for i in range(abs(loc[f][0] - loc[t][0])) if loc[f][0] < loc[t][0]])
    dcom.extend( [tcommand['right'] for i in range(abs(loc[f][1] - loc[t][1])) if loc[f][1] < loc[t][1]])
    dcom.extend( [tcommand['left'] for i in range(abs(loc[f][1] - loc[t][1])) if loc[f][1] > loc[t][1]])
    return (abs(loc[f][0] - loc[t][0]) + abs(loc[f][1] - loc[t][1]), dcom) 

def truckmove(t, bnum, map, mmap, mean, comm, dest, all = 'not'):
    x, y = map[t.p][0], map[t.p][1]
    retcomm = []
    if all =='out' or all == 'in':
        mean = 1

    for i in comm:
        if len(retcomm) >= 10: break
        id = mmap[x][y]
        if id == dest and all == 'out':
            need = t.load
            retcomm.extend([tcommand['out'] for i in range(need) if need > 0])
            bnum[id] += need
        elif all == 'in' and id == dest:
            need = min(bnum[id] - mean, 20 - t.load)
            retcomm.extend([tcommand['in'] for i in range(need) if need > 0])
            bnum[id] -= need
        elif all == 'out':
                need = min(bnum[id] - mean, 20 - t.load)
                retcomm.extend([tcommand['in'] for i in range(need) if need > 0])
                bnum[id] -=need
        elif all == 'in':
                need = min(mean - bnum[id], t.load)

                retcomm.extend([tcommand['out'] for i in range(need) if need > 0])
                bnum[id]+= need
        else:
            if bnum[id] < mean:
                need = min(mean - bnum[id], t.load)

                retcomm.extend([tcommand['out'] for i in range(need) if need > 0])
                bnum[id]+= need
            elif bnum[id] > mean:
                need = min(bnum[id] - mean, 20 - t.load)
                retcomm.extend([tcommand['in'] for i in range(need) if need > 0])
                bnum[id] -=need
        
        retcomm.append(i)
        x+= dr[i]
        y+= dc[i]

    return retcomm

def kakaotaxi(qid=1):
    url = 'https://pegkq2svv6.execute-api.ap-northeast-2.amazonaws.com/prod/users'
    path = 'start'
    token = '45dba8398be9c75b0decc13f3881f535'
    param = {'problem':qid}
    headers = {'X-Auth-Token':token, 'Content-Type': 'application/json'}

    msize = 0
    mean = 15
    if qid == 1: 
        msize = 5
        mean = 2
    else: 
        msize = 60
        mean = 3
    mymap = [[msize-i-1 + msize*j for j in range(msize)] for i in range(msize)]
    pos = { mymap[i][j] : (i,j) for i in range(msize) for j in range(msize)}
    bycycles = [ 0 for i in range(msize*msize)]
    tnum = [0,5,10]
    trucks = [truck() for i in range(tnum[qid]) ]
    req = requests.post('/'.join([url,path]),headers = headers, data=json.dumps(param))
    j = req.json()
    auth_key = j['auth_key']
    headers = {'Authorization': auth_key, 'Content-Type':'applications/json'}

    next_command = [[] for i in range(len(trucks))]
    bnum = [0,4,3]
    prev_bycycle = [[bnum[qid] for i in range(msize*msize)] for i in range(5)]

    for i in range(720):
        ti = i
        trucksdes = [int(random.uniform(0,msize*msize)) for i in range(len(trucks))]
        bycycles = getlocation(url, headers, bycycle =bycycles)
        for id in range(len(bycycles)):
            prev_bycycle[int(ti/240)+1][id] += bycycles[id]
        mmin = 100000000
        mini = 0
        mmax = -1000000000
        maxi = 0

        for i, j in enumerate(prev_bycycle[int(ti/240)+1][i] - prev_bycyle[0][i] for i in range(len(bycycles))]):
            if mmin > j:
                mmin, mini = j, i
            if mmax > j:
                mmax, maxi = j, i

        trucks = gettrucks(url, headers, trucks)
        emergen = [i[0] for i in enumerate(bycycles) if i[0] == 0]

        i = 0
        while i < min(int(mmin/20), tnum[qid]):                
            trucksdes[i] = mini
            i+=1
        while i < min(int(mmax/20), tnum[qid] ):
            trucksdes[i] = maxi
            i+=1

        for i in range(tnum[qid]):
            t = trucks[i]
            if len(emergen) > 0:
                trucksdes[i] = emergen.pop()
            idx, next_command[i] = getdist(pos, t.p, trucksdes[i])
            
        nextcommand = []

        for i in range(tnum[qid]):
            t = trucks[i]
            ncom = truckmove(t, bycycles, pos, mymap, mean, next_command[i], -1, 'not')
            nextcommand.append({'truck_id': i, 'command' : ncom})

        j = simulate(url,header=headers, data=json.dumps({'commands':nextcommand}))
        print(j['time'])
        
        prev_bycycle = [i for i in bycycles]

    req = requests.get(url + '/score',headers = headers)
    print(req.json()['score'])

kakaotaxi(2)
#kakaotaxi(2)