/*

試し
モデル表示＆モーション

組み合わせて表示モーションOK

*/


#include "AppFrame.h"
#include "../ApplicationMain.h"
#include "../Mode/ModeGame.h"

bool ModeGame::Initialize() {

	if (!ModeBase::Initialize()) {
		return false; 
	}
	_pCamera = nullptr;
	_pEffect3D = nullptr;
	_pCamera.reset(new Camera);
	_pEffect3D.reset(new Effect3D);

	_cg = MV1LoadModel("model/otoko/otoko.pmx");
	_cg2 = MV1LoadModel("model/tue/tue.pmx");

	//奥行0.1～1000までをカメラの描画範囲とする(カメラの初期位置)
	//SetCameraNearFar(0.1f, 800.0f);

	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));

	//カメラクラスで実装

	_pCamera->SetPosition(0.0f, 10.0f, -20.0f);
	_pCamera->SetTarget(0.0f, 10.0f, 0.0f);
	_pCamera->SetNearFar(0.1f, 800.0f);


	_pEffect3D->Init("effect/test.efk", 1.0f, false);
	_pEffect3D->SetPoint({ 100,250});


	_attachIndex = MV1AttachAnim(_cg, 1, -1, FALSE);
	_attachIndex2 = MV1AttachAnim(_cg2, 1, -1, FALSE);

	_totalTime = MV1GetAttachAnimTotalTime(_cg, _attachIndex);
	_totalTime2 = MV1GetAttachAnimTotalTime(_cg2, _attachIndex2);

	_playTime = 0.0f;
	_playTime2 = 0.0f;

	return true;
}

bool ModeGame::Process() {
	ModeBase::Process();

	int key = ApplicationMain::GetInstance()->GetKey();

	/*======================================
	アニメ
	=======================================*/


	if (key & PAD_INPUT_A) {
		_x += 8;
		// 再生時間を進める
		_playTime += 0.5f;
		_playTime2 += 0.5f;

		// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		if (_playTime >= _totalTime) {
			_playTime = 0.0f;
		}
		// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		if (_playTime2 >= _totalTime2) {
			_playTime2 = 0.0f;
		}
		// 再生時間をセットする
		MV1SetAttachAnimTime(_cg, _attachIndex, _playTime);
		// 再生時間をセットする
		MV1SetAttachAnimTime(_cg2, _attachIndex2, _playTime2);
	}


	if (key & PAD_INPUT_U) {
		//エフェクト出す
		_pEffect3D->Start();

	}

	if (_pEffect3D != nullptr) {
		_pEffect3D->Process();
	}

	_pCamera->Process();

	return true;
}

bool ModeGame::Render() {
	ModeBase::Render();


	_pCamera->Render();

	MV1DrawModel(_cg);
	MV1DrawModel(_cg2);

	DrawFormatString(500, 500, GetColor(255, 0, 0),"%lf:%lf",_playTime,_totalTime );
	DrawFormatString(500, 700, GetColor(255, 0, 0), "%lf:%lf", _playTime2, _totalTime2);



	return true;
}

bool ModeGame::Terminate() {
	ModeBase::Terminate();
	return true;
}

