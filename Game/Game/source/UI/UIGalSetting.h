#pragma once
#include "UIUseBase.h"
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include "../../../../AppFrame/Tween.h"

class UIGalSetting :public UIUseBase{
public:
    UIGalSetting();
    virtual ~UIGalSetting();

    bool Init() override;
    void Process() override;
    void Draw() override;

private:

    std::unique_ptr<Tween> _pTween;

    std::unique_ptr<UI2DBase> _pBackImageBase;
    std::unique_ptr<UI2DSelectBase> _pOutBSelectBase;
    std::unique_ptr<UI2DSelectBase> _pTitleBSelectBase;

    //�w�i�̏o������  ����_start��true��������
    //�����ł�DrawArea���g��

    /*
    ���N���X�̃R�}���h�x�N�^�[�ɓ�����ォ��{�^�����I�����ꂽ��
    */
};