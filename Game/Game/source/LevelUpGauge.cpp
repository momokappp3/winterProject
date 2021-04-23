#include "LevelUpGauge.h"

LevelUpGauge::LevelUpGauge() {
	_loopNum = 0;
	_isLoop = false;
}

LevelUpGauge::~LevelUpGauge() {
}

void LevelUpGauge::Process() {

	if (_pTween->IsStart()) {
		_nowRate = _pTween->GetPosition().x;
		GetGaugeArea();
	}

	if (_pTween->IsEnd()) {
		GetGaugeArea();
		_pTween->Reset();
		_lastRate = _rate;

		if (_isLoop) {
			if (_loopNum > 0) {
				SetRate(100);
				_loopNum--;
			}
			else if (_loopNum == 0) {
				SetRate(_rate);
			}
		}
	}

	_pTween->Process();
}

bool LevelUpGauge::SetRate(int rate) {  //1�񂾂������ƌĂ�ł���ƈ�u�œ���

	if (!_isLoop) {
		if (_pTween == nullptr || rate < 0 || rate > 100) {
			return false;
		}

		_lastRate = _rate;  //���̃��[�g������
		_rate = rate;

		_pTween->SetTween({ _lastRate,0 }, { _rate ,0 }, _tweenFrame, Tween::Type::SineStart);
	}
	else {
		_lastRate = 100;  //���̃��[�g������
		_rate = 100;
		_pTween->SetTween({ _lastRate,0 }, { _rate ,0 }, _tweenFrame, Tween::Type::SineStart);
	}

	return true;
}