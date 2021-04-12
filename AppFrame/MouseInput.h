#pragma once
#include "Dxlib.h"

/*
Process���ɌĂ��GetLeft()�Ȃǂ̊֐����Ă�
Draw���Ă΂Ȃ��ƃo�O��
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

	//�X�N���[�����W�����[���h���W��
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