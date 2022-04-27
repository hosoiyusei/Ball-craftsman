#pragma once
#include"Fireworks.h"

class Fireworks_0 :public Fireworks
{
private:

	Float2 mPos;

	CircleCollider mCollision;

	FIREWORKS_TYPE mColorType;

	float mSize;

	float mSize2;

	float mSizeUp;

	bool mActive;

public:

	Fireworks_0();
	~Fireworks_0();

	void Initialize(float x, float y, FIREWORKS_TYPE type) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	bool Active() override
	{
		return mActive;
	}

	void EffectPlay(Effect* pEffect) override;

	void EffectPlay2(Effect* pEffect) override;

	Float2 GetPos() override
	{
		return mPos;
	}

	CircleCollider Collision() override
	{
		return mCollision;
	}

	FIREWORKS_TYPE Type() override
	{
		return mColorType;
	}
};