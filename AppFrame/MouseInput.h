#pragma once
#include "Dxlib.h"

/*
Processを先に呼んでGetLeft()などの関数を呼び
Drawを呼ばないとバグる
*/

class MouseInput {
public:
	MouseInput();
	virtual ~MouseInput();

	void Process();
	void LastProcess();
	void Draw();
	void TitleDraw();

	bool GetRight() {
		return _isRight;
	}

	bool GetLeft() {
		return _isLeft;
	}

	bool GetTrgLeft() {
		return _isTrgLeft;
	}

	int GetXNum() {
		return _posX;
	}

	int GetYNum() {
		return _posY;
	}

	//スクリーン座標をワールド座標に
	VECTOR GetStart3D() {
		return _startPosition;
	}

	VECTOR GetEnd3D() {
		return _endPosition;
	}

	void SetEndPosition(VECTOR end) {
		_endPosition = end;
	}

	void SetStartPosition(VECTOR start) {
		_startPosition = start;
	}

private:

	VECTOR _startPosition;
	VECTOR _endPosition;

	bool _isRight;
	bool _isLeft;
	bool _isTrgLeft;

	int _lastLeft;

	int _handle;

	int _posX;
	int _posY;
};