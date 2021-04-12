#pragma once
#include "UI2DBase.h"
#include "../../../../AppFrame/MouseInput.h"
#include <functional>
#include "../../../../AppFrame/Types.h"
#include "../SoundManager.h"

/*
�摜�͈̔͂Ƀ}�E�X�������Ă�����摜��ύX����
*/

class UI2DSelectBase : public UI2DBase{
public:
    UI2DSelectBase();
    virtual ~UI2DSelectBase();

    void Process()override;
    void Draw() override;

    void SetOnSelect(std::function<void(void)> onSelect) {
        _onSelect = onSelect;
    }

private:
    int _lastSelect;

    std::function<void(void)> _onSelect;

};