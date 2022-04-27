#pragma once
#include"Bullet.h"

class Bullet_0 :public Bullet
{
private:

	Float2 mPos;

	CircleCollider mCollision;

	const float mGravity;

	float mVX, mVY;

	float mVelY;

	int mTimer;

	int mBomTexture;

	BULLET_TYPE mType;

	BULLET_COLOR mBulletColor;

	FireworksManager* mpFireworksManager;

public:

	Bullet_0();
	~Bullet_0();

	void Initialize(Float2 pos, float vx, float vy, BULLET_TYPE type, FIREWORKS_TYPE Colortype, BULLET_COLOR bulletcolor, FireworksManager* pFireworksManager) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void EffectPlay(Effect* pEffect) override;

	bool Active() override
	{
		return true;
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

	BULLET_COLOR BulletColor() override
	{
		return mBulletColor;
	}
};