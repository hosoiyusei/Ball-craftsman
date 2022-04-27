#pragma once
#include"Bullet.h"

class Bullet_2 :public Bullet
{
private:

	Float2 mPos;

	//“–‚½‚è”»’è
	CircleCollider mCollision;

	float mSpeed;

	float mAngle;

	float mX, mY, mX2, mY2;

	float mSize;

	int mTimer;

	int mBrightness;

	bool mActive;

	int mRed, mGreen, mBlue;

	BULLET_TYPE mType;

	FIREWORKS_TYPE mColorType;

public:

	Bullet_2(float size, float speed);
	~Bullet_2();

	void Initialize(Float2 pos, float vx, float vy, BULLET_TYPE type, FIREWORKS_TYPE Colortype, BULLET_COLOR bulletcolor, FireworksManager* pFireworksManager) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	bool Active() override
	{
		return mActive;
	}

	Float2 GetPos() override
	{
		return mPos;
	}

	BULLET_TYPE Type() override
	{
		return mType;
	}

	CircleCollider Collision() override
	{
		return mCollision;
	}

private:

	void Shot();

	void EffectPlay(Effect* pEffect) override {}

	BULLET_COLOR BulletColor() override
	{
		return BULLET_COLOR::TYPE_NORMAL;
	}
};