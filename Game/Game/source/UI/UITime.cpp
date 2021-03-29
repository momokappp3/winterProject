#include "UITime.h"
#include "../../ResourceServer.h"
#include <array>
#include "DxLib.h"

UITime::UITime() {

	_startTime = 0;
	_startNum = 0;
	_nowNum = 0;

	_isStart = false;
	_isStop = false;
	_isEnd = false;

	_pTimeBase = nullptr;
    _pUINumber = nullptr;
    _maxNum = 0;
}

UITime:: ~UITime() {
}

bool UITime::Init(int maxNum ,int digit) {

    _maxNum = maxNum;

    _pUINumber.reset(new UINumber);
	_pTimeBase.reset(new UI2DBase);

	int handle = ResourceServer::LoadGraph("png/galUI/numBase.png");

	if (handle == -1) {
		return false;
	}

	DrawInfo info = { handle,1590,620,true};

	_pTimeBase->SetDrawInfo(info);

	std::array<int, 10> trustHandle{
	ResourceServer::LoadGraph("png/galUI/number/trust0.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust1.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust2.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust3.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust4.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust5.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust6.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust7.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust8.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust9.png"),
	};

	//êîéöÇÃà íuÇÕSetÇ≈Ç∑ÇÈ
	
	for (int i = 0; i < 10; i++) {
		info = { trustHandle[i] ,1715,695,true,};

		_pUINumber->SetDrawInfo(info);
	}
	
	_pUINumber->SetNumberPoint({ 1715,695 });

	_pUINumber->Init(2);

	return true;
}

void UITime::Process() {

	if (!_isStart || _isEnd || _isStop) {
		return;
	}

	int nowTime = GetNowCount() - _startTime;
	int nowSecond = nowTime / 1000;
	int nowNum = _startNum - nowSecond;

	if (_nowNum != nowNum) {
		_nowNum = nowNum;

		if (_nowNum < 0) {
			_nowNum = 0;
		}

		if (_nowNum == 0) {
			_isEnd = true;
		}

		_pUINumber->SetNum(_nowNum);
	}

	_pTimeBase->Process();
    _pUINumber->Process();
}

void UITime::Draw() {
	_pTimeBase->Draw();
    _pUINumber->Draw();
}

void UITime::SetStart(int startNum) {

	_isStart = true;
	_isEnd = false;
	_isStop = false;

	_startNum = startNum;
	_nowNum = startNum;

	_startTime = GetNowCount();  //ãNìÆÇµÇƒÇ©ÇÁÇ«ÇÍÇ≠ÇÁÇ¢ÇΩÇ¡ÇΩÇ©

	_pUINumber->SetNum(startNum);
}


/*
bool UITime::SetNumber(int num) {
	_pUINumber->SetNum(num);
}

*/