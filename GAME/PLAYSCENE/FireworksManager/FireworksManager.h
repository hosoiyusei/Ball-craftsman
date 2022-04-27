#pragma once
#include <list>

class Fireworks;
class Effect;
class BulletManager;
class Bullet;
class SaveData;

class FireworksManager
{
private:

	std::list<Fireworks*> mpFireworks;
	//std::list<Fireworks*>::iterator itr;

	Effect* mpEffect;

	BulletManager* mpBulletManager;

	SaveData* mpSaveData;

	int mCreateTimer;

	int mCreateInterval;

	int mNum;

	float mFeverGage;

	bool mFeverFlag;

	int mExplosionSE;

	int mScore;

	int mFeverEffectTimer;

	int mRed, mGreen, mBlue;

	int mColorswitch;

public:

	FireworksManager();
	~FireworksManager();

	void Initialize(Effect* pEffect, BulletManager* pBulletManager,SaveData* pSaveData);

	void Update();

	void Draw();

	void Finalize();

	void Delete(std::list<Bullet*>::iterator pBulletitr);

	bool FeverFlag()
	{
		return mFeverFlag;
	}

private:

	void Create();

	void CreateFever();

	void DeleteTime();

	void Fever();

	void Rainbow();
};