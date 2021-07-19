#pragma once
#include "UIUseBase.h"
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include "../../../../AppFrame/Tween.h"

class UIRoomSetting :public UIUseBase{
public:
    UIRoomSetting();
    virtual ~UIRoomSetting();

    //�I�[�o�[���C�h
    bool Init(std::shared_ptr<SoundManager>& soundManager);
    void Process() override;
    void Draw() override;

private:

    std::unique_ptr<Tween> _pTween;

    std::unique_ptr<UI2DBase> _pBackImageBase;
    std::unique_ptr<UI2DSelectBase> _pOutBSelectBase;
    std::unique_ptr<UI2DSelectBase> _pTitleBSelectBase;

    std::shared_ptr<SoundManager> _pSoundManager;

    //�w�i�̏o������  ����_start��true��������
    //�����ł�DrawArea���g��

    /*
    ���N���X�̃R�}���h�x�N�^�[�ɓ�����ォ��{�^�����I�����ꂽ��
    */
};