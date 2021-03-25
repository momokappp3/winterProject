#include "UI2DSelectBase.h"

UI2DSelectBase::UI2DSelectBase() :UI2DBase() {
}

UI2DSelectBase::~UI2DSelectBase() {
}

void UI2DSelectBase::Draw() {

	if (_vDrawInfo.size() == 0 || _select < 0 || _select >= _vDrawInfo.size()) {
		return;
	}

	DrawInfo info = _vDrawInfo[_select];

	DrawGraph(info.xy.x, info.xy.y, info.handle, TRUE);
}