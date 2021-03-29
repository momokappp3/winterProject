#pragma once
#include "UI2DBase.h"

class UINumber : public UI2DBase {
public:
    UINumber();
    virtual ~UINumber();

    bool Init(int digitMax);
    void Process()override;
    void Draw() override;

    //�ꌅ�ڂ̍��W����œ񌅖ڂ���ꌅ�ڂ̉摜�T�C�Y�𑫂��Ă���
    bool SetNumHandle(int num);

    void SetNumberPoint(Point point);
    void SetNum(int num){
        _num = num;
    }

private:
    //Draw�ŃN���A���Ă�̂Ńv���Z�X�Ő�Βl�����Ȃ��Ƃ����Ȃ�

    std::vector<int> _vNumHandle;  //Set���������̃n���h�����������x�N�^�[

    Point _point;  //�ꌅ�ڂ̍��W

    int _num;  //
    int _digitMax;
};