#pragma once
#include <String>
#include < tchar.h>

enum class RoomGameUIType {

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

struct PopString {

	std::string string;
	Point xy;
	bool isDraw;

};

struct FaceInfo {

	int faceNum;
	float min;
	float max;
	int tweenFrame;
	int stopTime;
	int delay;
};