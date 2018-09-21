#include<iostream>
#include<Windows.h>
#include<stdlib.h>
#include<ctime>
#include<conio.h>
#include<iomanip>
#include<stdio.h>
#define N 20
using namespace std;
void gotoxy(int x, int y){
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
void hide(){
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}
//定义场地
char chess[N + 2][N + 2];
//定义链表
class snake {
public:
	int x, y;
	snake *Next;
	snake() {}
	snake(snake *p) {
		x = p->x;
		y = p->y;
		Next = new snake;
		*Next = *(p->Next);
	}
}*snake1;
//定义食物
struct possition {
	int x, y, score1;
}food;
//生成蛇所用函数
snake *Node(int valueX,int valueY) {
	static snake *head, *tail;
	tail = NULL;
	head = new snake;
	head->x = valueX;
	head->y = valueY;
	head->Next = tail;
	tail = head;
	return head;
}
//食物有没有生成在蛇身上
bool samePoint() {
	snake *snakeCheck = snake1;
	while (snakeCheck->Next != NULL) {
		if (food.x == snakeCheck->x&&food.y == snakeCheck->y) return true;
		snakeCheck = snakeCheck->Next;
	}
	if (food.x == snakeCheck->x&&food.y == snakeCheck->y) return true;
	if (chess[food.x][food.y] == '#') return true;
	return false;
}
bool Eat() {
	if (food.x == snake1->x&&food.y == snake1->y) return true;
	else return false;
}
//生成食物
void Food() {
	snake *snake3 = snake1;
	srand((unsigned)time(NULL));
	do {
		food.x = rand() % N+2;
		food.y = rand() % N+2;
		food.score1 = rand() % 5;
	} while (samePoint());
}
//删除蛇
void delete_(snake *snake5) {
	snake *dlt, *p1 = snake5;
	while (p1->Next != NULL) {
		dlt = p1;
		p1 = p1->Next;
		delete dlt;
	}
	delete p1;
}
//让蛇动起来
void go(char direction) {
	int x, y;
	switch (direction) {
		case 'W':
		case 'w': {
			x = snake1->x;
			y = snake1->y - 1;
			break;
		}
		case 'A':
		case 'a': {
			x = snake1->x - 1;
			y = snake1->y;
			break;
		}
		case 'S':
		case 's': {
			x = snake1->x;
			y = snake1->y + 1;
			break;
		}
		case 'D':
		case 'd': {
			x = snake1->x+1;
			y = snake1->y;
			break;
		}
	}
	snake *p=Node(x,y);
	p->Next = snake1;
	snake1 = p;
	if (!Eat()) {
		while (p->Next != NULL) {
			p = p->Next;
		}
		snake *p2=snake1;
		while (p2->Next != p) {
			p2 = p2->Next;
		}
		p2->Next = NULL;
		delete p;
	}
	snake *p1 = snake1->Next;
	switch (direction) {
		case 'W':
		case 'w': {
			snake1->x = p1->x;
			snake1->y = p1->y - 1;
			break;
		}
		case 'A':
		case 'a': {
			snake1->x = p1->x - 1;
			snake1->y = p1->y;
			break;
		}
		case 'S':
		case 's': {
			snake1->x = p1->x;
			snake1->y = p1->y + 1;
			break;
		}
		case 'D':
		case 'd': {
			snake1->x = p1->x + 1;
			snake1->y = p1->y;
			break;
		}	
	}
}
//蛇还活着吗??
bool Die() {
	if (snake1->x == 0 || snake1->x == N+1) return true;
	if (snake1->y == 0 || snake1->y == N+1) return true;
	snake *p = snake1->Next;
	for (; p->Next != NULL; p = p->Next) {
		if (p->x == snake1->x&&p->y==snake1->y) return true;
	}
	return false;
}
//main函数
int main() {
//打开关于最高分的文件
	FILE *fp;
	if ((fp = fopen("C:\\Users\\10990\\Desktop\\coding\\贪吃蛇\\highest.txt", "rt+")) == NULL) {
		cout << "sth wrong,fail to start the game" << endl;
		exit(0);
	}
	int highest=0;
	int *hst=&highest;
	fscanf(fp, "%d", &highest);
//初始化场地
	int i, j;
	memset(chess, ' ', (N + 2)*(N + 2));
	for (i = 0; i < N + 2; i++) {
		chess[0][i] = '#';
		chess[N + 1][i] = '#';
		chess[i][0] = '#';
		chess[i][N + 1] = '#';
	}
//定义蛇
	snake *snake2 = NULL;
	for (i = 0; i < 5; i++){
		if (i == 0) {
			snake2 = Node(5, 1);
			snake1 = snake2;
		}
		else {
			snake2->Next = Node(5 - i, 1);
			snake2 = snake2->Next;
		}
	}
//输出snake1的链表
	snake *snake3 = snake1;
//定义操作，并设计积分
	char control = 'd';
	int score=0;
//生成食物
	Food();
//蛇皮操作
	int speed=500;
//输出棋盘和成绩
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_GREEN);
	for (snake3 = snake1; snake3->Next != NULL; snake3 = snake3->Next) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				if (snake3->x == j&&snake3->y == i) {
					chess[i][j] = '*';
					break;
				}
				else {
					chess[i][j] = ' ';
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN|FOREGROUND_BLUE);
			if (food.x == j&&food.y == i && !Eat()) {
				if (food.score1 > 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
					chess[i][j] = '$';
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
					chess[i][j] = '$';
				}
			}
			else if (Eat()) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); 
				chess[i][j] = '*';
			}
		}
	}
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (snake3->x == j&&snake3->y == i) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); 
				chess[i][j] = '*';
				break;
			}
			else {
				chess[i][j] = ' ';
			}
		}
	}
	for (i = 0; i < N + 2; i++) {
		for (j = 0; j < N + 2; j++) {
			if (chess[i][j] == '*') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			}
			cout << chess[i][j];
		}
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
	cout << "score=" << score << endl;
	cout<<"best="<<highest<<endl;
	while (!Die()) {
		hide();
		if (_kbhit()) control = _getch();
		go(control);

		if (Eat()) {
			Food();
			score++;
			if (food.score1 == 0) score++;
			gotoxy(8, N + 2);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN);
			cout << "\b\b" << setw(3)<<score;
		}
		if (score >= 5) speed = 300;
		if (score >= 10)speed = 100;
		if (score >= 20)speed = 50;
		gotoxy(food.x, food.y);
		if (food.score1 > 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
			cout << '\b' << '$';
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << '\b' << '$';
		}
		gotoxy(snake1->x, snake1->y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		cout << '\b' << '*';
		for (snake3 = snake1; snake3->Next != NULL; snake3 = snake3->Next);
		gotoxy(snake3->x, snake3->y);
		cout << '\b' << ' ';
		Sleep(speed);		
	}
	if (score > highest){
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d", score);
	}
//游戏结束后的善后工作
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	system("cls");
	for (i = 0; i < N + 2; i++) {
		for (j = 0; j < N + 2; j++) {
			if (chess[i][j] == '*' || chess[i][j] == '$') chess[i][j] = ' ';
			cout << chess[i][j];
		}
		cout << endl;
	}
	delete_(snake1);
	fclose(fp);
	system("pause");
	return 0;
}