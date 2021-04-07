#include "UI2DSelectBase.h"

UI2DSelectBase::UI2DSelectBase() :UI2DBase() {
	//_pSoundManager = nullptr;
	_lastSelect = -1;

	_onSelect = nullptr;
}

UI2DSelectBase::~UI2DSelectBase() {
}
/*
bool UI2DSelectBase::Init(std::shared_ptr<SoundManager> soundManager) {

	if (soundManager != nullptr) {
		bool seTitle = soundManager->LoadSECommon();

		if (!seTitle) {
			return false;
		}
	}
	else {
		return false;
	}

	_pSoundManager = soundManager;
}

void UI2DSelectBase::Process() {

	if (_select && !_lastSelect) {
		_pSoundManager->PlaySECommon(SoundManager::SECommon::Select);
		_lastSelect = false;
	}
}
*/


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

	for (DrawInfo info : _vDrawInfo) {    //ベクターの中身が情報が入って最後まで処理
		if (!info.isDraw) {
			return;
		}
	}

	DrawInfo info = _vDrawInfo[_select];

	DrawGraph(info.xy.x, info.xy.y, info.handle, TRUE);
}