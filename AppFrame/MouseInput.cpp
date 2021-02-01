#include "MouseInput.h"
#include "DxLib.h"

MouseInput::MouseInput() {
	SetMouseDispFlag(TRUE);

	_isRight = false;
	_isLeft = false;

	_posX = 0;
	_posY = 0;
}

MouseInput::~MouseInput() {
}

void MouseInput::Process(){

	//マウスポインタの座標を取得
	GetMousePoint(&_posX, &_posY);

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		_isRight = true;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		_isLeft = true;
	}
}

void MouseInput::Draw() {
	DrawFormatString(20, 20, GetColor(255,255,255), "マウスの座標( %d, %d )", _posX, _posY);

	if (_isRight) {
		DrawString(20, 80, "マウス右ボタンが押されています", GetColor(255, 165, 0));
	}

	if (_isLeft) {
		DrawString(20, 50, "マウス左ボタンが押されています", GetColor(255, 165, 0));
	}

	_isRight = false;
	_isLeft = false;
}
