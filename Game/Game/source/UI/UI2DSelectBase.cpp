#include "UI2DSelectBase.h"

UI2DSelectBase::UI2DSelectBase() :UI2DBase() {

	_lastSelect = -1;

	_onSelect = nullptr;
}

UI2DSelectBase::~UI2DSelectBase() {
}

void UI2DSelectBase::Process() {

	if (_lastSelect == 0 && _select == 1) {
		if (_onSelect != nullptr) {
			_onSelect();
		}
	}

	_lastSelect = _select;
}

void UI2DSelectBase::Draw() {

	if (_vDrawInfo.size() == 0 || _select < 0 || _select >= _vDrawInfo.size()) {
		return;
	}

	for (DrawInfo info : _vDrawInfo) {    //�x�N�^�[�̒��g����񂪓����čŌ�܂ŏ���
		if (!info.isDraw) {
			return;
		}
	}

	DrawInfo info = _vDrawInfo[_select];

	DrawGraph(info.xy.x, info.xy.y, info.handle, TRUE);
}