#include "Input.h"
#include "DxLib.h"

Input::Input() {

    for (int i = 0; i < 256; i++) {
        _key[i] = 0;
    }
}

Input::~Input() {
}

void Input::Process(){

    char tmpKey[256];

    GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            _key[i]++;     // ���Z
        }
        else {              // ������Ă��Ȃ����
            _key[i] = 0;   // 0�ɂ���
        }
    }
}