#include "UI2DBase.h"
#include "Dxlib.h"

UI2DBase::UI2DBase() {

	_vDrawInfo.clear();
	_selectType = SelectType::Max;

	_start = { 0,0 };
	_end = { 0,0 };

	_select = 0;
	_radius = 0;
}

UI2DBase::~UI2DBase() {
}

bool UI2DBase::Init() {
	return true;
}

void UI2DBase::Process() {
}

bool UI2DBase::GetDrawInfo(int index, DrawInfo& info) {

	if (_vDrawInfo.size() == 0 || index < 0 || index >= _vDrawInfo.size()) {
		return false;
	}

	info = _vDrawInfo[index];
	return true;
}

void UI2DBase::Draw() {

	for (DrawInfo info : _vDrawInfo) {    //�x�N�^�[�̒��g����񂪓����čŌ�܂ŏ���
		if (!info.isDraw) {
			continue;
		}

		DrawGraph(info.xy.x, info.xy.y, info.handle, TRUE);
	}
}

Point UI2DBase::GetCenter() {

	if (_vDrawInfo.size() == 0) {
		return { 0,0 };
	}

	DrawInfo info = _vDrawInfo[0];

	int x,y;

	if (GetGraphSize(info.handle, &x, &y) == -1) {
		return { 0,0 };
	}

	return { info.xy.x + x / 2 ,info.xy.y + y / 2 };
}