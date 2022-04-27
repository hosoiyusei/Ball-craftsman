/*
�^�C�g���V�[��
*/
#include "TitleScene.h"

#include "../GameMain.h"
#include"../Framework/ResourceManager.h"
#include"../Effect/Effect.h"
#include"SoundWave/SoundWave.h"
#include<math.h>
#include"../SaveData/SaveData.h"

/*--------------------------------------------------
�R���X�g���N�^
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
�f�X�g���N�^
--------------------------------------------------*/
TitleScene::~TitleScene()
{
}

/*--------------------------------------------------
������
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
�X�V
�߂�l	:���̃V�[���ԍ�
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
�`��
--------------------------------------------------*/
void TitleScene::Draw()
{
	if (mpSoundWave != nullptr)
		mpSoundWave->DrawWave();

	if (mpEffect != nullptr)
		mpEffect->Draw();

	DrawRectRotaGraph(
		SCREEN_CENTER_X,//X�̈ʒu
		SCREEN_CENTER_Y-30,//Y�̈ʒu
		0,//�؂���J�n�̈ʒu
		0,//�؂���J�n�̈ʒu
		2500,//�؂���I���̈ʒu
		1500,//�؂���I���̈ʒu
		0.3,//�g��
		0.0,//��]
		msirome,//�A�h���X
		TRUE
	);

	DrawRectRotaGraph(
		mMouse_X,//X�̈ʒu
		mMouse_Y,//Y�̈ʒu
		0,//�؂���J�n�̈ʒu
		0,//�؂���J�n�̈ʒu
		2500,//�؂���I���̈ʒu
		1500,//�؂���I���̈ʒu
		0.05,//�g��
		0.0,//��]
		mTest,//�A�h���X
		TRUE
	);

	DrawRectRotaGraph(
		SCREEN_CENTER_X,//X�̈ʒu
		SCREEN_CENTER_Y - 180,//Y�̈ʒu
		0,//�؂���J�n�̈ʒu
		0,//�؂���J�n�̈ʒu
		2500,//�؂���I���̈ʒu
		1500,//�؂���I���̈ʒu
		0.3,//�g��
		0.0,//��]
		mmozi,//�A�h���X
		TRUE
	);

	DrawRectRotaGraph(
		SCREEN_CENTER_X-10,//X�̈ʒu
		SCREEN_CENTER_Y - 190,//Y�̈ʒu
		0,//�؂���J�n�̈ʒu
		0,//�؂���J�n�̈ʒu
		2500,//�؂���I���̈ʒu
		1500,//�؂���I���̈ʒu
		0.3,//�g��
		0.0,//��]
		mAccent,//�A�h���X
		TRUE
	);

	DrawRectRotaGraph(
		SCREEN_CENTER_X-42+mX,//X�̈ʒu
		SCREEN_CENTER_Y+mY,//Y�̈ʒu
		0,//�؂���J�n�̈ʒu
		0,//�؂���J�n�̈ʒu
		2500,//�؂���I���̈ʒu
		1500,//�؂���I���̈ʒu
		0.3,//�g��
		0.0,//��]
		mkurome,//�A�h���X
		TRUE
	);
	DrawRectRotaGraph(
		SCREEN_CENTER_X + 33+mX,//X�̈ʒu
		SCREEN_CENTER_Y+mY,//Y�̈ʒu
		0,//�؂���J�n�̈ʒu
		0,//�؂���J�n�̈ʒu
		2500,//�؂���I���̈ʒu
		1500,//�؂���I���̈ʒu
		0.3,//�g��
		0.0,//��]
		mkurome,//�A�h���X
		TRUE
	);

	SetFontSize(25);
	DrawString(400, 300, "�X�^�[�g", GetColor(255, 255, 255), TRUE);
	DrawString(400, 350, "Push Z Key", GetColor(255, 255, 255), TRUE);
	DrawString(70, 300, "�O��̃X�R�A", GetColor(255, 255, 255), TRUE);
	if (mpSaveData != nullptr)
		DrawFormatString(70, 350, GetColor(255, 255, 255), "%d", mpSaveData->Road());
}

/*--------------------------------------------------
�I������
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