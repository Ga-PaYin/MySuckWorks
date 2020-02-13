import socket
import json
import sys
import threading
import tkinter as tk

tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
def send(msg):
    addr = ('127.0.0.1',64170)
    try:
        tempSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        tempSocket.connect(addr)
        tempSocket.send(msg.encode('utf-8'))
        reply = json.loads(str(tempSocket.recv(1024),encoding='utf-8'))
        tempSocket.close()
    except:
        reply = {'error':'SERVER ERROR'}
    return reply

def newUser(nickname,password1,password2):
    print(nickname)
    if password1 == password2:
        if len(password1) >= 8:
            newuser = {
                'order':'newUser','password':password1,'nickname':nickname
            }
            msg = json.dumps(newuser)
            result = send(msg)
            if result['error'] == 'no error':
                msgBoxAlert('已提交','账号申请成功，id：' + result['id'])
            else:
                msgBoxWrong('错误！！', result['error'])
        else:
            msgBoxWrong('错误！！','密码过短')
    else:
        msgBoxWrong('错误！！','密码不一致')

def Login(id,password,addr):
    login = {
        'order':'login','password':password,'id':id,'addr':addr
    }
    msg = json.dumps(login)
    result = send(msg)
    if result['error'] != 'no error':
        msgBoxWrong('出错了！！',result['error']) 
        return result['error']
    else:
        return result

def newfriend(me,friend):
    newfriendAsk = {
        'order': 'newFriendAsk', 'me': me, 'friend': friend
    }
    print(newfriendAsk)
    msg = json.dumps(newfriendAsk)
    result = send(msg)
    if result['error'] == 'no error':
        msgBoxWrong('提交成功！','申请提交成功，等待对方回复')
    else:
        msgBoxWrong('出错了！！',result['error'])

def sendmsg(msg,myid,opid):
    sendmsgto = {
        'order':'sendMsgTo','from':myid,'to':opid,'msg':msg
    }
    jsonmsg = json.dumps(sendmsgto)
    result = send(jsonmsg)
    if result['error'] == 'no error':
        return 'send successfully'
    else:
        return result['error']
        
def getmsg(tcpSocket):
    ADDR = socket.gethostbyname(socket.gethostname())
    for i in range(5001,65536):
        try:
            tcpSocket.bind((ADDR, i))
            break
        except:
            continue
    tcpSocket.listen(5)
    while True:
        conn,addr = tcpSocket.accept()
        message = json.loads(str(conn.recv(1024),encoding='utf-8'))
        global friendButtonList
        if message['item'] == 'recvmsg':
            global openingChat, nicknameList
            if message['from'] in openingChat.keys():
                chatHistory = openingChat[message['from']]
                chatHistory.config(state=tk.NORMAL)
                chatHistory.insert(tk.END,nicknameList[message['from']] + ":\n" + message['message'] + '\n')
                chatHistory.config(state=tk.DISABLED)
            else:
                msgBoxAlert("收到了" + nicknameList[message['from']] + '(' + message['from'] + ')的消息',message['message'])    
        elif message['item'] == 'newfriendAsk':
            print("收到好友申请")
            friendrequire = tk.Tk()
            friendrequire.title("好友申请")
            friendrequire.geometry('200x100')
            askmsg = tk.Message(friendrequire, text=message['mynickname'] + '(' + message['from'] + ')申请添加你为好友')
            askmsg.place(relx=0,rely=0.3,relwidth=1,relheight=0.6, anchor='center')
            replyYes = tk.Button(friendrequire,text='同意',command=lambda :newfriendreply(message,'y'))
            replyNo = tk.Button(friendrequire,text='拒绝',command=lambda :newfriendreply(message,'n'))
            replyYes.place(relx=0.2,rely=0.7,relwidth=0.2,relheight=0.15)
            replyNo.place(relx=0.6,rely=0.7,relwidth=0.2,relheight=0.15)
            friendrequire.mainloop()
        elif message['item'] == 'newFriendReply':
            msgBoxAlert('消息通知',message['to'] + '已' + ('同意' if message['answer'] == 'y' else '拒绝') + '添加你为好友')
            if message['answer'] == 'y':
                global loginedgui
                friendinfo = message['nickname'] + '\n' + message['to'] + ' ' + 'online'
                friend = {
                    'id':message['to'],'nickname':message['nickname']
                }
                nicknameList[friend['id']] = message['nickname']
                friendButton = tk.Button(loginedgui,text=friendinfo,command=lambda :chatRoom(friend),anchor=tk.W)
                friendButton.place(relwidth=1, height=40, relx=0, y=40*len(nicknameList))
                friendButtonList[friend['id']] = friendButtonList
        elif message['item'] == 'sta':
                friendButton = friendButtonList[message['id']]
                tempstr = friendButton['text'].split(' ')[0]
                friendButton['text'] = tempstr + ' ' + message['state']
        conn.close()
            
def newfriendreply(message,answer):
    friendAskReply = {
        'order': 'newFriendReply', 'from': message['to'], 'to': message['from'], 'answer': answer
    }
    jsonmsg = json.dumps(friendAskReply)
    result = send(jsonmsg)
    if result['error'] == 'no error':
        msgBoxAlert('to ' + message['from'],'您的消息已发送成功')
        if answer == 'y':
            global loginedgui,friendButtonList
            print(message)
            friendinfo = message['mynickname'] + '\n' + message['to'] + ' ' + 'online'
            friend = {
                'id':message['to'],'nickname':message['mynickname']
            }
            nicknameList[friend['id']] = message['mynickname']
            friendButton = tk.Button(loginedgui,text=friendinfo,command=lambda :chatRoom(friend),anchor=tk.W)
            friendButton.place(relwidth=1, height=40, relx=0, y=40*len(nicknameList))
            friendButtonList[friend['id']] = friendButton
    else:
        msgBoxWrong('出错了！！', result['error'])

def newUsergui():
    newUserWindow = tk.Tk()
    newUserWindow.title('盗版微信demo--注册')
    newUserWindow.geometry('500x300')
    password1 = tk.StringVar()
    password2 = tk.StringVar()
    nickname = tk.StringVar()
    nickNameLabel = tk.Label(newUserWindow,text='请输入昵称',width=10,anchor='e')
    nickNameInput = tk.Entry(newUserWindow,textvariable=nickname)
    passwordLabel = tk.Label(newUserWindow,text='请输入密码',width=10,anchor='e')
    passwordInput = tk.Entry(newUserWindow,textvariable=password1,show='*')
    pwdconfirmLabel = tk.Label(newUserWindow,text='请再次输入密码',width=10,anchor='e')
    pwdconfirmInput = tk.Entry(newUserWindow,textvariable=password2,show='*')
    confirmButton = tk.Button(newUserWindow,text='提交',command=lambda :newUser(nickNameInput.get(),passwordInput.get(),pwdconfirmInput.get()))
    nickNameLabel.place(relx=0.2,rely=0.3)
    nickNameInput.place(relx=0.5,rely=0.3)
    passwordLabel.place(relx=0.2,rely=0.5)
    passwordInput.place(relx=0.5,rely=0.5)
    pwdconfirmLabel.place(relx=0.2,rely=0.7)
    pwdconfirmInput.place(relx=0.5,rely=0.7)
    confirmButton.place(relx=0.45,rely=0.85)
    newUserWindow.mainloop()

def msgBoxWrong(title,wrongmsg):
    wrong = tk.Tk()
    wrong.title(title)
    wrong.geometry('200x100')
    wrongmsg = tk.Message(wrong, text=wrongmsg)
    wrongmsg.pack(fill='both', anchor='center')
    wrong.mainloop()

def msgBoxAlert(title,alertmsg):
    alert = tk.Tk()
    alert.title(title)
    alert.geometry('400x100')
    alertmsg = tk.Message(alert,text=alertmsg)
    alertmsg.pack(fill='both',anchor='center')
    alert.mainloop()

def chatRoom(friend):
    def chatRoomClose(id, thiswindow):
        global openingChat
        if id in openingChat.keys():
            openingChat.pop(id)
        else:
            print(id + '窗口已删除')
        thiswindow.destroy()

    def sendbutton(msgInput, chatHistory, friend):
        msg = msgInput.get('0.0', tk.END)
        global MYID, MYNickName
        result = sendmsg(msg, MYID, friend['id'])
        # result = 'send successfully'
        if result == 'send successfully':
            chatHistory.config(state=tk.NORMAL)
            chatHistory.insert(tk.END, MYNickName + ":\n" + msg + "\n")
            chatHistory.config(state=tk.DISABLED)
            msgInput.delete('0.0', tk.END)
        else:
            msgBoxWrong('出错了', result)

    chat = tk.Tk()
    chat.geometry('500x400')
    global openingChat
    chat.title(friend['nickname'] + friend['id'])
    chatHistory = tk.Text(chat,state=tk.DISABLED)
    msgInput = tk.Text(chat)
    chatHistory.place(relx=0.05,rely=0.05,relwidth=0.9,relheight=0.55)
    msgInput.place(relx=0.05,rely=0.65,relwidth=0.6,relheight=0.3)
    msgSendButton = tk.Button(chat,text='发送',command=lambda :sendbutton(msgInput,chatHistory,friend))
    msgSendButton.place(relx=0.75,rely=0.65,relwidth=0.2,relheight=0.14)
    msgClearButton = tk.Button(chat,text='清空',command=lambda :msgInput.delete('0.0',tk.END))
    msgClearButton.place(relx=0.75,rely=0.81,relwidth=0.2,relheight=0.14)
    openingChat[friend['id']] = chatHistory
    chat.protocol("WM_DELETE_WINDOW",lambda :chatRoomClose(friend['id'],chat))
    chat.mainloop()

def askfriend():
    ask = tk.Tk()
    ask.title('添加新朋友')
    ask.geometry('500x400')
    reminder = tk.Label(ask,text='请输入添加朋友的id',anchor='center')
    idInput = tk.Entry(ask)
    confirm = tk.Button(ask,text='确认',command=lambda :newfriend(MYID,idInput.get()))
    reminder.place(relx=0.25,rely=0.3,relwidth=0.5)
    idInput.place(relx=0.25,rely=0.5,relwidth=0.5)
    confirm.place(relx=0.4,relwidth=0.2,rely=0.8)
    ask.mainloop()

def logingui(id,password,loginWindow):
    global MYID,MYNickName,tcpSocket,loginedgui
    global tcpSocket
    addr = tcpSocket.getsockname()
    result = Login(id,password,addr)
    if type(result) != str:
        MYID = id
        loginWindow.destroy()
        userWindow = tk.Tk()
        userWindow.title(id)
        userWindow.geometry('300x600')
        nicknameLabel = tk.Label(userWindow,text=result['nickname'],width=len(result['nickname'])+1,anchor=tk.W)
        nicknameLabel.place(relx=0,rely=0,relwidth=1,height=40)
        i = 1
        MYNickName = result['nickname']
        newfriendButton = tk.Button(userWindow,text='+',command=askfriend)
        newfriendButton.place(relx=0.9,rely=0.9)
        global nicknameList,friendButtonList
        for friend in result['friendList']:
            nicknameList[friend['id']] = friend['nickname']
            friendinfo = friend['nickname'] + '\n' + friend['id'] + ' ' + ('online' if friend['online'] == 1 else 'offline')
            friendButton = tk.Button(userWindow,text=friendinfo,command=lambda friend=friend:chatRoom(friend),anchor=tk.W)
            friendButton.place(relwidth=1,height=40,relx=0,y=40*i)
            friendButtonList[friend['id']] = friendButton
            i += 1
        loginedgui = userWindow
        userWindow.mainloop()
    else:
        print(result)
    

def InitWindow(window):
    window.title('盗版微信demo--登录')
    window.geometry('500x300')
    idLabel = tk.Label(window,text='盗版微信号',width=10,anchor=tk.E)
    idInput = tk.Entry(window)
    passwordLabel = tk.Label(window,text='密码',width=10,anchor=tk.E)
    passwordInput = tk.Entry(window,show='*')
    newUserBut = tk.Button(window,text='注册',command=lambda :newUsergui())
    loginBut = tk.Button(window,text='登录',command=lambda :logingui(idInput.get(),passwordInput.get(),window))
    idLabel.place(relx=0.2,rely=0.3)
    idInput.place(relx=0.5,rely=0.3)
    passwordLabel.place(relx=0.2,rely=0.6)
    passwordInput.place(relx=0.5,rely=0.6)
    loginBut.place(relx=0.3,rely=0.8)
    newUserBut.place(relx=0.6,rely=0.8)
    window.mainloop()

MYID = ''
MYNickName = ''
openingChat = {}
nicknameList = {}
loginedgui = None
friendButtonList = {}
if __name__ == "__main__":    
    recvMessage = threading.Thread(target=lambda :getmsg(tcpSocket),daemon=True)
    recvMessage.start()
    loginWindow = tk.Tk()
    InitWindow(loginWindow)

    print('end')
