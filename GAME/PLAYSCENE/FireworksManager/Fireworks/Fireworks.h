#pragma once
#include"../../../Utility.h"
#include"../../Collision/Collision.h"
#include"../FireworksType.h"

class Effect;

class Fireworks
{
public:

	virtual ~Fireworks() = default;

	virtual void Initialize(float x,float y, FIREWORKS_TYPE type) = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	virtual bool Active() = 0;

	virtual void EffectPlay(Effect* pEffect) = 0;

	virtual void EffectPlay2(Effect* pEffect) = 0;

	virtual Float2 GetPos() = 0;

	virtual CircleCollider Collision() = 0;

	virtual FIREWORKS_TYPE Type() = 0;
};