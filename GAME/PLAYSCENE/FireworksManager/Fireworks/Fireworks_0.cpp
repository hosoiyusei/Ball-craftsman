#include"Fireworks_0.h"
#include"../../../Effect/Effect.h"

Fireworks_0::Fireworks_0()
	:mPos()
	, mCollision()
	, mSize(1.0f)
	, mSize2(0.0f)
	, mActive(true)
	,mSizeUp(0.0f)
{

}

Fireworks_0::~Fireworks_0()
{

}

void Fireworks_0::Initialize(float x, float y, FIREWORKS_TYPE type)
{
	mPos.mX = x;
	mPos.mY = y;

	mColorType = type;

	mCollision.mRadius = 0.0f;
	mCollision.mPos.mX = mPos.mX;
	mCollision.mPos.mY = mPos.mY;
}

void Fireworks_0::Update()
{
	if (mSize < 50)
	{
		mSizeUp += 0.05f;
		mSize += mSizeUp;
	}

	if (mSize2 < mSize)
		mSize2 += 0.05f;

	if (mSize2 >= mSize)
	{
		mActive = false;
	}

	mCollision.mRadius = mSize;
}

void Fireworks_0::Draw()
{
	if (mColorType == FIREWORKS_TYPE::TYPE_RED)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(255, 0, 0), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize2), GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_YELLOW)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(255, 255, 0), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize2), GetColor(255, 255, 0), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_ORANGE)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(255, 100, 0), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize2), GetColor(255, 100, 0), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_GREEN)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(0, 255, 0), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize2), GetColor(0, 255, 0), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_BLUE)
	{
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize), GetColor(0, 100, 255), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(static_cast<int>(mPos.mX), static_cast<int>(mPos.mY), static_cast<int>(mSize2), GetColor(0, 100, 255), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
}

void Fireworks_0::Finalize()
{
	
}

void Fireworks_0::EffectPlay(Effect* pEffect)
{
	if (pEffect != nullptr)
		pEffect->Play(mPos.mX, mPos.mY, EFFECT_NUM::EFFECT_3);
}

void Fireworks_0::EffectPlay2(Effect* pEffect)
{
	if (pEffect != nullptr)
		pEffect->Play(mPos.mX, mPos.mY, EFFECT_NUM::EFFECT_4);
}