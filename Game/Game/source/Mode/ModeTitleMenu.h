#pragma once
#include "../ApplicationMain.h"
#include "../../AppFrame/Input.h"
#include <memory>

class ModeTitleMenu : public ModeBase{
public:
	ModeTitleMenu();
	virtual ~ModeTitleMenu();

	enum class Kind {
		Max = 0,
		NewGame, 
		LoadGame,
		Option,
		Help,
		End
	};

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	bool Render()override;

private:

	std::unique_ptr<Input> _pInput;

	Kind _menuKind;

	int _enterInput;


	int _backHandle;
	int _targetHandle;

	int _x, _y;
};