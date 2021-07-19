#pragma once
#include "UIUseBase.h"
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include "../../../../AppFrame/Tween.h"
#include "../../../../AppFrame/Types.h"
#include <vector>

class UIRoomStory :public UIUseBase {
public:
    UIRoomStory();
    virtual ~UIRoomStory();

    //override取った
    bool Init(std::shared_ptr<SoundManager>& soundManager);
    void Process() override;
    void Draw() override;

    void SetAddImageSize(int add) {
        _imageSize += add;
    }

    void SetStory0StringDraw(bool isDraw) {
        _story0String.isDraw = isDraw;

        if (isDraw) {
            _typeString = 0;
        }
    }

    void SetStory1StringDraw(bool isDraw) {
        _story1String.isDraw = isDraw;
        if (isDraw) {
            _typeString = 1;
        }
    }

    void SetStory2StringDraw(bool isDraw) {
        _story2String.isDraw = isDraw;
        if (isDraw) {
            _typeString = 2;
        }
    }
    void SetStory3StringDraw(bool isDraw) {
        _story3String.isDraw = isDraw;
        if (isDraw) {
            _typeString = 3;
        }
    }
    void SetStory4StringDraw(bool isDraw) {
        _story4String.isDraw = isDraw;
        if (isDraw) {
            _typeString = 4;
        }
    }

    int GetStringType() {
        return _typeString;
    }

    PopString GetStory0String() {
        return _story0String;
    }

    PopString GetStory1String() {
        return _story1String;
    }

    PopString GetStory2String() {
        return _story2String;
    }

    PopString GetStory3String() {
        return _story3String;
    }

    PopString GetStory4String() {
        return _story4String;
    }

    void StrinRoomlFalse() {
        _story0String.isDraw = false;
        _story1String.isDraw = false;
        _story2String.isDraw = false;
        _story3String.isDraw = false;
        _story4String.isDraw = false;
    }

private:

    //std::unique_ptr<Tween> _pTween;

    std::unique_ptr<UI2DBase> _pBackImageBase;

    //Vectorの数だけ増やす(json)
    //std::unique_ptr<UI2DSelectBase> _pStringBaseSelectBase;

    //背景の出現処理  基底の_startがtrueだったら

    /*
    基底クラスのコマンドベクター入れる上からボタンが選択されたか
    */

    //std::vector<std::unique_ptr<UI2DSelectBase>> _pvStringImageBaseSelectBase;

    std::unique_ptr<UI2DSelectBase> _pStringImageBase0;
    std::unique_ptr<UI2DSelectBase> _pStringImageBase1;
    std::unique_ptr<UI2DSelectBase> _pStringImageBase2;
    std::unique_ptr<UI2DSelectBase> _pStringImageBase3;
    std::unique_ptr<UI2DSelectBase> _pStringImageBase4;
    std::shared_ptr<SoundManager> _pSoundManager;

    int _imageSize;
    int _lastImageSize;

    PopString _story0String;
    PopString _story1String;
    PopString _story2String;
    PopString _story3String;
    PopString _story4String;

    int _typeString;
};