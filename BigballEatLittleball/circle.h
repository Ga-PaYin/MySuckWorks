#include <easyx.h>
#include<cmath>
#define graphWidth 800
#define graphHeight 500
#define STARTX 380
#define STARTY 250
#define EXITX 380
#define EXITY 300
#define ORIGINALR 10
#define CIRCLECOUNT 5
#define MAX 100
#pragma once
class Circle
{
private:
	friend class myCircle;
	int radius, x, y, color,dx,dy;
public:
	Circle(int X,int Y,int R,int Color);
	Circle(int X, int Y, int R, int Color, int dX, int dY);
	~Circle();
	int getRadius();
	void draw();
	void move();
	int getX();
	int getY();
};

class myCircle:public Circle {
private:
	int Max;
public:
	myCircle(int X, int Y, int R, int Color, int Maxsize);
	void resize();
	void move( MOUSEMSG mousemsg);
	int getMax();
};