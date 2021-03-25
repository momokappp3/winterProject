#pragma once

enum class GalGameUIType {

	MenuIinit = 0,
	Menu,
	Setting,
	Story,
	Item,

	Max
};

struct Point {
	int x;
	int y;
};

struct Rect {
	int x;
	int y;
	int w;  //endPosX
	int h;  //endPosY
};

struct DrawInfo {
	int handle;
	Point xy;
	bool isDraw;
	Point startXY;  //�����ʒu��{2000,50}

};