#pragma once
#include "GalGameUI.h"
#include "UIGalMenuInit.h"
#include <memory>
#include ".././.../../../../../AppFrame/Types.h"
#include "../../../../AppFrame/MouseInput.h"
#include "UIGalMenu.h"
#include "UIGalSetting.h"
#include "UIGalItem.h"
#include "UIGalStory.h"

/*
UIのやり取り
*/

class GalGameUI {
public:
    GalGameUI();
    virtual ~GalGameUI();

    bool Init();
    void Process();
    void Draw();

    void SetMolecule(int molecule) {
        _molecule = molecule;
    }

    void SetCoin(int coin) {
        _coin = coin;
    }

    void SetFavor(int favor) {
        _favor = favor;
    }
private:

    void SettingProcess();
    void ItemProcess();
    void StoryProcess();

    GalGameUIType _type;  //現在表示しているタイプ

    std::unique_ptr<UIGalMenuInit> _pUIGalMenuInit;
    std::unique_ptr<UIGalMenu> _pUIGalMenu;
    std::unique_ptr<UIGalSetting> _pUIGalSetting;
    std::unique_ptr<UIGalItem> _pUIGalItem;
    std::unique_ptr<UIGalStory> _pUIGalStory;

    std::unique_ptr<MouseInput> _pMouseInput;

    int _molecule;
    int _coin;
    int _favor;

};
