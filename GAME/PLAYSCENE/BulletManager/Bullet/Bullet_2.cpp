#include"Bullet_2.h"
#include<math.h>
#include <random>

Bullet_2::Bullet_2(float size, float speed)
	:mPos()
	, mCollision()
	, mSpeed(speed)
	, mAngle(0.0f)
	, mTimer(0)
	, mX(0.0f)
	, mY(0.0f)
	, mX2(0.0f)
	, mY2(0.0f)
	, mSize(size)
	, mBrightness(255)
	, mActive(true)
	,mRed(0)
	,mGreen(0)
	,mBlue(0)
{

}

Bullet_2::~Bullet_2()
{

}

void Bullet_2::Initialize(Float2 pos, float vx, float vy, BULLET_TYPE type, FIREWORKS_TYPE Colortype, BULLET_COLOR bulletcolor, FireworksManager* pFireworksManager)
{
	mType = type;
	mColorType = Colortype;
	mPos.mX = pos.mX;
	mPos.mY = pos.mY;
	
	mY = mPos.mY - 40.0f;

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> distX(static_cast<int>(mPos.mX - 30), static_cast<int>(mPos.mX + 30));

	mX = distX(mt);

	std::uniform_int_distribution<int> distColor(50, 255);

	mRed = distColor(mt);
	mGreen = distColor(mt);
	mBlue = distColor(mt);
}

void Bullet_2::Update()
{
	if (mTimer == 0)
	{
		Shot();
		++mTimer;
	}

	if (mBrightness > 0)
		mBrightness -= 3;
	if (mBrightness <= 0)
		mActive = false;

	mSize += 0.1f;

	mPos.mX += mX2;
	mPos.mY += mY2;
}

void Bullet_2::Draw()
{
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, mBrightness);
	
	DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(mRed, mGreen, mBlue), TRUE);

	SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
}

void Bullet_2::Finalize()
{

}

void Bullet_2::Shot()
{
	mAngle = atan2f(mY - mPos.mY, mX - mPos.mX);

	mX2 = mSpeed * static_cast<float>(cos(mAngle));
	mY2 = mSpeed * static_cast<float>(sin(mAngle));
}