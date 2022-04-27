/*
プレイシーン
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

	// コンストラクタ
	PlayScene();

	// デストラクタ
	~PlayScene();

	// 初期化
	void Initialize() override;

	// 更新
	GAME_SCENE Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

private:

	void ScoreUI();
};