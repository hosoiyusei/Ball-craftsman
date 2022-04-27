/*
タイトルシーン
*/
#include "TitleScene.h"

#include "../GameMain.h"
#include"../Framework/ResourceManager.h"
#include"../Effect/Effect.h"
#include"SoundWave/SoundWave.h"
#include<math.h>
#include"../SaveData/SaveData.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
TitleScene::TitleScene()
	:mTest(0)
	, mpEffect(nullptr)
	, mpSoundWave(nullptr)
	, mpSaveData(nullptr)
	, mAngle(0.0f)
	, mmozi(0)
	, mAccent(0)
	, mhanabi(0)
	, mMouse_X(0)
	, mMouse_Y(0)
	, msirome(0)
	, mkurome(0)
	, mX(0.0f)
	, mY(0.0f)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
TitleScene::~TitleScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void TitleScene::Initialize()
{
	ResourceManager* pRm = ResourceManager::GetInstance();

	mTest = pRm->GetResource("bomb.png", TYPE::Textures);
	mmozi = pRm->GetResource("mozi.png", TYPE::Textures);
	mAccent= pRm->GetResource("Accent.png", TYPE::Textures);
	mhanabi= pRm->GetResource("hanabi.png", TYPE::Textures);
	msirome= pRm->GetResource("sirome.png", TYPE::Textures);
	mkurome= pRm->GetResource("kurome.png", TYPE::Textures);

	mpEffect = new Effect();
	mpSoundWave = new SoundWave();
	mpSaveData = new SaveData();
	
	mpEffect->Initialize();
	mpSoundWave->Initialize();
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE TitleScene::Update()
{
	SetMouseDispFlag(FALSE);

	if (mpEffect != nullptr)
		mpEffect->Update();
	if (mpSoundWave != nullptr)
		mpSoundWave->Update();

	GetMousePoint(&mMouse_X, &mMouse_Y);

	SetAngle();

	if (IsButtonPressed(PAD_INPUT_1))
	{
		return GAME_SCENE::PLAY;
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void TitleScene::Draw()
{
	if (mpSoundWave != nullptr)
		mpSoundWave->DrawWave();

	if (mpEffect != nullptr)
		mpEffect->Draw();

	DrawRectRotaGraph(
		SCREEN_CENTER_X,//Xの位置
		SCREEN_CENTER_Y-30,//Yの位置
		0,//切り取り開始の位置
		0,//切り取り開始の位置
		2500,//切り取り終わりの位置
		1500,//切り取り終わりの位置
		0.3,//拡大
		0.0,//回転
		msirome,//アドレス
		TRUE
	);

	DrawRectRotaGraph(
		mMouse_X,//Xの位置
		mMouse_Y,//Yの位置
		0,//切り取り開始の位置
		0,//切り取り開始の位置
		2500,//切り取り終わりの位置
		1500,//切り取り終わりの位置
		0.05,//拡大
		0.0,//回転
		mTest,//アドレス
		TRUE
	);

	DrawRectRotaGraph(
		SCREEN_CENTER_X,//Xの位置
		SCREEN_CENTER_Y - 180,//Yの位置
		0,//切り取り開始の位置
		0,//切り取り開始の位置
		2500,//切り取り終わりの位置
		1500,//切り取り終わりの位置
		0.3,//拡大
		0.0,//回転
		mmozi,//アドレス
		TRUE
	);

	DrawRectRotaGraph(
		SCREEN_CENTER_X-10,//Xの位置
		SCREEN_CENTER_Y - 190,//Yの位置
		0,//切り取り開始の位置
		0,//切り取り開始の位置
		2500,//切り取り終わりの位置
		1500,//切り取り終わりの位置
		0.3,//拡大
		0.0,//回転
		mAccent,//アドレス
		TRUE
	);

	DrawRectRotaGraph(
		SCREEN_CENTER_X-42+mX,//Xの位置
		SCREEN_CENTER_Y+mY,//Yの位置
		0,//切り取り開始の位置
		0,//切り取り開始の位置
		2500,//切り取り終わりの位置
		1500,//切り取り終わりの位置
		0.3,//拡大
		0.0,//回転
		mkurome,//アドレス
		TRUE
	);
	DrawRectRotaGraph(
		SCREEN_CENTER_X + 33+mX,//Xの位置
		SCREEN_CENTER_Y+mY,//Yの位置
		0,//切り取り開始の位置
		0,//切り取り開始の位置
		2500,//切り取り終わりの位置
		1500,//切り取り終わりの位置
		0.3,//拡大
		0.0,//回転
		mkurome,//アドレス
		TRUE
	);

	SetFontSize(25);
	DrawString(400, 300, "スタート", GetColor(255, 255, 255), TRUE);
	DrawString(400, 350, "Push Z Key", GetColor(255, 255, 255), TRUE);
	DrawString(70, 300, "前回のスコア", GetColor(255, 255, 255), TRUE);
	if (mpSaveData != nullptr)
		DrawFormatString(70, 350, GetColor(255, 255, 255), "%d", mpSaveData->Road());
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void TitleScene::Finalize()
{
	if (mpEffect != nullptr)
	{
		mpEffect->Finalize();
		delete mpEffect;
		mpEffect = nullptr;
	}

	if (mpSoundWave != nullptr)
	{
		mpSoundWave->Finalize();
		delete mpSoundWave;
		mpSoundWave = nullptr;
	}

	if (mpSaveData != nullptr)
	{
		delete mpSaveData;
		mpSaveData = nullptr;
	}

	ResourceManager* pRm = ResourceManager::GetInstance();
	pRm->DeleteResource();
}


void TitleScene::SetAngle()
{
	mAngle= atan2f(mMouse_Y - SCREEN_CENTER_Y, mMouse_X - SCREEN_CENTER_X);
	mX = 7.0f * cos(mAngle);
	mY = 7.0f * sin(mAngle);
}