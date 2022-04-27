#include"FireworksManager.h"
#include <random>
#include"../BulletManager/BulletManager.h"
#include"../BulletManager/Bullet/Bullet_0.h"
#include"FireworksType.h"
#include"../BulletManager/BulletType.h"
#include"../../Framework/ResourceManager.h"
#include"../../SaveData/SaveData.h"
#include"../../Effect/Effect.h"

#include"Fireworks/Fireworks_0.h"
#include"Fireworks/Fireworks_1.h"

FireworksManager::FireworksManager()
	:mpFireworks()
	, mpEffect(nullptr)
	, mpBulletManager(nullptr)
	, mpSaveData(nullptr)
	, mCreateTimer(0)
	, mCreateInterval(100)
	, mNum(0)
	, mFeverGage(130.0f)
	, mFeverFlag(false)
	, mExplosionSE(0)
	, mScore(0)
	, mFeverEffectTimer(0)
	,mRed(255)
	,mGreen(255)
	,mBlue(255)
	, mColorswitch(255)
{

}

FireworksManager::~FireworksManager()
{

}

void FireworksManager::Initialize(Effect* pEffect, BulletManager* pBulletManager,SaveData* pSaveData)
{
	mpEffect = pEffect;
	mpBulletManager = pBulletManager;
	mpSaveData = pSaveData;
	ResourceManager* pRm = ResourceManager::GetInstance();
	mExplosionSE = pRm->GetResource("Explosion.mp3", TYPE::Audio);
	if (mpSaveData != nullptr)
		mpSaveData->Save(mScore);
}

void FireworksManager::Update()
{
	for (std::list<Fireworks*>::iterator itr = mpFireworks.begin(); itr != mpFireworks.end(); itr++)
	{
		if ((*itr) != nullptr)
			(*itr)->Update();
	}

	++mCreateTimer %= mCreateInterval;

	if (mCreateTimer == 0 && mFeverFlag == false)
		Create();

	if (mFeverFlag == true)
	{
		CreateFever();
		++mFeverEffectTimer %= 3;
		if (mFeverEffectTimer == 0 && mpBulletManager != nullptr)
		{
			mpBulletManager->FeverEffectBullet(50.0f, 480.0f);
			mpBulletManager->FeverEffectBullet(320.0f, 480.0f);
			mpBulletManager->FeverEffectBullet(590.0f, 480.0f);
		}
			
	}

	if (mFeverFlag == true)
	{
		Rainbow();
	}
	else
	{
		mRed = 255;
		mGreen = 255;
		mBlue = 255;
	}
		

	Fever();
	DeleteTime();
}

void FireworksManager::Draw()
{
	for (std::list<Fireworks*>::iterator itr = mpFireworks.begin(); itr != mpFireworks.end(); itr++)
	{
		if ((*itr) != nullptr)
			(*itr)->Draw();
	}

	//フィーバーゲージ
	DrawRoundRect(130, 440, 530, 460, 10, 10, GetColor(0, 0, 0), TRUE);
	DrawRoundRect(130, 440, static_cast<int>(mFeverGage), 460, 10, 10, GetColor(255, 255, 100), TRUE);
	DrawRoundRect(130, 440, 530, 460, 10, 10, GetColor(mRed, mGreen, mBlue), FALSE);
	DrawFormatString(310, 442, GetColor(mRed, mGreen, mBlue), "FEVER");
}

void FireworksManager::Finalize()
{
	for (std::list<Fireworks*>::iterator itr = mpFireworks.begin(); itr != mpFireworks.end(); itr++)
	{
		if ((*itr) != nullptr)
		{
			(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
		}
	}
	mpFireworks.clear();
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void FireworksManager::Create()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> distX(250, 540);
	std::uniform_int_distribution<int> distY(100, 280);
	std::uniform_int_distribution<int> distColor(0, 4);

	mNum = distColor(mt);

	float X=static_cast<float>(distX(mt));
	float Y=static_cast<float>(distY(mt));

	if (mpFireworks.size() < 3)
	{
		mpFireworks.push_back(new Fireworks_0());
		std::list<Fireworks*>::iterator itr = mpFireworks.end();
		(--itr);
		if (mNum == 0)
		{
			(*itr)->Initialize(X, Y, FIREWORKS_TYPE::TYPE_RED);
		}
		else if (mNum == 1)
		{
			(*itr)->Initialize(X, Y, FIREWORKS_TYPE::TYPE_ORANGE);
		}
		else if (mNum == 2)
		{
			(*itr)->Initialize(X, Y, FIREWORKS_TYPE::TYPE_YELLOW);
		}
		else if (mNum == 3)
		{
			(*itr)->Initialize(X, Y, FIREWORKS_TYPE::TYPE_GREEN);
		}
		else if (mNum == 4)
		{
			(*itr)->Initialize(X, Y, FIREWORKS_TYPE::TYPE_BLUE);
		}
	}
}

void FireworksManager::CreateFever()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> distColor(0, 4);
	mNum = distColor(mt);
	if (mpFireworks.size() < 1)
	{
		mpFireworks.push_back(new Fireworks_1());
		std::list<Fireworks*>::iterator itr = mpFireworks.end();
		(--itr);
		if (mNum == 0)
		{
			(*itr)->Initialize(395.0f, 190.0f, FIREWORKS_TYPE::TYPE_RED);
		}
		else if (mNum == 1)
		{
			(*itr)->Initialize(395.0f, 190.0f, FIREWORKS_TYPE::TYPE_ORANGE);
		}
		else if (mNum == 2)
		{
			(*itr)->Initialize(395.0f, 190.0f, FIREWORKS_TYPE::TYPE_YELLOW);
		}
		else if (mNum == 3)
		{
			(*itr)->Initialize(395.0f, 190.0f, FIREWORKS_TYPE::TYPE_GREEN);
		}
		else if (mNum == 4)
		{
			(*itr)->Initialize(395.0f, 190.0f, FIREWORKS_TYPE::TYPE_BLUE);
		}
	}
}

void FireworksManager::DeleteTime()
{
	for (std::list<Fireworks*>::iterator itr = mpFireworks.begin(); itr != mpFireworks.end();)
	{
		if ((*itr) == nullptr)
		{
			itr++;
			continue;
		}
			
		if ((*itr)->Active() == false)
		{
			(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
			itr = mpFireworks.erase(itr);
			continue;
		}
		itr++;
	}
}

void FireworksManager::Delete(std::list<Bullet*>::iterator pBulletitr)
{
	std::mt19937 mt{ std::random_device{}() };
	for (std::list<Fireworks*>::iterator itr = mpFireworks.begin(); itr != mpFireworks.end();)
	{
		if ((*itr) == nullptr)
			continue;
		if ((*itr)->Collision().CheckHit((*pBulletitr)->Collision()) == true &&
			(*pBulletitr)->Type() == BULLET_TYPE::TYPE_PLAYER &&
			IsButtonPressed(PAD_INPUT_10) == TRUE)
		{
			PlaySoundMem(mExplosionSE, DX_PLAYTYPE_BACK, TRUE);
			ChangeVolumeSoundMem(255, mExplosionSE);
			if (mFeverFlag == false && mpBulletManager != nullptr)
				mpBulletManager->Explosion((*itr)->GetPos(), (*itr)->Type());//FEVERじゃないときの弾タイプ
			if (mFeverFlag == true && mpBulletManager != nullptr)
				mpBulletManager->FeverExplosion((*itr)->GetPos(), (*itr)->Type());//FEVERの時の弾タイプ
			if (
				(*itr)->Type() == FIREWORKS_TYPE::TYPE_RED && (*pBulletitr)->BulletColor() == BULLET_COLOR::TYPE_RED ||
				(*itr)->Type() == FIREWORKS_TYPE::TYPE_ORANGE && (*pBulletitr)->BulletColor() == BULLET_COLOR::TYPE_ORANGE ||
				(*itr)->Type() == FIREWORKS_TYPE::TYPE_YELLOW && (*pBulletitr)->BulletColor() == BULLET_COLOR::TYPE_YELLOW ||
				(*itr)->Type() == FIREWORKS_TYPE::TYPE_GREEN && (*pBulletitr)->BulletColor() == BULLET_COLOR::TYPE_GREEN ||
				(*itr)->Type() == FIREWORKS_TYPE::TYPE_BLUE && (*pBulletitr)->BulletColor() == BULLET_COLOR::TYPE_BLUE
				)//色が一緒だったとき
			{
				if (mFeverFlag == false)
					(*itr)->EffectPlay2(mpEffect);
				if(mFeverFlag==true)
					(*itr)->EffectPlay(mpEffect);
				if (mFeverFlag == false)
				{
					if (mFeverGage + 40.0f > 530)
					{
						mFeverGage = 530;
						mFeverFlag = true;
					}
					else
					{
						mFeverGage += 40.0f;
					}
				}
				
				std::uniform_int_distribution<int> distS(300, 400);
				mScore += distS(mt);
				if (mpSaveData != nullptr)
					mpSaveData->Save(mScore);
			}
			else//違う色だった時
			{
				(*itr)->EffectPlay(mpEffect);
				if (mFeverFlag == false)
				{
					if (mFeverGage + 20.0f > 530)
					{
						mFeverGage = 530;
						mFeverFlag = true;
					}
					else
					{
						mFeverGage += 20.0f;
					}
				}
				std::uniform_int_distribution<int> distS(100, 200);
				mScore += distS(mt);
				if (mpSaveData != nullptr)
					mpSaveData->Save(mScore);
			}
			(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
			itr = mpFireworks.erase(itr);
			continue;
		}
		itr++;
	}
}

void FireworksManager::Fever()
{
	if (mFeverGage == 529.0f)
		Finalize();
	if (mFeverFlag == true)
		mFeverGage -= 0.5f;
	if (mFeverGage < 130 && mFeverFlag == true)
	{
		mFeverGage = 130;
		mFeverFlag = false;
		Finalize();
	}
	if (IsButtonPressed(PAD_INPUT_5) == TRUE)
	{
		mFeverGage += 100.0f; 
		mFeverFlag = true;
	}
}

void FireworksManager::Rainbow()
{
	switch (mColorswitch)
	{
		case 0:
		{
			mGreen += 5;
			if (mGreen > 250)
				mColorswitch = 1;
			break;
		}
		case 1:
		{
			mRed -= 5;

			if (mRed < 5)
				mColorswitch = 5;
			break;
		}
		case 2:
		{
			mGreen -= 5;
			if (mGreen < 5)
				mColorswitch = 3;
			break;
		}
		case 3:
		{
			mRed += 5;
			if (mRed > 250)
				mColorswitch = 4;
			break;
		}
		case 4:
		{
			mBlue -= 5;
			if (mBlue < 5)
				mColorswitch = 0;
			break;
		}
		case 5:
		{
			mBlue += 5;
			if (mBlue > 250)
				mColorswitch = 2;
			break;
		}
		default:
			break;
	}
}