#pragma once
#include"Fireworks.h"

class Fireworks_1 :public Fireworks
{
private:

	Float2 mPosfloat;

	Int2 mPos;

	CircleCollider mCollision;

	FIREWORKS_TYPE mColorType;

	float mSizef;

	float mSize2f;

	int mSize;

	int mSize2;

	float mSizeUp;

	bool mActive;

public:

	Fireworks_1();
	~Fireworks_1();

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
		return mPosfloat;
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