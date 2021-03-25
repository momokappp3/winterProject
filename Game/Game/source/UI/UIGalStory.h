#pragma once
#pragma once
#include "UIUseBase.h"
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include "../../../../AppFrame/Tween.h"
#include <vector>

class UIGalStory :public UIUseBase {
public:
    UIGalStory();
    virtual ~UIGalStory();

    bool Init() override;
    void Process() override;
    void Draw() override;

    void SetAddImageSize(int add) {
        _imageSize += add;
    }

private:

    //std::unique_ptr<Tween> _pTween;

    std::unique_ptr<UI2DBase> _pBackImageBase;

    //Vector�̐��������₷(json)
    //std::unique_ptr<UI2DSelectBase> _pStringBaseSelectBase;

    //�w�i�̏o������  ����_start��true��������

    /*
    ���N���X�̃R�}���h�x�N�^�[�����ォ��{�^�����I�����ꂽ��
    */

    //std::vector<std::unique_ptr<UI2DSelectBase>> _pvStringImageBaseSelectBase;

    std::unique_ptr<UI2DSelectBase> _pStringImageBase0;
    std::unique_ptr<UI2DSelectBase> _pStringImageBase1;
    std::unique_ptr<UI2DSelectBase> _pStringImageBase2;
    std::unique_ptr<UI2DSelectBase> _pStringImageBase3;
    std::unique_ptr<UI2DSelectBase> _pStringImageBase4;


    int _imageSize;
    int _lastImageSize;

};