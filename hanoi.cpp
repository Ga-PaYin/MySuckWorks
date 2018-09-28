#include <iostream>
#include <stack>
#include <windows.h>

using namespace std;
//������x�ϰ�ֱ����С�������϶��±��Ϊ1��0��n��Բ�̰�����ᵽ
//����z�ϣ�y����������������
//�ᶯ����move(x,n,z)
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
		move(x, 1, z);//�����Ϊ1�����Ϊ1��Բ�̴�x�Ƶ�z
	}
	else {
		hanoi(n - 1, x, z, y);//��x�ϱ��Ϊ1��n-1��Բ���Ե�y��z��������
		move(x, n, z);//�����Ϊn��Բ�̴�x�Ƶ�z
		hanoi(n - 1, y, x, z);//��y�ϱ��Ϊ1��n-1��Բ���Ƶ�z,x��������
	}
}
int main(int argc, char const *argv[]) {

	int n;//nΪ��������֡�
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
