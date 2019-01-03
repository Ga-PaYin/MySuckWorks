#include "circle.h"
#include<easyx.h>

//Circle 定义区******************************
Circle::Circle(int X,int Y,int R,int Color):
	x(X),y(Y),radius(R),color(Color){
	draw();
}
Circle::Circle(int X, int Y, int R, int Color, int dX, int dY) :
	x(X), y(Y), radius(R), color(Color), dx(dX), dy(dY) {
	draw();
}
Circle::~Circle(){
	clearcircle(x, y, radius);
}
void Circle::draw() {
	setfillcolor(color);
	solidcircle(x, y, radius);
}
int Circle::getRadius() {
	return radius;
}
int Circle::getX() {
	return x;
}
int Circle::getY() {
	return y;
}
void Circle::move(){
	clearcircle(x, y, radius);
	if (x + radius >= graphWidth || x - radius <= 0) {
		dx = -dx;
	}
	if (y + radius >= graphHeight || y - radius <= 0) {
		dy = -dy;
	}
	x += dx;
	y += dy;
	draw();
}
//*******************************************

//myCircle 定义区*****************************
myCircle::myCircle(int X, int Y, int R, int Color,int Maxsize) :
	Circle(X, Y, R, Color),Max(Maxsize){}
void myCircle::resize() {
	if (radius < 50) {
		clearcircle(x, y, radius);
		radius += 1;
		draw();
	}
}
void myCircle::move(MOUSEMSG mousemsg) {
	clearcircle(x,y,radius);
	x = mousemsg.x;
	y = mousemsg.y;
	draw();
}
int myCircle::getMax() {
	return Max;
}
//**********************************************