#include "../Mode/ModeTitle.h"
#include <string>
#include <Dxlib.h>
#include "../../ResourceServer.h"

#define CAMERA_TITLE_POSITION { -18.026157f, 14.650770f, -34.953270f }
#define CAMERA_TITLE_TARGET {-18.026155f, 16.672798f, 1.052301f}

#define CAMERA_INIT_POSITION {-3.857570f, 19.892756f, -25.599190f }
#define CAMERA_INIT_TARGET {-10.132383f, 13.788612f, 1.892545f}

#define CAMERA_MENU_POSITION {8.390586f, 22.943768f, -36.676380f }
#define CAMERA_MENU_TARGET {15.942330f, 13.788612f, 4.937160f}

#define ScaleStage {2.40,2.50,2.40}

#define PositionLove {-32.447, 23.073, 0.000}
#define PositionLove2 {-21.778, 18.026, 3.305}
#define PositionSweet {-28.778,13.000,0.00}
#define PositionEx {-18.984, 9.326,0.000}
#define Position2Heart {-11.537, 13.000, 0.000}
#define Position2Heart2 {-7.000, 13.000, 0.000}

//塗りつぶしハート1
#define ScaleHeart {1.040, 1.040, 1.040}
#define PositionHeart {-23.747, 23.352, 0.00}
#define RotationHeart {0.30, -0.395, 0.969}  //  0.135, 5.969

//塗りつぶしハート2
#define ScaleHeart2 {1.230, 1.230, 1.230}
#define PositionHeart2 {-38.839, 18.305, 0.000}
#define RotationHeart2 {0.2, 0.10, -0.359}

//TitleInit
#define PositionInitLove {-32.447, -7.073, 0.000}
#define PositionInitLove2 {-21.778, -12.026, 3.305}
#define PositionInitSweet {-28.778,-17.000,0.00}
#define PositionInitEx {-18.984, -21.326,0.000}
#define PositionInit2Heart {-11.537, -17.000, 0.000}
#define PositionInit2Heart2 {-7.000, -17.000, 0.000}
#define PositionInitHeart {-23.747, -7.352, 0.00}
#define PositionInitHeart2 {-38.839, -12.305, 0.000}

//TitleMenu
#define ScaleTitleMenu {0.650, 0.650, 0.650}
#define PositionNewGame {31.005, 28.121, 0.00}
#define PositionLoadGame {31.005, 21.631, 0.00}
#define PositionOption {37.494, 15.142, 0.00}
#define PositionHelp {43.263, 8.653, 0.00}
#define PositionExit {45.426, 2.163, 0.00}

#define PositionInitNewGame {11.5, -5.047, -7.00}
#define PositionInitLoadGame {11.5, -5.047, -7.00}
#define PositionInitOption {11.5, -5.047, -7.00}
#define PositionInitHelp {11.5, -5.047, -7.00}
#define PositionInitExit {11.5, -5.047, -7.00}

#define PositionSelectNewGame {11.5, -5.047, 7.00}
#define PositionSelectLoadGame {11.5, -5.047, 7.00}
#define PositionSelectOption {11.5, -5.047, 7.00}
#define PositionSelectHelp {11.5, -5.047, 7.00}
#define PositionSelectExit {11.5, -5.047, 7.00}

ModeTitle::ModeTitle() {

	_pStageModel = nullptr;
	_pLove = nullptr;
	_pLove2 = nullptr;
	_pSweet = nullptr;
	_p2Heart = nullptr;
	_p2Heart2 = nullptr;
	_pEx = nullptr;
	_pHeart = nullptr;
	_pHeart2 = nullptr;

	_pNewGame = nullptr;
	_pLoadGame = nullptr;
	_pOption = nullptr;
	_pHelp = nullptr;
	_pExit = nullptr;

	_pCamera = nullptr;
	_pMouseInput = nullptr;
	_pAnimationBase = nullptr;
	_pInput = nullptr;
	_pSoundManager = nullptr;

	//tween
	_pVectorTweenPotion = nullptr;
	_pVectorTweenTarget = nullptr;
	_pLoveTweenScale = nullptr;

	_pTweenMove1 = nullptr;
	_pTweenMove2 = nullptr;
	_pTweenMove3 = nullptr;
	_pTweenMove4 = nullptr;
	_pTweenMove5 = nullptr;

	_pTweenTitleMove1 = nullptr;
	_pTweenTitleMove2 = nullptr;
	_pTweenTitleMove3 = nullptr;
	_pTweenTitleMove4 = nullptr;
	_pTweenTitleMove5 = nullptr;
	_pTweenTitleMove6 = nullptr;
	_pTweenTitleMove7 = nullptr;
	_pTweenTitleMove8 = nullptr;

	_isBgm = false;
}

ModeTitle::~ModeTitle() {
}

/*　
	初期値
	_pCamera->SetPosition(-3.857570f, 19.892756f, -25.599190f);
	_pCamera->SetTarget(-10.132383f, 13.788612f, 1.892545f);

	タイトル文字アップ
	_pCamera->SetPosition(-18.026157f, 14.650770f, -34.953270f);
	_pCamera->SetTarget(-18.026155f, 16.672798f, 1.052301f);

	選択肢文字アップ
	_pCamera->SetPosition(8.390586f, 22.943768f, -36.676380f);
	_pCamera->SetTarget(15.942330f, 13.788612f, 4.937160f);


	音楽つける
	当たり判定


*/

bool ModeTitle::Initialize() {

	if (!ModeBase::Initialize()) {
		return false;
	}

	//メモリの所有権を委ねるには.reset
	_pCamera.reset(new Camera);
	_pStageModel.reset(new Model);
	_pLove.reset(new Model);
	_pLove2.reset(new Model);
	_pSweet.reset(new Model);
	_pHeart.reset(new Model);
	_pHeart2.reset(new Model);
	_p2Heart.reset(new Model);
	_p2Heart2.reset(new Model);
	_pEx.reset(new Model);

	_pNewGame.reset(new Model);
	_pLoadGame.reset(new Model);
	_pOption.reset(new Model);
	_pHelp.reset(new Model);
	_pExit.reset(new Model);

	_pMouseInput.reset(new MouseInput);
	_pAnimationBase.reset(new AnimationBase);
	_pInput.reset(new Input);
	_pSoundManager.reset(new SoundManager);

	_pVectorTweenPotion.reset(new VectorTween);
	_pVectorTweenTarget.reset(new VectorTween);
	_pLoveTweenScale.reset(new VectorTween);

	_pTweenMove1.reset(new VectorTween);
	_pTweenMove2.reset(new VectorTween);
	_pTweenMove3.reset(new VectorTween);
	_pTweenMove4.reset(new VectorTween);
	_pTweenMove5.reset(new VectorTween);

	_pTweenTitleMove1.reset(new VectorTween);
	_pTweenTitleMove2.reset(new VectorTween);
	_pTweenTitleMove3.reset(new VectorTween);
	_pTweenTitleMove4.reset(new VectorTween);
	_pTweenTitleMove5.reset(new VectorTween);
	_pTweenTitleMove6.reset(new VectorTween);
	_pTweenTitleMove7.reset(new VectorTween);
	_pTweenTitleMove8.reset(new VectorTween);

	_pCamera->SetPosition(-3.857570f, 19.892756f, -25.599190f);
	_pCamera->SetTarget(-10.132383f, 13.788612f, 1.892545f);
	_pCamera->SetNearFar(1.442092f, 360.523010f);

	_pStageModel->Load("model/iceStage/stage.pmx");  //ステージ
	_pAnimationBase->Load("model/onna/onna.pmx");  //キャラ
	_pLove->Load("model/title/title_love.mv1",true);  //文字
	_pLove2->Load("model/title/title_love.mv1",true);
	_pSweet->Load("model/title/title_sweet.mv1");
	_p2Heart->Load("model/title/title_hart2.mv1",true);
	_p2Heart2->Load("model/title/title_hart2.mv1",true);
	_pEx->Load("model/title/title_Ex.mv1");
	_pHeart->Load("model/title/title_hart.mv1", true);
	_pHeart2->Load("model/title/title_hart.mv1", true);

	//
	_pNewGame->Load("model/title/titleMenu/title_newGame.mv1");
	_pLoadGame->Load("model/title/titleMenu/title_loadGame.mv1");
	_pOption->Load("model/title/titleMenu/title_option.mv1");
	_pHelp->Load("model/title/titleMenu/title_help.mv1");
	_pExit->Load("model/title/titleMenu/title_exit.mv1");

	SetModelInitInfo();

	//_pSoundManager->Init();

	//_coNum = MV1SearchFrame(_pNewGame->GetHandle(), "collisionNewGame");



	return true;
}

bool ModeTitle::Process() {

	if (_pMouseInput == nullptr) {
		return false;
	}
	_pMouseInput->Process();
	
	if (!_isBgm) {
		if (_pSoundManager != nullptr) {  //null
			_pSoundManager->PlayBgm(SoundManager::BGM::Title);
			_isBgm = true;
		}
	}
	

	_pAnimationBase->Play(true, 0, 0.3f);

	//毎フレーム
	// モデル全体のコリジョン情報を構築
	//セットポジションスケールしてからする
	if (MV1SetupCollInfo(_pNewGame->GetHandle(), 4, 8, 8, 8) == -1) {
		return false;  //falseに来てしまう
	}


	// モデルと線分との当たり判定
	HitPoly = MV1CollCheck_Line(_pNewGame->GetHandle(), -1, _pMouseInput->GetStart3D(), _pMouseInput->GetEnd3D());


	if (HitPoly.HitFlag == 1) {

		_pNewGame->GetTransform().AddRotateY(5.0f);

	}


	//カメラに対して角度をつけ足せる バグ
	if (CheckHitKey(KEY_INPUT_LEFT)) {	
		_pCamera->GetTransform().AddRotateY(5.0f);
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		_pCamera->GetTransform().AddRotateY(5.0f);
	}

	if (CheckHitKey(KEY_INPUT_A)) {

		//モデルに対して角度をつけ足せる
		_pAnimationBase->GetTransform().AddRotateY(5.0f);
	}

	if (CheckHitKey(KEY_INPUT_S)) {

		//モデルに対して角度をつけ足せる
		_pAnimationBase->GetTransform().AddRotateY(-5.0f);
	}

	if (CheckHitKey(KEY_INPUT_D)) {
		_pAnimationBase->Play(true, 1, 5.0f);
	}

	if (_pInput->_key[(KEY_INPUT_Q)] == 1) {

		_pVectorTweenPotion->SetVectorTween(_pCamera->GetPosition(), CAMERA_INIT_POSITION,
											90, VectorTween::Type::SineStart);
		_pVectorTweenTarget->SetVectorTween(_pCamera->GetTarget(), CAMERA_INIT_TARGET,
											90, VectorTween::Type::SineStart);
	}

	if (_pInput->_key[(KEY_INPUT_W)] == 1) {
		//カメラ移動
		_pVectorTweenPotion->SetVectorTween(_pCamera->GetPosition(), CAMERA_TITLE_POSITION,
											100, VectorTween::Type::SineStart);
		_pVectorTweenTarget->SetVectorTween(_pCamera->GetTarget(), CAMERA_TITLE_TARGET,
											100, VectorTween::Type::SineStart);
	}
	
	if (_pMouseInput->GetLeft() && _pCamera->GetPosition().x < -1.0f) {
		_pVectorTweenPotion->SetVectorTween(_pCamera->GetPosition(), CAMERA_MENU_POSITION, 60);
		_pVectorTweenTarget->SetVectorTween(_pCamera->GetTarget(), CAMERA_MENU_TARGET, 60);


		//上に上がる
		_pTweenMove1->SetVectorTween(_pNewGame->GetTransform().GetPosition(), PositionNewGame,
									 60, VectorTween::Type::SineEnd);

		_pTweenMove2->SetVectorTween(_pLoadGame->GetTransform().GetPosition(), PositionLoadGame,
									 60, VectorTween::Type::SineEnd);

		_pTweenMove3->SetVectorTween(_pOption->GetTransform().GetPosition(), PositionOption,
									 60, VectorTween::Type::SineEnd);

		_pTweenMove4->SetVectorTween(_pHelp->GetTransform().GetPosition(), PositionHelp,
									 60, VectorTween::Type::SineEnd);

		_pTweenMove5->SetVectorTween(_pExit->GetTransform().GetPosition(), PositionExit,
									 60, VectorTween::Type::SineEnd);

		//下に下がるタイトル
		_pTweenTitleMove1->SetVectorTween(_pLove->GetTransform().GetPosition(), PositionInitLove,
										  60, VectorTween::Type::SineEnd);

		_pTweenTitleMove2->SetVectorTween(_pLove2->GetTransform().GetPosition(), PositionInitLove2,
										  60, VectorTween::Type::SineEnd);

		_pTweenTitleMove3->SetVectorTween(_pSweet->GetTransform().GetPosition(), PositionInitSweet,
										  60, VectorTween::Type::SineEnd);

		_pTweenTitleMove4->SetVectorTween(_p2Heart->GetTransform().GetPosition(), PositionInit2Heart,
										  40, VectorTween::Type::SineEnd);

		_pTweenTitleMove5->SetVectorTween(_p2Heart2->GetTransform().GetPosition(), PositionInit2Heart2,
										  40, VectorTween::Type::SineEnd);

		_pTweenTitleMove6->SetVectorTween(_pEx->GetTransform().GetPosition(), PositionInitEx,
										  60, VectorTween::Type::SineEnd);

		_pTweenTitleMove7->SetVectorTween(_pHeart->GetTransform().GetPosition(), PositionInitHeart,
										  60, VectorTween::Type::SineEnd);

		_pTweenTitleMove8->SetVectorTween(_pHeart2->GetTransform().GetPosition(), PositionInitHeart2,
										  60, VectorTween::Type::SineEnd);
	}

	if (_pMouseInput->GetLeft() && _pCamera->GetPosition().x > 7.0f) {
		_pVectorTweenPotion->SetVectorTween(_pCamera->GetPosition(), CAMERA_INIT_POSITION,
											90, VectorTween::Type::SineStart);
		_pVectorTweenTarget->SetVectorTween(_pCamera->GetTarget(), CAMERA_INIT_TARGET, 90,
											VectorTween::Type::SineStart);

		//下に下がるタイトルメニュー
		_pTweenMove1->SetVectorTween(_pNewGame->GetTransform().GetPosition(), PositionInitNewGame,
									 60, VectorTween::Type::SineEnd);

		_pTweenMove2->SetVectorTween(_pLoadGame->GetTransform().GetPosition(), PositionInitLoadGame,
									 60, VectorTween::Type::SineEnd);

		_pTweenMove3->SetVectorTween(_pOption->GetTransform().GetPosition(), PositionInitOption,
									 60, VectorTween::Type::SineEnd);

		_pTweenMove4->SetVectorTween(_pHelp->GetTransform().GetPosition(), PositionInitHelp,
									 60, VectorTween::Type::SineEnd);

		_pTweenMove5->SetVectorTween(_pExit->GetTransform().GetPosition(), PositionInitExit,
									 60, VectorTween::Type::SineEnd);

		//上に上がるタイトル
		_pTweenTitleMove1->SetVectorTween(_pLove->GetTransform().GetPosition(), PositionLove,
									 100, VectorTween::Type::SineStart);

		_pTweenTitleMove2->SetVectorTween(_pLove2->GetTransform().GetPosition(), PositionLove2,
									 60, VectorTween::Type::SineStart);

		_pTweenTitleMove3->SetVectorTween(_pSweet->GetTransform().GetPosition(), PositionSweet,
									 100, VectorTween::Type::SineStart);

		_pTweenTitleMove4->SetVectorTween(_p2Heart->GetTransform().GetPosition(), Position2Heart,
									 80, VectorTween::Type::SineStart);

		_pTweenTitleMove5->SetVectorTween(_p2Heart2->GetTransform().GetPosition(), Position2Heart2,
									 80, VectorTween::Type::SineStart);

		_pTweenTitleMove6->SetVectorTween(_pEx->GetTransform().GetPosition(), PositionEx,
									 100, VectorTween::Type::SineStart);

		_pTweenTitleMove7->SetVectorTween(_pHeart->GetTransform().GetPosition(), PositionHeart,
									 100, VectorTween::Type::SineStart);

		_pTweenTitleMove8->SetVectorTween(_pHeart2->GetTransform().GetPosition(), PositionHeart2,
									 110, VectorTween::Type::SineStart);

	}
	
	MoveUpDown();

	//カメラ
	if (_pVectorTweenPotion->IsStart() && !_pVectorTweenPotion->IsEnd()) {

		VECTOR CameraPositionNow = _pVectorTweenPotion->GetPosition();
		float pX = CameraPositionNow.x, pY = CameraPositionNow.y, pZ = CameraPositionNow.z;

		_pCamera->SetPosition(pX, pY, pZ);
	}

	if (_pVectorTweenTarget->IsStart() && !_pVectorTweenTarget->IsEnd()) {
		VECTOR CameraTargetNow = _pVectorTweenTarget->GetPosition();
		float tX = CameraTargetNow.x, tY = CameraTargetNow.y, tZ = CameraTargetNow.z;

		_pCamera->SetTarget(tX, tY, tZ);
	}

	if (CheckHitKey(KEY_INPUT_B)) {
		_pLove2->GetTransform().AddRotateY(2.0f);
		
	}

	

	_pAnimationBase->Process();
	_pCamera->Process();
	_pStageModel->Process();
	_pLove->Process();
	_pLove2->Process();
	_pSweet->Process();
	_pHeart->Process();
	_pHeart2->Process();
	_p2Heart->Process();
	_p2Heart2->Process();
	_pEx->Process();
	_pNewGame->Process();
	_pLoadGame->Process();
	_pOption->Process();
	_pHelp->Process();
	_pExit->Process();
	_pInput->Process();
	_pSoundManager->Process();

	_pVectorTweenPotion->Process();
	_pVectorTweenTarget->Process();
	_pLoveTweenScale->Process();

	_pTweenMove1->Process();
	_pTweenMove2->Process();
	_pTweenMove3->Process();
	_pTweenMove4->Process();
	_pTweenMove5->Process();

	_pTweenTitleMove1->Process();
	_pTweenTitleMove2->Process();
	_pTweenTitleMove3->Process();
	_pTweenTitleMove4->Process();
	_pTweenTitleMove5->Process();
	_pTweenTitleMove6->Process();
	_pTweenTitleMove7->Process();
	_pTweenTitleMove8->Process();

	return true;
}

bool ModeTitle::Render() {

	_pCamera->Render();
	_pStageModel->Render();
	_pLove->Render();
	_pLove2->Render();
	_pSweet->Render();
	_pHeart->Render();
	_pHeart2->Render();
	_p2Heart->Render();
	_p2Heart2->Render();
	_pEx->Render();
	_pNewGame->Render();
	_pLoadGame->Render();
	_pOption->Render();
	_pHelp->Render();
	_pExit->Render();
	_pMouseInput->Draw();
	_pAnimationBase->Render();

	return true;
}

bool ModeTitle::SetModelInitInfo() {

	_pStageModel->GetTransform().SetScale(ScaleStage);

	_pLove->GetTransform().SetPosition(PositionLove);
	_pLove2->GetTransform().SetPosition(PositionLove2);
	_pSweet->GetTransform().SetPosition(PositionSweet);
	_p2Heart->GetTransform().SetPosition(Position2Heart);
	_p2Heart2->GetTransform().SetPosition(Position2Heart2);
	_pEx->GetTransform().SetPosition(PositionEx);
	//潰しハート
	_pHeart->GetTransform().SetScale(ScaleHeart); 
	_pHeart->GetTransform().SetPosition(PositionHeart);
	_pHeart->GetTransform().SetDirection(RotationHeart);

	_pHeart2->GetTransform().SetScale(ScaleHeart2); 
	_pHeart2->GetTransform().SetPosition(PositionHeart2);
	_pHeart2->GetTransform().SetDirection(RotationHeart2);

	//TitleMenu
	_pNewGame->GetTransform().SetScale(ScaleTitleMenu);
	_pLoadGame->GetTransform().SetScale(ScaleTitleMenu);
	_pOption->GetTransform().SetScale(ScaleTitleMenu);
	_pHelp->GetTransform().SetScale(ScaleTitleMenu);
	_pExit->GetTransform().SetScale(ScaleTitleMenu);

	_pNewGame->GetTransform().SetPosition(PositionInitNewGame);
	_pLoadGame->GetTransform().SetPosition(PositionInitLoadGame);
	_pOption->GetTransform().SetPosition(PositionInitOption);
	_pHelp->GetTransform().SetPosition(PositionInitHelp);
	_pExit->GetTransform().SetPosition(PositionInitExit);

	return true;
}

void ModeTitle::MoveUpDown() {

//タイトルメニュー
	if (_pTweenMove1->IsStart() && !_pTweenMove1->IsEnd()) {
		_pNewGame->GetTransform().SetPosition(_pTweenMove1->GetPosition());
	}
	if (_pTweenMove2->IsStart() && !_pTweenMove2->IsEnd()) {
		_pLoadGame->GetTransform().SetPosition(_pTweenMove2->GetPosition());
	}
	if (_pTweenMove3->IsStart() && !_pTweenMove3->IsEnd()) {
		_pOption->GetTransform().SetPosition(_pTweenMove3->GetPosition());
	}
	if (_pTweenMove4->IsStart() && !_pTweenMove4->IsEnd()) {
		_pHelp->GetTransform().SetPosition(_pTweenMove4->GetPosition());
	}
	if (_pTweenMove5->IsStart() && !_pTweenMove5->IsEnd()) {
		_pExit->GetTransform().SetPosition(_pTweenMove5->GetPosition());
	}

	//タイトル
	if (_pTweenTitleMove1->IsStart() && !_pTweenTitleMove1->IsEnd()) {
		_pLove->GetTransform().SetPosition(_pTweenTitleMove1->GetPosition());
	}
	if (_pTweenTitleMove2->IsStart() && !_pTweenTitleMove2->IsEnd()) {
		_pLove2->GetTransform().SetPosition(_pTweenTitleMove2->GetPosition());
	}
	if (_pTweenTitleMove3->IsStart() && !_pTweenTitleMove3->IsEnd()) {
		_pSweet->GetTransform().SetPosition(_pTweenTitleMove3->GetPosition());
	}
	if (_pTweenTitleMove4->IsStart() && !_pTweenTitleMove4->IsEnd()) {
		_p2Heart->GetTransform().SetPosition(_pTweenTitleMove4->GetPosition());
	}
	if (_pTweenTitleMove5->IsStart() && !_pTweenTitleMove5->IsEnd()) {
		_p2Heart2->GetTransform().SetPosition(_pTweenTitleMove5->GetPosition());
	}
	if (_pTweenTitleMove6->IsStart() && !_pTweenTitleMove6->IsEnd()) {
		_pEx->GetTransform().SetPosition(_pTweenTitleMove6->GetPosition());
	}
	if (_pTweenTitleMove7->IsStart() && !_pTweenTitleMove7->IsEnd()) {
		_pHeart->GetTransform().SetPosition(_pTweenTitleMove7->GetPosition());
	}
	if (_pTweenTitleMove8->IsStart() && !_pTweenTitleMove8->IsEnd()) {
		_pHeart2->GetTransform().SetPosition(_pTweenTitleMove8->GetPosition());
	}
}

bool ModeTitle::Terminate() {
	return true;
}