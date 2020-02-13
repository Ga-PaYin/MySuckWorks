import pymysql
import sys
import socket
import random
import threading
import time
import json
def database_Execute(sqlsentence):
    db = pymysql.connect(host = "localhost",user = "root",db = "wechatdemo")
    cursor = db.cursor()
    try:
        cursor.execute(sqlsentence)
        data = cursor.fetchall()
        db.commit()
    except:
        db.rollback()
        data = ("database error")
    db.close()
    return data

def sendmessage(msg,addr):
    tempSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tempSocket.connect(addr)
    tempSocket.send(msg.encode('utf-8'))
    tempSocket.close()

def newUser(message):
    nickname = message['nickname']
    password = message['password']
    id = 0
    i = 0
    returnVal = {'item':'newUser','error':'no error'}
    while i < 100:
        id = random.randint(0, 10000000000)
        sql = 'insert into user_info (id,nickname,password,online) value("' + str(id) + '","' + nickname + '","' + password + '",false);'
        result = database_Execute(sql)
        if "database error" in result:
            returnVal['error'] = "database error"
        else:
            returnVal['id'] = str(id)
            break
        i += 1
    sql = "create table id" + str(id) + " (id varchar(10) unique);"
    result = database_Execute(sql)
    if "database error" in result:
        returnVal['error'] = "create fail"
        sql = 'delete from user_info where id = ' + str(id) + '";'
        database_Execute(sql)
    return json.dumps(returnVal)

def getfriendList(id):
    friendList = []
    sql = 'select id from id' + id + ';'
    print(sql)
    friend = database_Execute(sql)
    print("friend = ",end = '')
    print(friend)
    if friend != ():
        for item in friend:
            it = item[0]
            sql = 'select online,nickname from user_info where id = "' + str(it) + '";'
            print(sql)
            result = database_Execute(sql)[0]
            thisfriend = {
                'id':it,'nickname':result[1],'online':result[0]
            }
            friendList.append(thisfriend)
    return friendList

def login(message):
    id = message['id']
    password = message['password']
    ipAddr = message['addr'][0]
    port = message['addr'][1]
    sql = 'select nickname,password from user_info where id = "' + id + '";'
    result = database_Execute(sql)[0]
    returnVal = {'item':'login','error':'no error','nickname':'','friendList':[]}
    if result == ():
        returnVal['error'] = 'id not exist'
    else: 
        returnVal['nickname'] = result[0]
        print(password)
        print(result[1])
        if password == result[1]:
            sql = 'update user_info set online = true, ipAddress = "' + ipAddr + '", port = "' + str(port) + '" where id = "' + id + '";'
            result = database_Execute(sql)
            if 'database error' not in result:
                returnVal['friendList'] = getfriendList(id)
                print('friendList = ',end='')
                print(returnVal['friendList'])
            else:
                returnVal['error'] = 'login error'
        else:
            returnVal['error'] = 'wrong password'
    return json.dumps(returnVal)

def offline():
    while True:
        time.sleep(60)
        print("offline is running")
        sql = 'select id,ipAddress,port from user_info where online = 1;'
        result = database_Execute(sql)
        for item in result:
            id = item[0]
            Addr = (item[1],item[2])
            try:
                checkOnline = json.dumps({'item':'checkOnline'})
                sendmessage(checkOnline,Addr)
            except:
                sql = 'update user_info set online = false where id = ' + id + ';'
                database_Execute(sql)
                sql = 'select id from id' + id +';'
                result_ = database_Execute(sql)
                for item in result_:
                    friend = item[0]
                    print('friend = ' + friend)
                    sql = 'select online,ipAddress,port from user_info where id = ' + friend + ';'
                    oap = database_Execute(sql)
                    print('oap = ',end='')
                    print(oap)
                    if oap[0][0] == 1:
                        addr = (oap[0][1],oap[0][2])
                        sendmessage(id + '_offLine', addr)
                continue

def getAddr(friend):
    sql = 'select online,ipAddress,port from user_info where id = "' + friend + '";'
    result = database_Execute(sql)
    if "database error" not in result:
        print(result)
        if result[0][0] == 1:
            return (result[0][1],result[0][2])
        else:
            return "user offline"

def getNickname(id):
    sql = 'select nickname from user_info where id = "' + id + '";'
    result = database_Execute(sql)
    if "database error" not in result:
        return result[0][0]
    else:
        return "database error"

def isFriend(sendfrom,sendto):
    sql = 'select id from id' + sendfrom + ' where id = "' + sendto +'";'
    result = database_Execute(sql)
    return result[0] != ()

def addfriend(me,friend):
    sql = 'insert into id' + me + ' value("' + friend + '");'
    print(sql)
    database_Execute(sql)
    sql = 'insert into id' + friend + ' value("' + me + '");'
    print(sql)
    database_Execute(sql)

def askfriend(me,friend):
    add = getAddr(friend)
    if type(add) == tuple:
        nickname = getNickname(me)
        print('nickname = %s' % nickname)
        if nickname != 'database error':
            quest = {
                'item':'newfriendAsk','from':me,'to':friend,'mynickname':nickname
            }
            sendmessage(json.dumps(quest),add)
            print('asked')
            return 'asked'
        else:
            return nickname
    else:
        return add

if __name__ == "__main__":
    tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcpSocket.bind(('127.0.0.1', 64170))
    tcpSocket.listen(5)

    heartbeat = threading.Thread(target=offline,daemon=True)
    heartbeat.start()
    
    while True:
        print("server listening")
        conn,addr = tcpSocket.accept()
        print(addr)
        require = json.loads(str(conn.recv(1024),encoding="utf-8"))
        print(require)
        order = require['order']
        print(order)
        if order == "newUser":
            conn.send(newUser(require).encode('utf-8'))
        elif order == "login":
            result = login(require)
            conn.send(result.encode('utf-8'))
        elif order == "sendMsgTo":
            sendfrom = require['from']
            sendto = require['to']
            msg = require['msg']
            returnVal = {
                'item':order, 'error':'no error',
            }
            if isFriend(sendfrom,sendto):
                Addr = getAddr(sendto)
                if type(Addr) == tuple:
                    print(Addr[0])
                    print(Addr[1])
                    toMsg = {'item':'recvmsg','from':sendfrom, 'message':msg}
                    sendmessage(json.dumps(toMsg),Addr)
                else:
                    returnVal['error'] = 'user ' + sendto + ' offline'
            else:
                returnVal['error'] = 'you are not friend with ' + sendto
            conn.send(json.dumps(returnVal).encode('utf-8'))
        elif order == "newFriendAsk":
            me = require['me']
            friend = require['friend']
            answer = askfriend(me,friend)
            returnVal = {
                'error':'no error','item':'newFriendAsk'
            }
            if answer != 'asked':
                returnVal['error'] = answer
            print(returnVal)
            conn.send(json.dumps(returnVal).encode('utf-8'))
        elif order == "newFriendReply":
            from_ = require['from']
            to = require['to']
            answer = require['answer']
            Addr = getAddr(to)
            returnVal = {
                'item': 'newFriendReply', 'to': from_, 'answer': 'y'
            }
            if answer == 'y':
                addfriend(me,friend)
                returnVal['nickname'] = getNickname(from_)
            else:
                returnVal['answer'] = 'n'
            sendmessage(json.dumps(returnVal),Addr)
            conn.send(json.dumps({'error':'no error'}).encode('utf-8'))
        conn.close()
    #-----
    tcpSocket.close()
