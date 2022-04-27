/*
タイトルシーン
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

	// コンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

	// 初期化
	void Initialize() override;

	// 更新
	GAME_SCENE Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

private:

	void SetAngle();
};