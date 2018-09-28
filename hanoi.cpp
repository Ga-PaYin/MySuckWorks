#include <iostream>
#include <stack>
#include <windows.h>

using namespace std;
//将塔座x上按直径由小到大自上而下编号为1至0的n个圆盘按规则搬到
//塔座z上，y可用作辅助塔座。
//搬动操作move(x,n,z)
typedef struct tower Tower;
struct tower {
	stack<int> t;
	char name;
	int line;
};
int c = 0;
void gotoxy(int x, int y) {
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
void hide() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}
int m;
void move(Tower *a, int n, Tower *b) {
	if (a->t.top() == n) {
		Sleep(100);
		int line = 0;
		int amount = a->t.size() + 2;
		if (m < 10) {
			gotoxy(amount, a->line);
			cout << "\b ";
		}
		b->t.push(a->t.top());
		a->t.pop();
		line = 0;
		amount = b->t.size() + 2;
		if (m < 10) {
			gotoxy(amount,b->line);
			cout << '\b' << b->t.top();
		}
		c++;
		gotoxy(1, 5);
		cout << "\b\b\b\b" << c;
	}

}

void hanoi(int n, Tower *x, Tower *y, Tower *z) {
	if (n == 1) {
		move(x, 1, z);//将编号为1将编号为1的圆盘从x移到z
	}
	else {
		hanoi(n - 1, x, z, y);//将x上编号为1至n-1的圆盘以到y，z作辅助塔
		move(x, n, z);//将编号为n的圆盘从x移到z
		hanoi(n - 1, y, x, z);//将y上编号为1至n-1的圆盘移到z,x作辅助塔
	}
}
int main(int argc, char const *argv[]) {

	int n;//n为输入的数字。
	cin >> n;
	m = n;
	Tower *x = new Tower, *y = new Tower, *z = new Tower;
	x->name = 'x'; x->line = 1;
	y->name = 'y'; y->line = 2;
	z->name = 'z'; z->line = 3;
	cout << "x:";
	for (int i = n; i >= 1; i--) {
		if (m < 10) cout << i;
		x->t.push(i);
	}
	cout << endl << "y:" << endl << "z:";
	hanoi(n, x, y, z);
	delete x, y, z;
	cout << endl;
	system("pause");
	return 0;
}
