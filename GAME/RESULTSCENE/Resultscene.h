#pragma once

#include "../IScene.h"

class SaveData;

class ResultScene : public IScene
{
private:

	int mFadeTimer;

	int mScoreTexture;

	int mScore;

	float mAngle;

	SaveData* mpSaveData;

public:

	// �R���X�g���N�^
	ResultScene();

	// �f�X�g���N�^
	~ResultScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

private:

	void ScoreUI();
};