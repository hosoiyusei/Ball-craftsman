/*
�v���C�V�[��
*/
#pragma once

#include "../IScene.h"

enum class SCENE :int
{
	COUNT,
	PLAY,
	TIMEUP,
};

class Player;
class BulletManager;
class Effect;
class FireworksManager;
class SaveData;

class PlayScene : public IScene
{
private:

	Player* mpPlayer;

	BulletManager* mpBulletManager;

	Effect* mpEffect;

	FireworksManager* mpFireworksManager;

	SaveData* mpSaveData;

	int mCountTimer;

	SCENE mScene;

	int mFontSize;

	int mFontSizeInterval;

	int mPlayTimer;

	int mResultTimer;

	int mFadeTimer;

	int mScore;

	float mAngle;

	int mScoreTexture;

	int mCannonTexture;

public:

	// �R���X�g���N�^
	PlayScene();

	// �f�X�g���N�^
	~PlayScene();

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