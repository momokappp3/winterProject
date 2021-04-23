#include "MentalGauge.h"

MentalGauge::MentalGauge() {

    _mental = -1;
    _minMental = 0;
    _maxMental = 0;

	_maxStart = false;
}

MentalGauge::~MentalGauge() {
}

void MentalGauge::Process() {

	if (_pTween->IsStart()) {
		_nowRate = _pTween->GetPosition().x;
		GetGaugeArea();
	}

	if (_pTween->IsEnd()) {
		GetGaugeArea();
		_pTween->Reset();
		_lastRate = _rate;

		if (_maxStart) {
			_pTween->SetTween({ _maxMental,0 }, { _minMental,0 }, _tweenFrame, Tween::Type::SineStart);
			_maxStart = false;
		}
		else {
			_pTween->SetTween({ _minMental,0 }, { _maxMental,0 }, _tweenFrame, Tween::Type::SineStart);
			_maxStart = true;
		}
	}

	_pTween->Process();
}

bool MentalGauge::SetRate(int num){

	//¡‚Ìƒƒ“ƒ^ƒ‹’l‚ª“ü‚Á‚Ä‚­‚é‚Ì‚Å
	_minMental = num - 5;
	_maxMental = num + 5;

	if (_maxMental > 100) {
		_maxMental = 100;
	}

	if (_minMental < 0) {
		_minMental = 0;
	}

	_pTween->SetTween({ _minMental,0}, { _maxMental,0}, _tweenFrame,Tween::Type::SineEnd);
	_maxStart = true;

	return true;
}