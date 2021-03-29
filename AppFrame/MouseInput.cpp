#include "MouseInput.h"
#include "DxLib.h"
#include "../Game/Game/ResourceServer.h"

MouseInput::MouseInput() {

	SetMouseDispFlag(TRUE);

	_startPosition = { 0,0,0 };
	_endPosition = { 0,0,0 };

	_isRight = false;
	_isLeft = false;

	_handle = ResourceServer::LoadGraph("png/arrow_cursor.png");

	_posX = 0;
	_posY = 0;
}

MouseInput::~MouseInput() {
}

void MouseInput::Process(){

	//�}�E�X�|�C���^�̍��W���擾
	GetMousePoint(&_posX, &_posY);

	// �}�E�X�|�C���^�������ʏ�̍��W�ɊY������R�c��ԏ�� Near �ʂ̍��W���擾
	_startPosition = ConvScreenPosToWorldPos(VGet(_posX, _posY, 0.0f));

	// �}�E�X�|�C���^�������ʏ�̍��W�ɊY������R�c��ԏ�� Far �ʂ̍��W���擾
	_endPosition = ConvScreenPosToWorldPos(VGet(_posX, _posY, 1.0f));


	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		_isRight = true;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		_isLeft = true;
	}
}

void MouseInput::Draw() {

	DrawGraph(_posX, _posY,_handle, TRUE);

	DrawFormatString(20, 500, GetColor(255, 255, 255), "�}�E�X�̍��W( %d, %d )", _posX, _posY);

	if (_isRight) {
		DrawString(20, 580, "�}�E�X�E�{�^����������Ă��܂�", GetColor(255, 165, 0));
	}

	if (_isLeft) {
		DrawString(20, 550, "�}�E�X���{�^����������Ă��܂�", GetColor(255, 165, 0));
	}

	_isRight = false;
	_isLeft = false;

}

void MouseInput::TitleDraw() {

	//DrawFormatString(20, 500, GetColor(255, 255, 255), "�}�E�X�̍��W( %d, %d )", _posX, _posY);

	if (_isRight) {
		//DrawString(20, 580, "�}�E�X�E�{�^����������Ă��܂�", GetColor(255, 165, 0));
	}

	if (_isLeft) {
		//DrawString(20, 550, "�}�E�X���{�^����������Ă��܂�", GetColor(255, 165, 0));
	}

	_isRight = false;
	_isLeft = false;
}