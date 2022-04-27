#pragma once
#include"../../Utility.h"
#include"../BulletManager/BulletType.h"

class BulletManager;

class Player
{
private:

	Float2 mPos;
	Float2 mFirstPos, mSecondPos;

	BULLET_COLOR mColor;

	int mMouseX, mMouseY;

	bool mFirstSetFlag,mShotFlag;

	int mClickTimer, mClickTimer2;

	float mAngle;

	float mX, mY, mX2, mY2, mVX, mVY;

	int mBulletSetSE;

	int mRed, mGreen, mBlue;

	BulletManager* mpBulletManager;

public:

	Player();
	~Player();

	void Initialize(BulletManager* pBulletManager);

	void Update();

	void Draw();

	void Finalize();

	Float2 GetPos()
	{
		return mPos;
	}

	void Reset();

private:

	void Shot();

	void Search();
};