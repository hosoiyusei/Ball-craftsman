/*
�^�C�g���V�[��
*/
#pragma once

#include "../IScene.h"

class Effect;
class SoundWave;
class SaveData;

class TitleScene : public IScene
{
private:

	int mTest;

	float mAngle;

	int mmozi, mhanabi, mAccent, msirome, mkurome;

	int mMouse_X, mMouse_Y;

	float mX, mY;

	Effect* mpEffect;

	SoundWave* mpSoundWave;

	SaveData* mpSaveData;

public:

	// �R���X�g���N�^
	TitleScene();

	// �f�X�g���N�^
	~TitleScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

private:

	void SetAngle();
};