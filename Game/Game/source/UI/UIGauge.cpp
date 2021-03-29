#include "UIGauge.h"
#include <cmath>
#include "Dxlib.h"

UIGauge::UIGauge() :UI2DBase(){

    _pTween = nullptr;

	_point = { 0,0 };
	_leftUp = { 0,0 };
	_rightDown = { 0,0 };

	_imageWidth = 0;
	_imageHeight = 0;

	_tweenFrame = 30;

	_rate = 0;
	_nowRate = 0;
	_nextRate = 0;
}

UIGauge::~UIGauge() {
}

bool UIGauge::Init(int frame) {

	if (GetGraphSize(_vDrawInfo[1].handle, &_imageWidth, &_imageHeight) == -1) {
		return false;
	}

	_tweenFrame = frame;

	_pTween.reset(new Tween);

	_point = UI2DBase::GetPoint();
	_rightDown = _point;
	//_rightDown.x += _imageWidth;  //Max
	_rightDown.y += _imageHeight;

	return true;
}

void UIGauge::Process() {

	_pTween->Process();

	_point = UI2DBase::GetPoint();
	
	if (_pTween->IsStart()) {
		_rightDown = _pTween->GetPosition();
	}

	if (_pTween->IsEnd()) {
		_nowRate = _nextRate;
	}
}

void UIGauge::GetGaugeArea(int rate, int& rightDownX) {

	float _rate = static_cast<float>(rate) / 100.0f;  //Šù‚É0.5
	int width = static_cast<int>(_imageWidth * _rate);

	rightDownX = _point.x + width;
}

/*
void Hp::GetHpArea(int hp, Point& rightDown) {

	int hpPixel = _imageWidth - Parameter::_HpImageMarginLeft - Parameter::_HpImageMarginRight;

	float rate = static_cast<float>(hp) / static_cast<float>(_hp);
	float hpRate = std::round(static_cast<float>(hpPixel) * rate);
	int nowHp = static_cast<int>(hpRate);

	rightDown = _leftUp;
	rightDown.x += nowHp;
	rightDown.y += _imageHeight;

}

*/

void UIGauge::Draw() {

	DrawGraph(_point.x, _point.y, UI2DBase::_vDrawInfo[0].handle, TRUE);
	SetDrawArea(_point.x, _point.y, _rightDown.x, _rightDown.y);
	DrawGraph(_point.x, _point.y, UI2DBase::_vDrawInfo[1].handle, TRUE);
	SetDrawArea(0, 0, 1920, 1080);  //•`‰æ”ÍˆÍ‚ð–ß‚·
}

bool UIGauge::SetRate(int rate) {

	if (_pTween == nullptr || rate < 0 || rate > 100) {
		return false;
	}

	_nextRate = rate;

	int nextWidth = 0;

	GetGaugeArea(_nextRate, nextWidth);

	int nowWidth = 0;

	GetGaugeArea(_nowRate, nowWidth);

	_pTween->Reset();
	_pTween->SetTween({ nowWidth,0 }, { nextWidth ,0 }, _tweenFrame, Tween::Type::SineStart);

	return true;
}