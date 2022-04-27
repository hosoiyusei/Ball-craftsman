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

	// コンストラクタ
	ResultScene();

	// デストラクタ
	~ResultScene();

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