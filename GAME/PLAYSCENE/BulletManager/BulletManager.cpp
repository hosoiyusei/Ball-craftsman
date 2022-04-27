#include"BulletManager.h"
#include"../../GameMain.h"
#include"../Player/Player.h"
#include"../FireworksManager/FireworksManager.h"
#include"../../Framework/ResourceManager.h"

#include"Bullet/Bullet_0.h"
#include"Bullet/Bullet_1.h"
#include"Bullet/Bullet_2.h"

BulletManager::BulletManager()
	:mpBullet()
	, mpPlayer(nullptr)
	, mpEffect(nullptr)
	, mpFireworksManager(nullptr)
	, mBulletColorNum(1)
	, mCannonSE(0)
	, mColor(BULLET_COLOR::TYPE_RED)
{

}

BulletManager::~BulletManager()
{

}

void BulletManager::Initialize(Player* pPlayer,Effect* pEffect, FireworksManager* pFireworksManager)
{
	mpPlayer = pPlayer;
	mpEffect = pEffect;
	mpFireworksManager = pFireworksManager;
	ResourceManager* pRm = ResourceManager::GetInstance();
	mCannonSE = pRm->GetResource("Cannon.mp3", TYPE::Audio);
}

void BulletManager::Update()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end(); itr++)
	{
		if ((*itr) != nullptr)
			(*itr)->Update();
	}
	if (IsButtonPressed(PAD_INPUT_10) == TRUE)
	{
		DeleteFireworks();
		PlayerBulletDelete();
		if (mpPlayer != nullptr)
			mpPlayer->Reset();
	}
	DeleteBullet();

	if (mpFireworksManager != nullptr)
		BulletColorChange();
}

void BulletManager::Draw()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end(); itr++)
	{
		if ((*itr) != nullptr)
			(*itr)->Draw();
	}
	DrawRoundRect(30, 30, 230, 70, 20, 20, GetColor(255, 255, 255), FALSE);
	DrawCircle(63, 50, 10, GetColor(255, 0, 0), TRUE);
	DrawCircle(96, 50, 10, GetColor(255, 100, 0), TRUE);
	DrawCircle(129, 50, 10, GetColor(255, 255, 0), TRUE);
	DrawCircle(162, 50, 10, GetColor(0, 255, 0), TRUE);
	DrawCircle(195, 50, 10, GetColor(0, 100, 255), TRUE);

	if (mpFireworksManager != nullptr)
	{
		if (mpFireworksManager->FeverFlag() == true)
		{
			DrawCircle(63, 50, 10, GetColor(255, 255, 255), TRUE);
			DrawCircle(96, 50, 10, GetColor(255, 255, 255), TRUE);
			DrawCircle(129, 50, 10, GetColor(255, 255, 255), TRUE);
			DrawCircle(162, 50, 10, GetColor(255, 255, 255), TRUE);
			DrawCircle(195, 50, 10, GetColor(255, 255, 255), TRUE);
		}
	}

	if (mBulletColorNum == 1)
	{
		DrawCircle(63, 50, 15, GetColor(255, 255, 255), FALSE);
	}
	else if (mBulletColorNum == 2)
	{
		DrawCircle(96, 50, 15, GetColor(255, 255, 255), FALSE);
	}
	else if (mBulletColorNum == 3)
	{
		DrawCircle(129, 50, 15, GetColor(255, 255, 255), FALSE);
	}
	else if (mBulletColorNum == 4)
	{
		DrawCircle(162, 50, 15, GetColor(255, 255, 255), FALSE);
	}
	else if (mBulletColorNum == 5)
	{
		DrawCircle(195, 50, 15, GetColor(255, 255, 255), FALSE);
	}
}

void BulletManager::Finalize()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end(); itr++)
	{
		if ((*itr) != nullptr)
		{
			(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
		}	
	}
	mpBullet.clear();
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void BulletManager::Shot(Float2 pos, float vx, float vy)
{
	mpBullet.push_back(new Bullet_0());
	std::list<Bullet*>::iterator itr = mpBullet.end();
	(--itr);
	if (mpFireworksManager != nullptr)
	{
		if (mpFireworksManager->FeverFlag() == true)
		{
			(*itr)->Initialize(pos, vx, vy, BULLET_TYPE::TYPE_PLAYER, FIREWORKS_TYPE::TYPE_NORMAL, BULLET_COLOR::TYPE_FEVER, mpFireworksManager);//フィーバー
		}
		else if (mBulletColorNum == 1)
		{
			(*itr)->Initialize(pos, vx, vy, BULLET_TYPE::TYPE_PLAYER, FIREWORKS_TYPE::TYPE_NORMAL, BULLET_COLOR::TYPE_RED, mpFireworksManager);
		}
		else if (mBulletColorNum == 2)
		{
			(*itr)->Initialize(pos, vx, vy, BULLET_TYPE::TYPE_PLAYER, FIREWORKS_TYPE::TYPE_NORMAL, BULLET_COLOR::TYPE_ORANGE, mpFireworksManager);
		}
		else if (mBulletColorNum == 3)
		{
			(*itr)->Initialize(pos, vx, vy, BULLET_TYPE::TYPE_PLAYER, FIREWORKS_TYPE::TYPE_NORMAL, BULLET_COLOR::TYPE_YELLOW, mpFireworksManager);
		}
		else if (mBulletColorNum == 4)
		{
			(*itr)->Initialize(pos, vx, vy, BULLET_TYPE::TYPE_PLAYER, FIREWORKS_TYPE::TYPE_NORMAL, BULLET_COLOR::TYPE_GREEN, mpFireworksManager);
		}
		else if (mBulletColorNum == 5)
		{
			(*itr)->Initialize(pos, vx, vy, BULLET_TYPE::TYPE_PLAYER, FIREWORKS_TYPE::TYPE_NORMAL, BULLET_COLOR::TYPE_BLUE, mpFireworksManager);
		}
	}
	
	PlaySoundMem(mCannonSE, DX_PLAYTYPE_BACK, TRUE);
	ChangeVolumeSoundMem(255, mCannonSE);
}

void BulletManager::BulletColorChange()
{
	if (mpFireworksManager->FeverFlag() == true)
	{
		mColor = BULLET_COLOR::TYPE_FEVER;
	}
	else if (CheckHitKey(KEY_INPUT_1) == TRUE)
	{
		mBulletColorNum = 1;
		mColor = BULLET_COLOR::TYPE_RED;
	}
	else if (CheckHitKey(KEY_INPUT_2) == TRUE)
	{
		mBulletColorNum = 2;
		mColor = BULLET_COLOR::TYPE_ORANGE;
	}
	else if (CheckHitKey(KEY_INPUT_3) == TRUE)
	{
		mBulletColorNum = 3;
		mColor = BULLET_COLOR::TYPE_YELLOW;
	}
	else if (CheckHitKey(KEY_INPUT_4) == TRUE)
	{
		mBulletColorNum = 4;
		mColor = BULLET_COLOR::TYPE_GREEN;
	}
	else if (CheckHitKey(KEY_INPUT_5) == TRUE)
	{
		mBulletColorNum = 5;
		mColor = BULLET_COLOR::TYPE_BLUE;
	}

	if (mpFireworksManager->FeverFlag() == false)
	{
		if (mBulletColorNum == 1)
		{
			mColor = BULLET_COLOR::TYPE_RED;
		}
		else if (mBulletColorNum == 2)
		{
			mColor = BULLET_COLOR::TYPE_ORANGE;
		}
		else if (mBulletColorNum == 3)
		{
			mColor = BULLET_COLOR::TYPE_YELLOW;
		}
		else if (mBulletColorNum == 4)
		{
			mColor = BULLET_COLOR::TYPE_GREEN;
		}
		else if (mBulletColorNum == 5)
		{
			mColor = BULLET_COLOR::TYPE_BLUE;
		}
	}
}

void BulletManager::DeleteBullet()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end();)
	{
		if ((*itr) == nullptr)
		{
			itr++;
			continue;
		}
			
		if ((*itr)->GetPos().mY < -100 || (*itr)->GetPos().mY > SCREEN_BOTTOM + 100 || (*itr)->GetPos().mX<-100 || (*itr)->GetPos().mX>SCREEN_RIGHT + 100)
		{
			if ((*itr)->Type() == BULLET_TYPE::TYPE_PLAYER && mpPlayer != nullptr)
				mpPlayer->Reset();
			(*itr)->Finalize();
			delete (*itr);
			itr = mpBullet.erase(itr);
			continue;
		}
		if ((*itr)->Active() == false && (*itr)->Type() == BULLET_TYPE::TYPE_FIREWORKS)
		{
			(*itr)->Finalize();
			delete (*itr); 
			itr = mpBullet.erase(itr);
			continue;
		}
		itr++;
	}
}

void BulletManager::PlayerBulletDelete()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end();)
	{
		if ((*itr) == nullptr)
		{
			itr++;
			continue;
		}
		if ((*itr)->Type() == BULLET_TYPE::TYPE_PLAYER)
		{
			(*itr)->EffectPlay(mpEffect);
			(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
			itr = mpBullet.erase(itr);
			continue;
		}
		itr++;
	}
}

void BulletManager::DeleteFireworks()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end(); itr++)
	{
		mpFireworksManager->Delete(itr);
	}
}

void BulletManager::Explosion(Float2 pos, FIREWORKS_TYPE Colortype)
{
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	mpBullet.push_back(new Bullet_1(1.0f, 0.3f));
	mpBullet.push_back(new Bullet_1(5.0f, 0.6f));
	mpBullet.push_back(new Bullet_1(10.0f, 0.9f));
	std::list<Bullet*>::iterator itr = mpBullet.end();
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
}

void BulletManager::FeverExplosion(Float2 pos, FIREWORKS_TYPE Colortype)
{
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	mpBullet.push_back(new Bullet_1(1.5f, 0.45f));
	mpBullet.push_back(new Bullet_1(7.5f, 0.9f));
	mpBullet.push_back(new Bullet_1(15.0f, 1.35f));
	std::list<Bullet*>::iterator itr = mpBullet.end();
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY - 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY - 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX - 1, pos.mY + 0.5f, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
	(--itr);(*itr)->Initialize(pos, pos.mX + 0.5f, pos.mY + 1, BULLET_TYPE::TYPE_FIREWORKS, Colortype, BULLET_COLOR::TYPE_NORMAL,mpFireworksManager);
}

void BulletManager::FeverEffectBullet(float x,float y)
{
	Float2 SetPos;
	SetPos.mX = x;
	SetPos.mY = y;
	mpBullet.push_back(new Bullet_2(10.0f, 4.0f));
	std::list<Bullet*>::iterator itr = mpBullet.end();
	(--itr); (*itr)->Initialize(SetPos, 0.0f, 0.0f, BULLET_TYPE::TYPE_FIREWORKS, FIREWORKS_TYPE::TYPE_NORMAL, BULLET_COLOR::TYPE_NORMAL, mpFireworksManager);
}