#pragma once
#include "../../AppFrame/source/appframe.h"
#include <memory>
#include "../../Camera.h"
#include "../../Model.h"
#include "../../Animation.h"
#include"../../AnimationBase.h"
#include "../../AppFrame/Input.h"

class Action3DGame : public ModeBase {
public:
	Action3DGame();
	virtual ~Action3DGame();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

private:

	std::unique_ptr<Camera> _pCamera;
	std::unique_ptr<Model> _pModel;
	std::unique_ptr<AnimationBase> _pAnimationBase;
	std::unique_ptr<Input> _pInput;
	//std::unique_ptr<Animation> _pAnimation;

};