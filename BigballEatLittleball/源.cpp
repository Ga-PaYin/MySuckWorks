#include"circle.h"
#include<ctime>
#include<fstream>
#include<iostream>

using namespace std;
int versusEnermy(myCircle *user, Circle *enermy) {
	if (sqrt(pow(user->getX() - enermy->getX(), 2) + pow(user->getY() - enermy->getY(), 2)) - user->getRadius() - enermy->getRadius() <= 0.00001) {
		if (user->getRadius() > enermy->getRadius()) {
			delete enermy;
			user->resize();
			return 1;
		}
		else {
			delete user;
			return 0;
		}
	}
	else {
		return 2;
	}
}

int Larger(Circle **enermy,myCircle *user) {
	int n = 0;
	for (int i = 0; i < CIRCLECOUNT; i++) {
		if (enermy[i] != NULL) {
			if (enermy[i]->getRadius() >= user->getRadius()) {
				n++;
			}
		}
	}
	return n;
}

int Smaller(Circle **enermy,myCircle *user) {
	int n = 0;
	for (int i = 0; i < CIRCLECOUNT; i++) {
		if (enermy[i] != NULL) {
			if (enermy[i]->getRadius() < user->getRadius()) {
				n++;
			}
		}
	}
	return n;
}

Circle *newEnermy(myCircle *user,Circle **enermyArr) {
	srand((unsigned)time(NULL));
	int enermyR;
	if (Smaller(enermyArr,user) == 0) {
		enermyR = rand() % (user->getRadius() - 5) + 5;
	}
	else if(Larger(enermyArr,user) == 0) {
		enermyR = rand() % (user->getMax() - user->getRadius()) + user->getRadius();
	}
	else {
		if (rand() % 2) {
			enermyR = rand() % (user->getRadius() - 5) + 5;
		}
		else {
			enermyR = rand() % (user->getMax() - user->getRadius()) + user->getRadius();
		}
	}
	Circle *enermy = new Circle(rand() % (graphWidth - enermyR * 2) + enermyR, rand() % (graphHeight - enermyR * 2) + enermyR, enermyR, rand() % 16777216, rand() % (graphWidth / 100) + 1, rand() % (graphHeight / 100) + 1);
	return enermy;
}

void startGame() {
	/*这是正式的写游戏过程的函数*/
	cleardevice();
	srand((unsigned)time(NULL));
	MOUSEMSG mousemsg = GetMouseMsg();
	myCircle *user = new myCircle(mousemsg.x, mousemsg.y, ORIGINALR, MAGENTA,MAX);
	Circle *enermy[CIRCLECOUNT];
	for (int i = 0; i < CIRCLECOUNT / 2; i++) {
		int enermyR = rand() % (ORIGINALR - 5) + 5;
		enermy[i] = new Circle(rand() % (graphWidth - enermyR * 2) + enermyR, rand() % (graphHeight - enermyR * 2) + enermyR, enermyR, rand()%16777216, rand() % (graphWidth / 100), rand() % (graphHeight / 100));
	}
	for (int i = CIRCLECOUNT / 2; i < CIRCLECOUNT; i++) {
		int enermyR = rand() % (user->getMax() - user->getRadius());
		enermy[i] = new Circle(rand() % (graphWidth - enermyR * 2) + enermyR, rand() % (graphHeight - enermyR * 2) + enermyR, enermyR, rand()%16777216, rand() % (graphWidth / 100), rand() % (graphHeight / 100));
	}
	Sleep(1500);
	while (true) {
		if (MouseHit()) {
			FlushMouseMsgBuffer();
			mousemsg = GetMouseMsg();
			user->move(mousemsg);
		}
		Sleep(5);//放缓游戏节奏，不然容易落地成盒
		for (int i = 0; i < CIRCLECOUNT; i++) {
			if (enermy[i] != NULL) {
				enermy[i]->move();
				int result = versusEnermy(user, enermy[i]);
				if (result == 0) goto outside;
				else if (result == 1) {
					enermy[i] = NULL;
					enermy[i] = newEnermy(user, enermy);
				}
			}
		}
	}
	outside:
	for (int i = 0; i < 4; i++) {
		if(enermy[i] != NULL)
			delete enermy[i];
	}
	cleardevice();
}

bool click(MOUSEMSG mousemsg, LPCTSTR word) {
	//判断鼠标点击的是哪个字符串
	bool result = false;
	short x, y;
	if(word == _T("start")||word == _T("restart")){
		x = STARTX;
		y = STARTY;
	}
	else if (word == _T("exit")) {
		x = EXITX;
		y = EXITY;
	}
	if (mousemsg.x >= x && mousemsg.x <= x + textwidth(word)) {
		if (mousemsg.y >= y && mousemsg.y <= y + textwidth(word)) {
			result = true;
		}
	}
	return result;
}

int main(int argc, char *argv[]) {
	initgraph(graphWidth,graphHeight/*,SHOWCONSOLE/**/);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	cleardevice();
	
	//颜色代码从左到右是BGR
	Circle Circle1(420,125, 50, 0xe22b8a);
	Circle Circle2(380, 125, 25, 0xFFFF);
	LPCTSTR start = _T("start");
	LPCTSTR exit = _T("exit");
	outtextxy(STARTX, STARTY, start);
	outtextxy(EXITX, EXITY, exit);
	struct MOUSEMSG mousemsg;
	while (true) {
		if (MouseHit()) {
			mousemsg = GetMouseMsg();
			if (mousemsg.mkLButton && click(mousemsg, start)) {
				startGame();
				Circle1.draw();
				Circle2.draw();
				start = _T("restart");
				outtextxy(STARTX, STARTY, start);
				outtextxy(EXITX, EXITY, exit);
			}else if (mousemsg.mkLButton && click(mousemsg, exit)) {
				FlushMouseMsgBuffer();
				break;
			}
		}
	}
	FlushMouseMsgBuffer();
	closegraph();
	return 0;
}