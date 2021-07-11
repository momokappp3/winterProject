/*****************************************************************//**
 * \file   GalGame.h
 * \brief  ÉQÅ[ÉÄÉVÅ[Éì
 * \author momoka
 * \date   2021 7/9
 *********************************************************************/
#pragma once
#include "../../AppFrame/source/appframe.h"
#include <memory>
#include "../../Camera.h"
#include "../../Model.h"
#include "../../AppFrame/MouseInput.h"
#include "../../AnimationBase.h"
#include "../Novel/scripts/script_engine.h"
#include "../.././../../AppFrame/Input.h"
#include "../../../../AppFrame/VectorTween.h"
#include "../UI/GalGameUI.h"
#include "../SoundManager.h"
#include "../Face.h"
#include "../PlayerInfo.h"

class GalGame : public ModeBase {
public:
	GalGame();
	virtual ~GalGame();

	virtual bool Initialize() override;
	virtual bool Terminate()override;
	virtual bool Process();
	virtual bool Render();

private:
	std::unique_ptr<Camera> _pCamera;
	std::unique_ptr<Model> _pCharaModel;
	std::unique_ptr<Model> _pRoomModel;
	std::unique_ptr<AnimationBase> _pOnnaModel;
	std::unique_ptr<AnimationBase> _pOnnaRedModel;
	std::unique_ptr<Input> _pInput;
	std::unique_ptr<VectorTween> _pVectorTweenPotion;
	std::unique_ptr<VectorTween> _pVectorTweenTarget;
	std::unique_ptr<GalGameUI> _pGalGameUI;
	std::unique_ptr<Face> _pFace;

	std::unique_ptr<MouseInput> _pMouseInput;

	std::shared_ptr<PlayerInfo> _pPlayerInfo;
};