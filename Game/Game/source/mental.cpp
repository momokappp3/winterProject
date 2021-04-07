#include "mental.h"

Mental::Mental() {

    _pMentalTween = nullptr;
    _pBarRedBase = nullptr;

    _mental = -1;
    _minMental = 0;
    _maxMental = 0;
}

Mental::~Mental() {
}

bool Mental::Init() {
    _pMentalTween.reset(new Tween);
    _pBarRedBase.reset(new UIGauge);




    return false;
}

void Mental::Process() {

    //_pBarRedBase->SetRate();

    

    _pBarRedBase->Process();
    _pMentalTween->Process();
}

void Mental::Draw() {
    _pBarRedBase->Draw();
}