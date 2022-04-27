#include"Player.h"
#include"../BulletManager/BulletManager.h"
#include<math.h>
#include"../../Framework/ResourceManager.h"

Player::Player()
	:mPos()
	,mFirstPos()
	,mSecondPos()
	,mFirstSetFlag(false)
	, mShotFlag(false)
	,mX(0.0f)
	,mY(0.0f)
	,mX2(0.0f)
	,mY2(0.0f)
	,mVX(0.0f)
	,mVY(0.0f)
	,mpBulletManager(nullptr)
	,mClickTimer(0)
	,mClickTimer2(0)
	, mBulletSetSE(0)
	, mColor(BULLET_COLOR::TYPE_RED)
	,mRed(0)
	,mGreen(0)
	,mBlue(0)
{

}

Player::~Player()
{

}

void Player::Initialize(BulletManager* pBulletManager)
{
	mpBulletManager = pBulletManager;

	mPos.mX = 100.0f;
	mPos.mY = 380.0f;

	ResourceManager* pRm = ResourceManager::GetInstance();
	mBulletSetSE = pRm->GetResource("BulletSet.mp3", TYPE::Audio);
}

void Player::Update()
{
	Shot();
	Search();

	mColor = mpBulletManager->Color();
}

void Player::Draw()
{
	if (mColor == BULLET_COLOR::TYPE_RED)
	{
		mRed = 255; mGreen = 0; mBlue = 0;
	}
	else if (mColor == BULLET_COLOR::TYPE_ORANGE)
	{
		mRed = 255; mGreen = 100; mBlue = 0;
	}
	else if (mColor == BULLET_COLOR::TYPE_YELLOW)
	{
		mRed = 255; mGreen = 255; mBlue = 0;
	}
	else if (mColor == BULLET_COLOR::TYPE_GREEN)
	{
		mRed = 0; mGreen = 255; mBlue = 0;
	}
	else if (mColor == BULLET_COLOR::TYPE_BLUE)
	{
		mRed = 0; mGreen = 100; mBlue = 255;
	}
	else if (mColor == BULLET_COLOR::TYPE_FEVER)
	{
		mRed = 255; mGreen = 255; mBlue = 255;
	}

	DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), 10, GetColor(mRed, mGreen, mBlue),TRUE);

	DrawCircle(mMouseX, mMouseY, 5, GetColor(255, 0, 0), TRUE);
	if (mFirstSetFlag == true)
	{
		DrawTriangle(
			static_cast<int>(mFirstPos.mX),static_cast<int>(mFirstPos.mY),
			static_cast<int>(mFirstPos.mX + mX), static_cast<int>(mFirstPos.mY +  mY),
			static_cast<int>(mFirstPos.mX + mX2),static_cast<int>(mFirstPos.mY + mY2),
			GetColor(255, 255, 255), TRUE
		);
		DrawLine(static_cast<int>(mFirstPos.mX), static_cast<int>(mFirstPos.mY), static_cast<int>(mSecondPos.mX), static_cast<int>(mSecondPos.mY), GetColor(255, 255, 255), TRUE);
		DrawCircle(static_cast<int>(mFirstPos.mX), static_cast<int>(mFirstPos.mY), 5, GetColor(0, 255, 0), TRUE);
		DrawCircle(static_cast<int>(mSecondPos.mX), static_cast<int>(mSecondPos.mY), 5, GetColor(0, 0, 255), TRUE);
	}
}

void Player::Finalize()
{

}

//Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°

void Player::Shot()
{
	GetMousePoint(&mMouseX, &mMouseY);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && mShotFlag == false)
	{
		if (mClickTimer < 2)
			mClickTimer++;
		if (mClickTimer == 1)
		{
			mFirstPos.mX = static_cast<float>(mMouseX);
			mFirstPos.mY = static_cast<float>(mMouseY);
			mFirstSetFlag = true;
			PlaySoundMem(mBulletSetSE, DX_PLAYTYPE_BACK, TRUE);
			ChangeVolumeSoundMem(255, mBulletSetSE);
		}
	}
	if (mFirstSetFlag == true)
	{
		mSecondPos.mX = static_cast<float>(mMouseX);
		mSecondPos.mY = static_cast<float>(mMouseY);
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0 && mFirstSetFlag == true)
	{
		if (mClickTimer2 < 2)
			mClickTimer2++;
		if (mClickTimer2 == 1)
		{
			mSecondPos.mX = static_cast<float>(mMouseX);
			mSecondPos.mY = static_cast<float>(mMouseY);
			mVX = mFirstPos.mX - mSecondPos.mX;
			mVY = mFirstPos.mY - mSecondPos.mY;
			mFirstSetFlag = false;
			mShotFlag = true;
			mClickTimer = 0;
			mClickTimer2 = 0;

			//íeÇÃî≠éÀ
			mpBulletManager->Shot(mPos, mVX/30.0f, mVY/30.0f);
		}
	}
}

void Player::Search()
{
	mAngle = atan2f(mFirstPos.mY - mMouseY, mFirstPos.mX - mMouseX);

	mX = -30 * static_cast<float>(cos(mAngle - 0.5f));
	mY = -30 * static_cast<float>(sin(mAngle - 0.5f));
	mX2 = -30 * static_cast<float>(cos(mAngle + 0.5f));
	mY2 = -30 * static_cast<float>(sin(mAngle + 0.5f));
}

void Player::Reset()
{
	mVX = 0.0f;
	mVY = 0.0f;
	mShotFlag = false;
}