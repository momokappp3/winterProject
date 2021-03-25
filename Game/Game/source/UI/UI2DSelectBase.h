#pragma once
#include "UI2DBase.h"
#include "../../../../AppFrame/MouseInput.h"
#include <functional>
#include "../../../../AppFrame/Types.h"

/*
画像の範囲にマウスが入っていたら画像を変更する
*/

class UI2DSelectBase : public UI2DBase{
public:
    UI2DSelectBase();
    virtual ~UI2DSelectBase();

    void Draw() override;

};