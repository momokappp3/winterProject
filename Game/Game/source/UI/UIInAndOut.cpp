#include "UIInAndOut.h"

UIInAndOut::UIInAndOut() {

	_start = { 0,0 };
	_end = { 0,0 };
	_now = { 0,0 };

	_isStart = false;
	_isEnd = false;

    _pTween = nullptr;
}

UIInAndOut::~UIInAndOut() {
}

bool UIInAndOut::Init() {
    _pTween.reset(new Tween);

	return true;
}

void UIInAndOut::Process() {

	if (_isStart) {
		_pTween->SetTween({ _start.x,_start.y }, { _end.x,_end.y }, 100, Tween::Type::SineStart);
		_isStart = false;
	}

	if (_isEnd) {
		_pTween->SetTween({ _end.x,_end.y }, { _start.x,_start.y }, 40, Tween::Type::SineEnd);
		_isEnd = false;
	}

	if (_pTween->IsStart()) {
		_now = _pTween->GetPosition();
	}

	_pTween->Process();
}