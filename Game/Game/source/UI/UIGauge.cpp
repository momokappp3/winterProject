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

	_lastRate = 0;
	_rate = 0;
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
	//_rightDown.x += _imageWidth;  //Max‚Å‰Šú‰»
	_rightDown.y += _imageHeight;

	return true;
}

void UIGauge::Process() {

	if (_pTween->IsStart()) {
		_nowRate = _pTween->GetPosition().x;
		GetGaugeArea();
	}

	if (_pTween->IsEnd()) {
		GetGaugeArea();
		_pTween->Reset();
		_lastRate = _rate;
	}

	_pTween->Process();
}

void UIGauge::GetGaugeArea() {

	float rate = static_cast<float>(_nowRate) / 100.0f;
	int width = static_cast<int>(_imageWidth * rate);

	_rightDown.x = _point.x + width;
}

void UIGauge::Draw() {

	_point = UI2DBase::GetPoint();

	DrawGraph(_point.x, _point.y, UI2DBase::_vDrawInfo[0].handle, TRUE);
	SetDrawArea(_point.x, _point.y, _rightDown.x, _rightDown.y);
	DrawGraph(_point.x, _point.y, UI2DBase::_vDrawInfo[1].handle, TRUE);
	SetDrawArea(0, 0, 1920, 1080);  //•`‰æ”ÍˆÍ‚ğ–ß‚·
}

bool UIGauge::SetRate(int rate) {  //1‰ñ‚¾‚¯‚¸‚Á‚ÆŒÄ‚ñ‚Å‚¢‚é‚Æˆêu‚Å“ü‚é

	if (_pTween == nullptr || rate < 0 || rate > 100) {
		return false;
	}

	_lastRate = _rate;  //¡‚ÌƒŒ[ƒg‚ğ“ü‚ê‚é
	_rate = rate;

	_pTween->SetTween({ _lastRate,0 }, { _rate ,0}, _tweenFrame, Tween::Type::SineStart);

	return true;
}