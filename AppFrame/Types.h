#pragma once
#include <String>
#include < tchar.h>

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
	Point startXY;  //‰ŠúˆÊ’u—á{2000,50}

};

struct PopString {

	std::string string;
	Point xy;
	bool isDraw;

};