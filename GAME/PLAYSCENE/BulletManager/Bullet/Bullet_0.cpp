#include"Bullet_0.h"
#include"../../../Effect/Effect.h"
#include"../../../Framework/ResourceManager.h"
#include"../../FireworksManager/FireworksManager.h"

Bullet_0::Bullet_0()
	:mPos()
	, mCollision()
	, mGravity(0.1f)
	,mVX(0.0f)
	,mVY(0.0f)
	,mVelY(0.0f)
	,mTimer(0)
	, mBomTexture(0)
	, mpFireworksManager(nullptr)
{

}

Bullet_0::~Bullet_0()
{

}

void Bullet_0::Initialize(Float2 pos, float vx, float vy, BULLET_TYPE type, FIREWORKS_TYPE Colortype, BULLET_COLOR bulletcolor, FireworksManager* pFireworksManager)
{
	mpFireworksManager = pFireworksManager;
	mPos.mX = pos.mX;
	mPos.mY = pos.mY;
	mVX = vx;
	mVY = vy;
	mType = type;
	mBulletColor = bulletcolor;

	mCollision.mRadius = 1.0f;
	mCollision.mPos.mX = mPos.mX;
	mCollision.mPos.mY = mPos.mY;

	ResourceManager* pRm = ResourceManager::GetInstance();
	mBomTexture = pRm->GetResource("bomb.png", TYPE::Textures);
}

void Bullet_0::Update()
{
	if (mTimer < 2)
		mTimer++;
	if (mTimer == 1)
		mVelY = mVY;

	mVelY += mGravity;

	mPos.mX += mVX;
	mPos.mY += mVelY;

	mCollision.mPos.mX = mPos.mX;
	mCollision.mPos.mY = mPos.mY;
}

void Bullet_0::Draw()
{
	DrawRectRotaGraph(
		static_cast<int>(mPos.mX),//X�̈ʒu
		static_cast<int>(mPos.mY),//Y�̈ʒu
		0,//�؂���J�n�̈ʒu
		0,//�؂���J�n�̈ʒu
		2500,//�؂���I���̈ʒu
		1500,//�؂���I���̈ʒu
		0.05,//�g��
		0.0,//��]
		mBomTexture,//�A�h���X
		TRUE
	);
}

void Bullet_0::Finalize()
{
	
}

void Bullet_0::EffectPlay(Effect* pEffect)
{
	if (mpFireworksManager != nullptr)
	{
		if (mpFireworksManager->FeverFlag() == false)
		{
			pEffect->Play(mPos.mX, mPos.mY, EFFECT_NUM::EFFECT_2);
		}
		else
		{
			pEffect->Play(mPos.mX, mPos.mY, EFFECT_NUM::EFFECT_7);
		}
	}
}