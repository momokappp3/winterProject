#include "UINumber.h"
#include "DxLib.h"

UINumber::UINumber() :UI2DBase() {

	_vNumHandle.clear();

	_point = { 0,0 };

	_num = 0;
	_digitMax = 0;

}

UINumber::~UINumber() {

}

bool UINumber::Init(int digitMax) {
	//�K��reutrn true����O�ɂ��
	_digitMax = digitMax;

	SetNumHandle(0);

	return true;
}

void UINumber::Process() {

	SetNumHandle(_num);
}


void UINumber::Draw() {

	//�����o��_point�̓��j���[�̓����Ŏg��
	Point point = _point;

	for (int i = 0; i < _digitMax; i++) {
		if (i != 0) {

			int x = 0, y =0;

			GetGraphSize(_vNumHandle[i - 1], &x, &y);

			point.x -= x; //�O�̉摜�̕��𑫂�
		}

		DrawGraph(point.x, point.y, _vNumHandle[i], TRUE);
	}
	_vNumHandle.clear();
}

void UINumber::SetNumberPoint(Point point) {
	_point = point;
}

bool UINumber::SetNumHandle(int num) {

	int maxNum = 1;

	for (int i = 0; i < _digitMax;i++) {
		maxNum *= 10;
	}

	maxNum -= 1;

	if (num < 0 || num > maxNum) {
		return false;
	}

	for (int i = 0; i < _digitMax; i++) {

		int mod = num % 10; // �]�肪��̈� �Ō�̌�

		num = num / 10; // �擾�ς݂̗]���"num"���珜��

		int handle = UI2DBase::GetHandle(mod);// _vDrawInfo[mod].handle;  //���̃n���h�������o��

		_vNumHandle.push_back(handle);  //�n���h���������Ă���  
										//[6]�̈ʒu�Ɉ�̈ʂ������Ă���
	}
}