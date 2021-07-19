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
	_isEndNow = false;

	_pTimeBase = nullptr;
    _pUINumber = nullptr;
	_pBaseInAndOut = nullptr;
	_pNumInAndOut = nullptr;

    _maxNum = 0;
}

UITime:: ~UITime() {
}

bool UITime::Init(int maxNum ,int digit) {

    _maxNum = maxNum;

    _pUINumber.reset(new UINumber);
	_pTimeBase.reset(new UI2DBase);
	_pBaseInAndOut.reset(new UIInAndOut);
	_pNumInAndOut.reset(new UIInAndOut);

	if (!_pBaseInAndOut->Init() || !_pNumInAndOut->Init()) {
		return false;
	}

	int handle = ResourceServer::LoadGraph("png/RoomUI/numBase.png");

	if (handle == -1) {
		return false;
	}

	DrawInfo info = { handle,180,195,true,{-350,470} };

	_pTimeBase->SetDrawInfo(info);

	std::array<int, 10> trustHandle{
	ResourceServer::LoadGraph("png/RoomUI/number/trust0.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust1.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust2.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust3.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust4.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust5.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust6.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust7.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust8.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust9.png"),
	};
	
	for (int i = 0; i < 10; i++) {
		info = { trustHandle[i] ,300,270,true,-350,620};

		_pUINumber->SetDrawInfo(info);
	}
	
	_pUINumber->SetPoint({ 300,270 });

	_pUINumber->Init(digit);

	DrawInfo infoInit;
	_pTimeBase->GetDrawInfo(0, infoInit);
	_pBaseInAndOut->SetStartPosition(infoInit.startXY);
	_pBaseInAndOut->SetEndPosition(infoInit.xy);
	_pBaseInAndOut->SetNowPosition(infoInit.startXY);

	_pUINumber->GetDrawInfo(0, infoInit);
	_pNumInAndOut->SetStartPosition(infoInit.startXY);
	_pNumInAndOut->SetEndPosition(infoInit.xy);
	_pNumInAndOut->SetNowPosition(infoInit.startXY);

	return true;
}

void UITime::Process() {

	_pTimeBase->SetPoint(0, _pBaseInAndOut->GetNowPosition());
	_pUINumber->SetPoint(_pNumInAndOut->GetNowPosition());

	_pTimeBase->Process();
	_pUINumber->Process();
	_pBaseInAndOut->Process();
	_pNumInAndOut->Process();

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
			_isEndNow = true;

			//êŠ‚ð“®‚©‚·‚µ‚Ü‚¤ˆ—
			_pBaseInAndOut->SetIsEnd(true);
			_pNumInAndOut->SetIsEnd(true);
		}

		_pUINumber->SetNum(_nowNum);
	}
	/*
	if (_isEnd) {
		_isEndNow = true;
	}
	*/
}

void UITime::Draw() {
	_pTimeBase->Draw();
    _pUINumber->Draw();
	_isEndNow = false;
}

void UITime::SetStart(int startNum) {

	_isStart = true;
	_isEnd = false;
	_isStop = false;

	_startNum = startNum;
	_nowNum = startNum;

	_startTime = GetNowCount();  //‹N“®‚µ‚Ä‚©‚ç‚Ç‚ê‚­‚ç‚¢‚½‚Á‚½‚©

	_pUINumber->SetNum(startNum);

	//êŠ‚ð“®‚©‚·ˆ—
	_pBaseInAndOut->SetIsStart(true);
	_pNumInAndOut->SetIsStart(true);
}