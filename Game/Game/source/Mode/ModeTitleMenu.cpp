//#include "ModeGame.h"
#include "AppFrame.h"
#include "../ApplicationMain.h"
#include "../Mode/ModeTitleMenu.h"
#include "Action3DGame.h"
#include "../../ResourceServer.h"
#include "GalGame.h"
#include "../Mode/ModeGame.h"

ModeTitleMenu::ModeTitleMenu() {

	_pInput = nullptr;
	_menuKind = Kind::Max;

	_enterInput = 0;

	_x = 0;
	_y = 0;

	_backHandle = -1;
	_targetHandle = -1;
}

ModeTitleMenu::~ModeTitleMenu() {
}

bool ModeTitleMenu::Initialize() {
	if (!ModeBase::Initialize()) {
		return false;
	}

	_pInput.reset(new Input);

	_menuKind = Kind::Max;

	_x = 117;
	_y = 600 - 75;

	_backHandle = ResourceServer::LoadGraph(_T("res/menu.png"));
	_targetHandle = ResourceServer::LoadGraph(_T("res/target.png"));

	return true;
}

bool ModeTitleMenu::Process() {
	ModeBase::Process();

	if (_pInput != nullptr) {
		_pInput->Process();
	}

	if (_pInput->_key[(KEY_INPUT_RETURN)] == 1) {

		switch (_menuKind){
		case Kind::NewGame:
			ModeServer::GetInstance()->Del(this);  // このモードを削除予約
			ModeServer::GetInstance()->Add(new Action3DGame(), 2, "Action3DGame");  // 次のモードを登録
			break;

		case Kind::LoadGame:
			ModeServer::GetInstance()->Del(this);  // このモードを削除予約
			ModeServer::GetInstance()->Add(new GalGame(), 3, "GalGame");  // 次のモードを登録
			break;

		case Kind::Option:
			ModeServer::GetInstance()->Del(this);  // このモードを削除予約
			ModeServer::GetInstance()->Add(new ModeGame(), 4, "ModeGame");  // 次のモードを登録
			break;

		case Kind::Help:
			break;
		case Kind::End:
			break;
		default:
			break;
		}
	}

	//上に移動
	if (_pInput->_key[(KEY_INPUT_UP)] == 1 && _menuKind > Kind::NewGame) {
		int now = static_cast<int>(_menuKind);

		now--;
		_y -= 75;
		_menuKind = static_cast<Kind>(now);
	}
	//下に移動
	if (_pInput->_key[(KEY_INPUT_DOWN)] == 1 && _menuKind < Kind::End) {
		int now = static_cast<int>(_menuKind);

		now++;
		_y += 75;
		_menuKind = static_cast<Kind>(now);
	}

	return true;
}

bool ModeTitleMenu::Render() {
	ModeBase::Render();

	//DrawFormatString(600, 600, GetColor(255,255,255), "%d",_menuKind);

	DrawGraph(0, 0, _backHandle, TRUE);

	if (_menuKind != Kind::Max) {
		DrawGraph(_x, _y, _targetHandle, TRUE);
	}

	//種類表示
	//============================================
	int now = static_cast<int>(_menuKind);
	DrawFormatString(20, 20, GetColor(255, 255, 255), "今のKIND%d", now);
	_menuKind = static_cast<Kind>(now);

	return true;
}

bool ModeTitleMenu::Terminate() {
	// _cg を解放しないといけないけど、AMLibは個別解放できない・・
	ModeBase::Terminate();

	return true;
}