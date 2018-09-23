#include <iostream>
#include <stack>
#include <queue>
#include <Windows.h>
using namespace std;
int main() {
	//����
	char BinTree[] = {'0','A',
		'B','C',
		'D','E','F','G',
		'0','H','I','0','J','K','0','L',
		'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
	//����ջ
	stack<int> Stack;
	//�������
	cout << "�������" << endl;
	int i = 1;
	while (i <= 15 || !Stack.empty()) {
		while (BinTree[i] != '0') {
			Stack.push(i);
			i = 2 * i;
		}
		
		if (!Stack.empty()) {
			i = Stack.top();
			cout << BinTree[Stack.top()];
			Stack.pop();
			i = 2 * i + 1;
		}
	}
	cout << endl;
	while (!Stack.empty()) {
		Stack.pop();
	}
	//�������
	cout << "�������" << endl;
	i = 1;
	while (i <= 15 || !Stack.empty()) {
		while (BinTree[i] != '0') {
			cout << BinTree[i];
			Stack.push(i);
			i = 2 * i;
		}
		if (!Stack.empty()) {
			i = Stack.top() * 2 + 1;
			Stack.pop();
		}
	}
	while (!Stack.empty()) {
		Stack.pop();
	}
	cout << endl;
	//�������
	cout << "�������" << endl;
	i = 1;
	int r = 0;//r��������ʹ��Ľڵ���±�
	while (i>0||!Stack.empty()) {
		if (BinTree[i] != '0') {
			Stack.push(i);
			i = i * 2;
		}
		else {
			i = Stack.top();
			if (BinTree[i * 2 + 1] != '0' && r != i * 2 + 1) {
				i = i * 2 + 1;
			}
			else {
				cout << BinTree[Stack.top()];
				Stack.pop();
				r = i;
				i = 0;
			}
		}
	}
	cout << endl;
	//�������
	cout << "�������" << endl;
	queue<int> Queue;
	i = 1;
	while (!Queue.empty() || i <= 15) {
		cout << BinTree[i];
		if (BinTree[i * 2] != '0') {
			Queue.push(i * 2);
		}
		if (BinTree[i * 2 + 1] != '0') {
			Queue.push(i * 2 + 1);
		}
		if (!Queue.empty()) {
			i = Queue.front();
			Queue.pop();
		}
		else {
			break;
		}
	}
	cout << endl;
	system("pause");
	return 0;
}