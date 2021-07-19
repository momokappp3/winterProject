#pragma once
#include "source/UI/UI2DBase.h"
#include "source/UI/UI2DSelectBase.h"

class Utility {
public:
    static int ImageHitDetection(int x, int y, UI2DBase* ui2DBase);  //‰æ‘œ‚Ì“–‚½‚è”»’è
    static bool HitRect(int x,int y,Point leftUp,Point rightDown);
};