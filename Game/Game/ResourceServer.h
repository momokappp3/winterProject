/*****************************************************************
 * \file   ResourceServer.h
 * \brief  (���L���\�[�X�𐧌䂷�邽�߂̃T�[�o) �摜��3D���f���̓��ꕨ�N���X
 * \author momoka Fuhita
 * \date   2021 5/28
 * @details ���ׂĐÓI�����o�ō\������
 *			LoadGraph��map���g�����z��ɗ� _mapGraph[/png/player.png]�̒��g���ʔԍ�
 *			�֐���static��`�͂���Ȃ�
 *          �ϐ��̒�`�͕K�v
 *********************************************************************/
#pragma once
#include <unordered_map>   //���߂�ꂽ�����ŕ���ł��Ȃ�
#include<Tchar.h>

class ResourceServer {
public:
	static void	Init();   //static���ƃC���X�^���X�Ȃ��ŌĂׂ�
	static void	Release();
	static void	ClearGraph();

	static int MV1LoadModel(const TCHAR* FileName,bool multiple);
	static bool DeleteModel(int handle);

	//2D
	static int LoadGraph(const TCHAR* FileName);
	static bool DeleteGraph(int handle);
};