#pragma once
#include <list>
#include"../../Utility.h"
#include"../FireworksManager/FireworksType.h"
#include"BulletType.h"

class Bullet;
class Player;
class Effect;
class FireworksManager;

class BulletManager
{
private:

	std::list<Bullet*> mpBullet;

	Player* mpPlayer;

	Effect* mpEffect;

	FireworksManager* mpFireworksManager;

	int mBulletColorNum;

	int mCannonSE;

	BULLET_COLOR mColor;

public:

	BulletManager();
	~BulletManager();

	void Initialize(Player* pPlayer, Effect* pEffect, FireworksManager* pFireworksManager);

	void Update();

	void Draw();

	void Finalize();

	void Shot(Float2 pos,float vx,float vy);

	void Explosion(Float2 pos, FIREWORKS_TYPE Colortype);

	void FeverExplosion(Float2 pos, FIREWORKS_TYPE Colortype);

	void DeleteBullet();

	BULLET_COLOR Color()
	{
		return mColor;
	}

	void FeverEffectBullet(float x,float y);

private:

	void BulletColorChange();

	void PlayerBulletDelete();

	void DeleteFireworks();
};