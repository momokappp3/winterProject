#pragma once
#include "UI2DBase.h"
#include "../../../../AppFrame/MouseInput.h"
#include <functional>
#include "../../../../AppFrame/Types.h"

/*
�摜�͈̔͂Ƀ}�E�X�������Ă�����摜��ύX����
*/

class UI2DSelectBase : public UI2DBase{
public:
    UI2DSelectBase();
    virtual ~UI2DSelectBase();

    void Draw() override;

};