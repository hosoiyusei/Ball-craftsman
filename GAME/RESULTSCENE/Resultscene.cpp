#include "Resultscene.h"

#include "../GameMain.h"
#include"../SaveData/SaveData.h"
#include"../Framework/ResourceManager.h"
#include<math.h>

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
ResultScene::ResultScene()
	:mFadeTimer(0)
	, mpSaveData(nullptr)
	, mScoreTexture(0)
	, mScore(0)
	,mAngle(0.0f)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
ResultScene::~ResultScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void ResultScene::Initialize()
{
	mpSaveData = new SaveData();

	ResourceManager* pRm = ResourceManager::GetInstance();

	mScoreTexture = pRm->GetResource("all.png", TYPE::Textures);
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE ResultScene::Update()
{
	if (mFadeTimer < 255)
		mFadeTimer += 5;
	if (mpSaveData != nullptr)
	{
		if (mpSaveData->Road() - 100 > mScore)
		{
			mScore += 100;
		}
		else if (mpSaveData->Road() > mScore)
		{
			mScore++;
		}
		else
		{
			mAngle += 0.1f;
			if (IsButtonPressed(PAD_INPUT_1) && mFadeTimer == 255)
			{
				return GAME_SCENE::TITLE;
			}
		}
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void ResultScene::Draw()
{
	SetDrawBright(mFadeTimer, mFadeTimer, mFadeTimer);

	SetFontSize(60);
	DrawString(230, 30, "Result", GetColor(255, 255, 255));
	SetFontSize(16);
	ScoreUI();
	DrawString(100, 240, "スコア", GetColor(255, 255, 255));
	SetFontSize(20);
	DrawString(400, 400, "Input ZKey", GetColor(
		static_cast<int>(205 - (50 * sin(mAngle))),
		static_cast<int>(205 - (50 * sin(mAngle))),
		static_cast<int>(205 - (50 * sin(mAngle)))));
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void ResultScene::Finalize()
{
	ResourceManager* pRm = ResourceManager::GetInstance();
	pRm->DeleteResource();

	if (mpSaveData != nullptr)
	{
		delete mpSaveData;
		mpSaveData = nullptr;
	}
}

void ResultScene::ScoreUI()
{
	int PosX = 500;
	int PosY = 90;

	int x = mScore;
	int Y = 240;

	for (int i = 0; i < 5; i++)
	{
		int a = 0;

		a = x % 10;
		
		DrawRectRotaGraph(
			PosX,//Xの位置
			Y,//Yの位置
			0 + a * 16,//切り取り開始の位置
			32,//切り取り開始の位置
			16,//切り取り終わりの位置
			23,//切り取り終わりの位置
			2,//拡大
			0.0,//回転
			mScoreTexture,//アドレス
			TRUE
		);
		PosX -= 30;
		x /= 10;
	}
}