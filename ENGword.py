import requests
import re
from bs4 import BeautifulSoup

def getHTMLText(url):
    try:
        r = requests.get(url)
        r.raise_for_status
        r.encoding = r.apparent_encoding
        return r.text
    except:
        return ""

def parserHTML(html,word):
    try:
        soup = BeautifulSoup(html,"html.parser")
        meaningList = []
        meaning = soup.find_all(name = "div",attrs = {"class":"trans-container"})[0]
        for li in meaning.find_all(name = "li"):
            meaningList.append(li)
        return meaningList
    except:
        return ""

def printMeanings(meaningList):
    if meaningList == []:
        print("查无此词")
    else:
#        for i in range(len(meaningList)):
#            stringMeaning = str(meaningList[i]).split(">")[1].split("<")[0]
        for i in meaningList:
            stringMeaning = re.split(r'>|<',re.search(r">.*<",str(i)).string)[2]
            print("\t"+stringMeaning)

def main():
    while True:
        word = input("你要查询的词是：")
        url = "http://dict.youdao.com/w/"+word+"/#keyfrom=dict2.top"
        html = getHTMLText(url)
        parser = parserHTML(html,word)
        printMeanings(parser)
main()