#include"Fireworks_1.h"
#include"../../../Effect/Effect.h"

Fireworks_1::Fireworks_1()
	:mPos()
	, mCollision()
	, mSizef(1.0f)
	, mSize2f(0.0f)
	, mActive(true)
	, mSizeUp(0.0f)
	, mPosfloat()
	,mSize(0)
	,mSize2(0)
{

}

Fireworks_1::~Fireworks_1()
{

}

void Fireworks_1::Initialize(float x, float y, FIREWORKS_TYPE type)
{
	mPos.mX = static_cast<int>(x);
	mPos.mY = static_cast<int>(y);
	mPosfloat.mX = x;
	mPosfloat.mY = y;

	mColorType = type;

	mCollision.mRadius = 0.0f;
	mCollision.mPos.mX = mPosfloat.mX;
	mCollision.mPos.mY = mPosfloat.mY;
}

void Fireworks_1::Update()
{
	if (mSizef < 120)
	{
		mSizeUp += 1.0f;
		mSizef += mSizeUp;
	}

	mSize2f = mSizef;

	mSize = static_cast<int>(mSizef);
	mSize2 = static_cast<int>(mSize2f);

	mCollision.mRadius = mSizef;
}

void Fireworks_1::Draw()
{
	if (mColorType == FIREWORKS_TYPE::TYPE_RED)
	{
		DrawCircle(mPos.mX, mPos.mY, mSize, GetColor(255, 0, 0), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(mPos.mX, mPos.mY, mSize2, GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_YELLOW)
	{
		DrawCircle(mPos.mX, mPos.mY, mSize, GetColor(255, 255, 0), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(mPos.mX, mPos.mY, mSize2, GetColor(255, 255, 0), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_ORANGE)
	{
		DrawCircle(mPos.mX, mPos.mY, mSize, GetColor(255, 100, 0), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(mPos.mX, mPos.mY, mSize2, GetColor(255, 100, 0), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_GREEN)
	{
		DrawCircle(mPos.mX, mPos.mY, mSize, GetColor(0, 255, 0), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(mPos.mX, mPos.mY, mSize2, GetColor(0, 255, 0), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
	else if (mColorType == FIREWORKS_TYPE::TYPE_BLUE)
	{
		DrawCircle(mPos.mX, mPos.mY, mSize, GetColor(0, 100, 255), FALSE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 50);
		DrawCircle(mPos.mX, mPos.mY, mSize2, GetColor(0, 100, 255), TRUE);
		SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 0);
	}
}

void Fireworks_1::Finalize()
{
	
}

void Fireworks_1::EffectPlay(Effect* pEffect)
{
	if (pEffect != nullptr)
		pEffect->Play(mPosfloat.mX, mPosfloat.mY, EFFECT_NUM::EFFECT_5);
}

void Fireworks_1::EffectPlay2(Effect* pEffect)
{
	if (pEffect != nullptr)
		pEffect->Play(mPosfloat.mX, mPosfloat.mY, EFFECT_NUM::EFFECT_4);
}