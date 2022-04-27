#include"Bullet_1.h"
#include<math.h>

Bullet_1::Bullet_1(float size,float speed)
	:mPos()
	, mCollision()
	, mSpeed(speed)
	, mAngle(0.0f)
	, mTimer(0)
	, mX(0.0f)
	, mY(0.0f)
	, mX2(0.0f)
	, mY2(0.0f)
	,mSize(size)
	, mBrightness(255)
	, mActive(true)
{

}

Bullet_1::~Bullet_1()
{

}

void Bullet_1::Initialize(Float2 pos, float vx, float vy, BULLET_TYPE type, FIREWORKS_TYPE Colortype, BULLET_COLOR bulletcolor, FireworksManager* pFireworksManager)
{
	mType = type;
	mColorType = Colortype;
	mPos.mX = pos.mX;
	mPos.mY = pos.mY;
	mX = vx;
	mY = vy;
}

void Bullet_1::Update()
{
	if (mTimer == 0)
	{
		Shot();
		++mTimer;
	}

	if (mBrightness > 0)
		mBrightness -= 2;
	if (mBrightness <= 0)
		mActive = false;

	mSize += 0.1f;

	mPos.mX += mX2;
	mPos.mY += mY2;
}

void Bullet_1::Draw()
{
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, mBrightness);
	if (mColorType == FIREWORKS_TYPE::TYPE_RED)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(255, 0, 0), FALSE);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_ORANGE)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(255, 100, 0), FALSE);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_YELLOW)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(255, 255, 0), FALSE);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_GREEN)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(0, 255, 0), FALSE);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_BLUE)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(0, 100, 255), FALSE);
	}
	
	SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
}

void Bullet_1::Finalize()
{

}

void Bullet_1::Shot()
{
	mAngle = atan2f(mY - mPos.mY, mX - mPos.mX);

	mX2 = mSpeed * static_cast<float>(cos(mAngle));
	mY2 = mSpeed * static_cast<float>(sin(mAngle));
}