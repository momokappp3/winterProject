#include "PlayerInfo.h"
#include <algorithm>
#include <iostream>

PlayerInfo::PlayerInfo() {

    _favor = 0;
    _molecule = 0;
    _coin = 0;
    _mentalNum = 0;
}

PlayerInfo::~PlayerInfo(){
}

void PlayerInfo::Process(){

    //クランプの処理できてない？？×
    //std::clamp(_favor, 0, 99);
    std::clamp(_molecule, 0, 99);
    std::clamp(_coin, 0, 999999);
    std::clamp(_mentalNum, 0, 100);
}