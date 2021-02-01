#pragma once
/*

3Dの読み込み
表示のベースクラス

派生クラスにアニメーションとコリジョンクラス

*/
#include "../../AppFrame/ObjectBase.h"
#include "Transform.h"
#include"ResourceServer.h"
#include <memory>

class Model : public ObjectBase {
public:
	Model();
	virtual ~Model();

	virtual bool Load(const TCHAR* fileName, bool multiple = false);

	void Process() override;
	void Render() override;

	Transform& GetTransform() {
		return _transform;
	}

	int GetHandle() {
		return _handle;
	}

protected:
	Transform _transform;

	std::unique_ptr<ResourceServer> _pResourceServer;

	int _handle;
};