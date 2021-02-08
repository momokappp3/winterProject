
#include "AppFrame.h"
#include "../ApplicationMain.h"
#include "ModeGame.h"


bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j
	_handle = MV1LoadModel("model/onna/onna.pmx");
	_attach_index = -1;		// �A�j���[�V�����A�^�b�`�͂���Ă��Ȃ�
	// �X�e�[�^�X���u�����v�ɐݒ�
	_status = STATUS::NONE;
	// �Đ����Ԃ̏�����
	_total_time = 0.f;
	_play_time = 0.0f;
	// �ʒu,�����̏�����
	_vPos = VGet(0, 0, 0);
	_vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���

	// �}�b�v
	//_handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1");
#if 1
	// �_���W����
	_handleMap = MV1LoadModel("model/demoStage/demoStage.mv1");
	_handleCoMap = MV1LoadModel("model/demoCo/2Co.mv1");

	MV1SetPosition(_handleCoMap, { 158.831,-30.482,-359.6 });

	_frameMapCollision = MV1SearchFrame(_handleCoMap, "dungeon_collision");
	//_frameMapCollision = MV1SearchFrame(_handleMap, "dungeon_collision");
#else
	// �t�B�[���h
	_handleMap = MV1LoadModel("res/Ground/Ground.mv1");
	_frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
#endif





	// �R���W�������̐���
	MV1SetupCollInfo(_handleCoMap, _frameMapCollision, 16, 16, 16);
	// �R���W�����̃t���[����`�悵�Ȃ��ݒ�
	MV1SetFrameVisible(_handleCoMap, _frameMapCollision, FALSE);
	// ���ʒu�̐ݒ�
	_colSubY = 40.f;


	// �J�����̐ݒ�i�킩��₷���ʒu�Ɂj
	//_cam._vPos = VGet(0, 90.f, -300.f);
	_cam._vPos = VGet(0-34, 20.f, -300.f);
	_cam._vTarget = VGet(0, 60, 0);
	_cam._clipNear = 2.f;
	_cam._clipFar = 10000.f;

	// ���̑�������
	_bViewCollision = TRUE;


	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGame::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �����O�̃X�e�[�^�X��ۑ����Ă���
	STATUS oldStatus = _status;


	if ((key & (PAD_INPUT_7 | PAD_INPUT_8)) == (PAD_INPUT_7 | PAD_INPUT_8)) {	// Q & W
		// �����A�^�[�Q�b�g�̍����ύX
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float rad = atan2(sz, sx);
		float length = sqrt(sz * sz + sx * sx);
		if (key & PAD_INPUT_LEFT) { length -= 1.f; }
		if (key & PAD_INPUT_RIGHT) { length += 1.f; }
		_cam._vPos.x = _cam._vTarget.x + cos(rad) * length;
		_cam._vPos.z = _cam._vTarget.z + sin(rad) * length;

		// Y�ʒu
		if (key & PAD_INPUT_DOWN) { _cam._vTarget.y -= 1.f; }
		if (key & PAD_INPUT_UP) { _cam._vTarget.y += 1.f; }
	}
	else if (key & PAD_INPUT_7) {	// Q
		// �p�x�ύX
		// Y����]
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float rad = atan2(sz, sx);
		float length = sqrt(sz * sz + sx * sx);
		if (key & PAD_INPUT_LEFT) { rad -= 0.05f; }
		if (key & PAD_INPUT_RIGHT) { rad += 0.05f; }
		_cam._vPos.x = _cam._vTarget.x + cos(rad) * length;
		_cam._vPos.z = _cam._vTarget.z + sin(rad) * length;

		// Y�ʒu
		if (key & PAD_INPUT_DOWN) { _cam._vPos.y -= 5.f; }
		if (key & PAD_INPUT_UP) { _cam._vPos.y += 5.f; }
	}
	else if (key & PAD_INPUT_8) {	// W
		// �J�����ʒu�i���ڈʒu��XZ�X���C�h�j
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float camrad = atan2(sz, sx);

		// �ړ����������߂�
		VECTOR v = { 0,0,0 };
		float mvSpeed = 2.f;
		if (key & PAD_INPUT_DOWN) { v.x = 1; }
		if (key & PAD_INPUT_UP) { v.x = -1; }
		if (key & PAD_INPUT_LEFT) { v.z = -1; }
		if (key & PAD_INPUT_RIGHT) { v.z = 1; }

		// v��rad����]������
		float length = 0.f;
		if (VSize(v) > 0.f) { length = mvSpeed; }
		float rad = atan2(v.z, v.x);
		v.x = cos(rad + camrad) * length;
		v.z = sin(rad + camrad) * length;

		// v�̕��ړ�
		_cam._vPos = VAdd(_cam._vPos, v);
		_cam._vTarget = VAdd(_cam._vTarget, v);
	}
	else {
		// �L�����ړ�(�J�����ݒ�ɍ��킹��)

		// �J�����̌����Ă���p�x���擾
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float camrad = atan2(sz, sx);

		// �ړ����������߂�
		VECTOR v = { 0,0,0 };
		float mvSpeed = 6.f;
		if (key & PAD_INPUT_DOWN) { v.x = 1; }
		if (key & PAD_INPUT_UP) { v.x = -1; }
		if (key & PAD_INPUT_LEFT) { v.z = -1; }
		if (key & PAD_INPUT_RIGHT) { v.z = 1; }

		// v��rad����]������
		float length = 0.f;
		if (VSize(v) > 0.f) { length = mvSpeed; }
		float rad = atan2(v.z, v.x);
		v.x = cos(rad + camrad) * length;
		v.z = sin(rad + camrad) * length;

		// �ړ��O�̈ʒu��ۑ�
		VECTOR oldvPos = _vPos;
		VECTOR oldv = v;

		// �R���W��������ň��������������ɁAescapeTbl[]���Ɋp�x��ς��ĉ�������݂�
		float escapeTbl[] = {
			0, -10, 10, -20, 20, -30, 30, -40, 40, -50, 50, -60, 60, -70, 70, -80, 80,
		};
		for (int i = 0; i < sizeof(escapeTbl) / sizeof(escapeTbl[0]); i++) {
			// escapeTbl[i]�̕������ړ���v��]
			float escape_rad = DEG2RAD(escapeTbl[i]);
			v.x = cos(rad + camrad + escape_rad) * length;
			v.z = sin(rad + camrad + escape_rad) * length;

			// v�̕��ړ�
			_vPos = VAdd(_vPos, v);

			// �ړ�������ŃR���W��������
			MV1_COLL_RESULT_POLY hitPoly;

			// ��l���̍��ʒu���牺�����ւ̒���
			hitPoly = MV1CollCheck_Line(_handleMap, _frameMapCollision,
										VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)));
			if (hitPoly.HitFlag) {
				// ��������
				// ��������Y�ʒu���L�������W�ɂ���
				_vPos.y = hitPoly.HitPosition.y;

				// �L�������㉺�Ɉړ������ʂ����A�ړ��ʂ��C��
				v.y += _vPos.y - oldvPos.y;

				// �J�������ړ�����
				_cam._vPos = VAdd(_cam._vPos, v);
				_cam._vTarget = VAdd(_cam._vTarget, v);

				// ���[�vi���甲����
				break;
			}
			else {
				// ������Ȃ������B���̍��W�ɖ߂�
				_vPos = oldvPos;
				v = oldv;
			}
		}

		// �ړ��ʂ����̂܂܃L�����̌����ɂ���
		if (VSize(v) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
			_vDir = v;
			_status = STATUS::WALK;
		}
		else {
			_status = STATUS::WAIT;
		}


		// ESC�L�[�Ń��j���[���J��
		if (trg & PAD_INPUT_9) {
			//ModeMenu* modeMenu = new ModeMenu();
			// ModeGame����̃��C���[�Ƀ��j���[��o�^����
			//ModeServer::GetInstance()->Add(modeMenu, 99, "menu");
		}

		// �f�o�b�O�@�\
		if (trg & PAD_INPUT_6) {
			_bViewCollision = !_bViewCollision;
		}
		if (_bViewCollision) {
			MV1SetFrameVisible(_handleMap, _frameMapCollision, TRUE);
		}
		else {
			MV1SetFrameVisible(_handleMap, _frameMapCollision, FALSE);
		}
	}

	// �X�e�[�^�X���ς���Ă��Ȃ����H
	if (oldStatus == _status) {
		// �Đ����Ԃ�i�߂�
		_play_time += 0.5f;
	}
	else {
		// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
		if (_attach_index != -1) {
			MV1DetachAnim(_handle, _attach_index);
			_attach_index = -1;
		}
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
		switch (_status) {
		case STATUS::WAIT:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "idle"), -1, FALSE);
			break;
		case STATUS::WALK:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "run"), -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_total_time = MV1GetAttachAnimTotalTime(_handle, _attach_index);
		// �Đ����Ԃ�������
		_play_time = 0.0f;
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (_play_time >= _total_time) {
		_play_time = 0.0f;
	}


	return true;
}

bool ModeGame::Render() {
	base::Render();

	// 3D��{�ݒ�
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// ���C�g�ݒ�
	SetUseLighting(TRUE);
#if 0	// ���s���C�g
	SetGlobalAmbientLight(GetColorF(0.5f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(VGet(-1, -1, 0));
#endif
#if 1	// �|�C���g���C�g
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypePoint(VAdd(_vPos, VGet(0, 50.f, 0)), 1000.f, 0.f, 0.005f, 0.f);
#endif

	// �J�����ݒ�X�V
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);

	// 0,0,0�𒆐S�ɐ�������
	{
		float linelength = 1000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	// �J�����^�[�Q�b�g�𒆐S�ɒZ����������
	{
		float linelength = 10.f;
		VECTOR v = _cam._vTarget;
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(_handle, _attach_index, _play_time);

	// ���f����`�悷��
	{
		// �ʒu
		MV1SetPosition(_handle, _vPos);
		// ��������Y����]���Z�o
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);		// ���f�����W���łǂ���������Ă��邩�Ŏ����ς��(�����-z�������Ă���ꍇ)
		MV1SetRotationXYZ(_handle, vRot);
		// �`��
		MV1DrawModel(_handle);

		// �R���W��������p���C���̕`��
		if (_bViewCollision) {
			DrawLine3D(VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));
		}

	}

	// �}�b�v���f����`�悷��
	{
		MV1DrawModel(_handleMap);
		MV1DrawModel(_handleSkySphere);
	}

	// �J�������\��
	{
		int x = 0, y = 0, size = 16;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _cam._vTarget.x, _cam._vTarget.y, _cam._vTarget.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _cam._vPos.x, _cam._vPos.y, _cam._vPos.z); y += size;
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float length = sqrt(sz * sz + sx * sx);
		float rad = atan2(sz, sx);
		float deg = RAD2DEG(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += size;
	}
	return true;
}

