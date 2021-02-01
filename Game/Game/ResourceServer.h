#pragma once

#include <unordered_map>   //���߂�ꂽ�����ŕ���ł��Ȃ�
#include<Tchar.h>

/* ���\�[�X�Ǘ��T�[�o
 ���ׂĐÓI�����o�ō\������
 LoadGraph��map���g�����z��ɗ� _mapGraph[/png/player.png]�̒��g���ʔԍ�
 �֐���static��`�͂���Ȃ�
*/
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