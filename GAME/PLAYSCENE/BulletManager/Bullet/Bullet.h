#pragma once
#include"../../../Utility.h"
#include"../BulletType.h"
#include"../../Collision/Collision.h"
#include"../../FireworksManager/FireworksType.h"

class Effect;
class FireworksManager;

class Bullet
{
public:

	virtual ~Bullet() = default;

	virtual void Initialize(Float2 pos, float vx, float vy, BULLET_TYPE type, FIREWORKS_TYPE Colortype, BULLET_COLOR bulletcolor, FireworksManager* pFireworksManager) = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	virtual void EffectPlay(Effect* pEffect) = 0;

	virtual bool Active() = 0;

	virtual Float2 GetPos() = 0;

	virtual BULLET_TYPE Type() = 0;

	virtual BULLET_COLOR BulletColor() = 0;

	virtual CircleCollider Collision() = 0;
};