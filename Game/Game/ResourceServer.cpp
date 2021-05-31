#include "DxLib.h"
#include <vector>
#include "ResourceServer.h"

namespace {
    // �ÓI�����o����
    std::unordered_map<std::string, int> _mapGraph3D;  //�t�@�C���� ���ʔԍ�
    std::unordered_map<std::string, int> _mapGraph2D;
}

void ResourceServer::Init() {
    _mapGraph3D.clear();
}

void ResourceServer::Release() {   //�������ǂ����Ă���̂�
    ClearGraph();
}

void ResourceServer::ClearGraph() {

    // ���ׂẴf�[�^�̍폜������
    for (auto itr = _mapGraph3D.begin(); itr != _mapGraph3D.end(); itr++) {
        MV1DeleteModel(itr->second);   //�����ō폜���Ă���clear
    }
    _mapGraph3D.clear();
}

//�g���@�����̃C���X�^���X�𐶐�����ꍇ���̂܂܃n���h����Ԃ�
int ResourceServer::MV1LoadModel(const TCHAR* FileName,bool multiple) {

    if (!multiple) {
        // �L�[�̌���
        auto itr = _mapGraph3D.find(FileName);  //�����̃t�@�C�����̃L�[�̈ʒu

        if (itr != _mapGraph3D.end()) {   //�ŏI�v�f�̎��ł͂Ȃ�������@�@�����̐���

            // �L�[��������
            return itr->second;   //second = �n���h��
        }
    }

    int cg = DxLib::MV1LoadModel(FileName);     // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���

    if (!multiple) {
        // �L�[�ƃf�[�^��map�ɓo�^
        _mapGraph3D[FileName] = cg;
    }

    return cg;   //���ʔԍ���Ԃ�
}

bool ResourceServer::DeleteModel(int handle) {

    if (handle == -1) {
        return false;
    }

    for (auto itr = _mapGraph3D.begin(); itr != _mapGraph3D.end(); itr++) {
        if (itr->second == handle) {
            DxLib::MV1DeleteModel(handle);

            _mapGraph3D.erase(itr);

            return true;
        }
    }

    return false;
}

//2D
int ResourceServer::LoadGraph(const TCHAR* FileName) {

    // �L�[�̌���
    auto itr = _mapGraph2D.find(FileName);  //�����̃t�@�C�����̃L�[�̈ʒu

    if (itr != _mapGraph2D.end()) {   //�ŏI�v�f�̎��ł͂Ȃ�������@�@�����̐���

        // �L�[��������
        return itr->second;   //second = �n���h��
    }


    int cg = DxLib::LoadGraph(FileName);     // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���

        // �L�[�ƃf�[�^��map�ɓo�^
    _mapGraph2D[FileName] = cg;

    return cg;   //���ʔԍ���Ԃ�
}

bool ResourceServer::DeleteGraph(int handle) {

    if (handle == -1) {
        return false;
    }

    for (auto itr = _mapGraph2D.begin(); itr != _mapGraph2D.end(); itr++) {
        if (itr->second == handle) {
            DxLib::DeleteGraph(handle);

            _mapGraph2D.erase(itr);

            return true;
        }
    }

    return false;
}