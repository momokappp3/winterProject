#pragma once

#include "appframe.h"

#include <string>
#include <vector>

class ModeMenu : public ModeBase {
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void	Add(MenuItemBase* itemBase);
	void	Clear();

protected:
	std::vector<MenuItemBase*>	_vItems;

	int		_curPos;
	int		_curAnimCnt;

};

// メニュー項目用ベースクラス
class MenuItemBase {
public:
	MenuItemBase(void* param, std::string text) {
		_param = param;
		_text = text;
	}

	virtual ~MenuItemBase() {
	}

	// 項目を決定したらこの関数が呼ばれる
	// return int : 0 = メニュー継続, 1 = メニュー終了
	virtual int Selected() {
		return 0;
	}

public:
	void* _param;
	std::string		_text;
};