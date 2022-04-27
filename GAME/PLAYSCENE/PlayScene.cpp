/*
プレイシーン
*/
#include "PlayScene.h"

#include "../GameMain.h"
#include"Player/Player.h"
#include"BulletManager/BulletManager.h"
#include"../Effect/Effect.h"
#include"FireworksManager/FireworksManager.h"
#include"../SaveData/SaveData.h"
#include"../Framework/ResourceManager.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
PlayScene::PlayScene()
	:mpPlayer(nullptr)
	, mpBulletManager(nullptr)
	, mpEffect(nullptr)
	, mpFireworksManager(nullptr)
	, mpSaveData(nullptr)
	, mCountTimer(240)
	, mScene(SCENE::COUNT)
	, mFontSize(0)
	, mFontSizeInterval(60)
	, mPlayTimer(3600)
	, mResultTimer(0)
	, mFadeTimer(255)
	, mScore(0)
	, mAngle(0.0f)
	, mScoreTexture(0)
	, mCannonTexture(0)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
PlayScene::~PlayScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void PlayScene::Initialize()
{
	mpPlayer = new Player();
	mpBulletManager = new BulletManager();
	mpEffect = new Effect();
	mpFireworksManager = new FireworksManager();
	mpSaveData = new SaveData();

	mpPlayer->Initialize(mpBulletManager);
	mpBulletManager->Initialize(mpPlayer, mpEffect, mpFireworksManager);
	mpEffect->Initialize();
	mpFireworksManager->Initialize(mpEffect,mpBulletManager,mpSaveData);
	mpSaveData->Save(mScore);

	//mpEffect->Play(0.0f, 0.0f, EFFECT_NUM::EFFECT_START);

	ResourceManager* pRm = ResourceManager::GetInstance();

	mScoreTexture = pRm->GetResource("all.png", TYPE::Textures);
	mCannonTexture = pRm->GetResource("Cannon.png", TYPE::Textures);
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE PlayScene::Update()
{
	mCountTimer--;
	mAngle += 0.1f;

	if (mpBulletManager != nullptr)
		mpBulletManager->Update();

	switch (mScene)
	{
		case SCENE::COUNT:
		{
			++mFontSize %= mFontSizeInterval;
			if (mCountTimer<60)
				mScene = SCENE::PLAY;
			break;
		}
		case SCENE::PLAY:
		{
			if (mPlayTimer > 0)
				mPlayTimer--;
			if (mpPlayer != nullptr)
				mpPlayer->Update();
			if (mpFireworksManager != nullptr)
				mpFireworksManager->Update();
			if (mPlayTimer == 0)
				mScene = SCENE::TIMEUP;
			break;
		}
		case SCENE::TIMEUP:
		{
			if (mFontSize < 200)
				mFontSize += 10;
			mResultTimer++;
			if (mResultTimer > 40)
				mFadeTimer-=5;
			
			if (mResultTimer > 200)
				return GAME_SCENE::RESULT;

			break;
		}
		default:
			break;
	}

	if (mpSaveData != nullptr)
	{
		if (mpSaveData->Road() - 10 > mScore)
		{
			mScore += 5;
		}
		else if (mpSaveData->Road() > mScore)
			mScore++;
	}
		
			
	if (mpEffect != nullptr)
		mpEffect->Update();
	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void PlayScene::Draw()
{
	DrawRectRotaGraph(
		73,//Xの位置
		400,//Yの位置
		0,//切り取り開始の位置
		0,//切り取り開始の位置
		1000,//切り取り終わりの位置
		1000,//切り取り終わりの位置
		0.4,//拡大
		0.0,//回転
		mCannonTexture,//アドレス
		TRUE
	);
	if (mpEffect != nullptr)
		mpEffect->Draw();
	if (mpFireworksManager != nullptr)
		mpFireworksManager->Draw();
	if (mpPlayer != nullptr)
		mpPlayer->Draw();
	if (mpBulletManager != nullptr)
		mpBulletManager->Draw();
	if (mPlayTimer / 60 >= 10)
		DrawFormatString(SCREEN_RIGHT - 26, 10, GetColor(255, 255, 255), "%d", mPlayTimer / 60);
	if (mPlayTimer / 60 < 10)
		DrawFormatString(SCREEN_RIGHT - 18, 10, GetColor(255, 255, 255), "%d", mPlayTimer / 60);

	switch (mScene)
	{
		case SCENE::COUNT:
		{
			if (mCountTimer > 60)
			{
				int Font = mFontSize * 3;
				SetFontSize(Font);
				DrawFormatString(SCREEN_CENTER_X - Font / 4, SCREEN_CENTER_Y - Font / 2, GetColor(255, 255, 255), "%d", mCountTimer / 60);
				SetFontSize(16);
			}
			else if (mCountTimer > 0 && mScene == SCENE::PLAY)
			{
				int Font = 200;
				SetFontSize(Font);
				DrawFormatString(SCREEN_CENTER_X - Font - 50, SCREEN_CENTER_Y - Font / 2, GetColor(255, 255, 255), "START");
				SetFontSize(16);
			}
			break;
		}
		case SCENE::PLAY:
		{
			break;
		}
		case SCENE::TIMEUP:
		{
			SetFontSize(mFontSize);
			DrawFormatString(SCREEN_CENTER_X - (mFontSize / 4) * 6, SCREEN_CENTER_Y - mFontSize / 2, GetColor(255, 255, 255), "TIMEUP");
			SetFontSize(16);
			break;
		}
		default:
			break;
	}
	ScoreUI();
	SetDrawBright(mFadeTimer, mFadeTimer, mFadeTimer);
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void PlayScene::Finalize()
{
	if (mpPlayer != nullptr)
	{
		mpPlayer->Finalize();
		delete mpPlayer;
		mpPlayer = nullptr;
	}

	if (mpBulletManager != nullptr)
	{
		mpBulletManager->Finalize();
		delete mpBulletManager;
		mpBulletManager = nullptr;
	}

	if (mpEffect != nullptr)
	{
		mpEffect->Finalize();
		delete mpEffect;
		mpEffect = nullptr;
	}

	if (mpFireworksManager != nullptr)
	{
		mpFireworksManager->Finalize();
		delete mpFireworksManager;
		mpFireworksManager = nullptr;
	}

	if (mpSaveData != nullptr)
	{
		delete mpSaveData;
		mpSaveData = nullptr;
	}

	ResourceManager* pRm = ResourceManager::GetInstance();
	pRm->DeleteResource();
}

void PlayScene::ScoreUI()
{
	int PosX = 100;
	int PosY = 90;

	int x = mScore;
	int Y = 0;

	for (int i = 0; i < 5; i++)
	{
		int a = 0;

		a = x % 10;
		if (i == 0 || i == 2 || i == 4)
			Y = PosY + (1 * cos(mAngle));
		if (i == 1 || i == 3)
			Y = PosY + (1 * sin(mAngle));
		DrawRectRotaGraph(
			PosX,//Xの位置
			Y,//Yの位置
			0 + a * 16,//切り取り開始の位置
			32,//切り取り開始の位置
			16,//切り取り終わりの位置
			23,//切り取り終わりの位置
			1,//拡大
			0.0,//回転
			mScoreTexture,//アドレス
			TRUE
		);
		PosX -= 15;
		x /= 10;
	}
}