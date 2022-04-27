#include "Resultscene.h"

#include "../GameMain.h"
#include"../SaveData/SaveData.h"
#include"../Framework/ResourceManager.h"
#include<math.h>

/*--------------------------------------------------
�R���X�g���N�^
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
�f�X�g���N�^
--------------------------------------------------*/
ResultScene::~ResultScene()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void ResultScene::Initialize()
{
	mpSaveData = new SaveData();

	ResourceManager* pRm = ResourceManager::GetInstance();

	mScoreTexture = pRm->GetResource("all.png", TYPE::Textures);
}

/*--------------------------------------------------
�X�V
�߂�l	:���̃V�[���ԍ�
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
�`��
--------------------------------------------------*/
void ResultScene::Draw()
{
	SetDrawBright(mFadeTimer, mFadeTimer, mFadeTimer);

	SetFontSize(60);
	DrawString(230, 30, "Result", GetColor(255, 255, 255));
	SetFontSize(16);
	ScoreUI();
	DrawString(100, 240, "�X�R�A", GetColor(255, 255, 255));
	SetFontSize(20);
	DrawString(400, 400, "Input ZKey", GetColor(
		static_cast<int>(205 - (50 * sin(mAngle))),
		static_cast<int>(205 - (50 * sin(mAngle))),
		static_cast<int>(205 - (50 * sin(mAngle)))));
}

/*--------------------------------------------------
�I������
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
			PosX,//X�̈ʒu
			Y,//Y�̈ʒu
			0 + a * 16,//�؂���J�n�̈ʒu
			32,//�؂���J�n�̈ʒu
			16,//�؂���I���̈ʒu
			23,//�؂���I���̈ʒu
			2,//�g��
			0.0,//��]
			mScoreTexture,//�A�h���X
			TRUE
		);
		PosX -= 30;
		x /= 10;
	}
}