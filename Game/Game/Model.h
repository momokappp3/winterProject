#pragma once
/*

3D�̓ǂݍ���
�\���̃x�[�X�N���X

�h���N���X�ɃA�j���[�V�����ƃR���W�����N���X

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