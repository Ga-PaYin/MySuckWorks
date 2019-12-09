import requests
from bs4 import BeautifulSoup
import os
import time
import random
import sys
import win32api
import win32con
import win32gui
def getHTML(url):
    for i in range(0,10):
        try:
            r = requests.get(url)
            r.raise_for_status()
            r.encoding = r.apparent_encoding
            print("get html successfully")
            return r.text
        except:
            print("getHTML error")
            if i < 9 :
                print('tring again...')
            else:
                print('I tried')

def parserHTML(html):
    try:
        soup = BeautifulSoup(html,"html.parser")
        return soup.find('a',attrs={'class':'preview'})['href']
    except:
        print('parseError')
def getPhoto(html):
    try:
        soup = BeautifulSoup(html,"html.parser")
        print(soup.find('img',attrs={'id':'wallpaper'})['src'])
        return soup.find('img',attrs={'id':'wallpaper'})['src']
    except:
        pass
def savePicture(imag):
    root = 'C:\\Users\\10990\\Pictures\\DesktopPaper\\'
    path = root + imag.split('/')[-1]
    try:
        if not os.path.exists(root):
            os.mkdir(root)
        if not os.path.exists(path):
            print("downloading picture")
            print('imag = ' + imag)
            r = requests.get(imag)
            print("downloaded")
            with open(path,'wb') as f:
                f.write(r.content)
                time.sleep(5)
                f.close()
                print("Picture Saved at " + path + " Successfully")
        else:
            print("Picture Exist")
        return path
    except:
        print("fail to get the picture")
def setWallPaper(Imag):
    # 打开指定注册表路径
    reg_key = win32api.RegOpenKeyEx(win32con.HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, win32con.KEY_SET_VALUE)
    # 最后的参数:2拉伸,0居中,6适应,10填充,0平铺
    win32api.RegSetValueEx(reg_key, "WallpaperStyle", 0, win32con.REG_SZ, "10")
    # 最后的参数:1表示平铺,拉伸居中等都是0
    win32api.RegSetValueEx(reg_key, "TileWallpaper", 0, win32con.REG_SZ, "0")
    # 刷新桌面
    win32gui.SystemParametersInfo(win32con.SPI_SETDESKWALLPAPER,Imag, win32con.SPIF_SENDWININICHANGE)
def main(keyword):
    # keyword = input()
    url = 'https://wallhaven.cc/search?q=' + keyword + '&categories=111&purity=100&atleast=2560x1920&sorting=random&order=desc'
    print("grasping photo from wallhaven...")
    HTMLpage = ''
    while HTMLpage == '':
        HTMLpage = getHTML(url)
    print("grap web successfully")
    photoAddress = parserHTML(HTMLpage)
    photo = getHTML(photoAddress)
    if photo != '':
        imag = getPhoto(photo)
        LocalImag = savePicture(imag)
        setWallPaper(LocalImag)
    
if __name__ == '__main__':
    keyword = ''
    if len(sys.argv) == 1:
        keywordList = ['space','mountain','river','galaxy','moon','earth','sun','sky','planet','universe','rain','aurora']
        keyword = keywordList[ random.randint(0,len(keywordList)) ]
    else:
        keyword = sys.argv[1]
    print('keyword = ' + keyword)
    main(keyword)
