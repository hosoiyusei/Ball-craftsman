#include"Effect.h"
#include "EffekseerForDXLib.h"
#include"../Framework/ResourceManager.h"
#pragma warning(disable:4099)

Effect::Effect()
	:mEffectResourceHandle(0)
	, mEffectResourceHandle2(0)
	, mEffectResourceHandle3(0)
	, mEffectResourceHandle4(0)
	, mEffectResourceHandle5(0)
	, mEffectResourceHandle6(0)
	, mEffectResourceHandle7(0)
	, mEffectResourceHandle8(0)
	,mEffectResourceHandle9(0)
	, mEffect1(0)
	, mEffect2(0)
	, mEffect3(0)
	, mEffect4(0)
	, mEffect5(0)
	, mEffect6(0)
	, mEffect7(0)
	,mEffect8(0)
	, mTimer(0)
	, mPos()
	, mStartTimer(0)
{

}

Effect::~Effect()
{

}

void Effect::Initialize()
{
	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	ResourceManager* pRm = ResourceManager::GetInstance();

	mEffectResourceHandle = pRm->GetResource("laser.efk", TYPE::Effect, 20);
	mEffectResourceHandle2 = pRm->GetResource("Breakdown.efk", TYPE::Effect, 20);
	mEffectResourceHandle3 = pRm->GetResource("Gohlem1.efk", TYPE::Effect, 20);
	mEffectResourceHandle4 = pRm->GetResource("Test.efk", TYPE::Effect, 20);
	mEffectResourceHandle5= pRm->GetResource("Gohlem2.efk", TYPE::Effect, 40);
	mEffectResourceHandle6 = pRm->GetResource("Gohlem3.efk", TYPE::Effect, 60);
	mEffectResourceHandle7 = pRm->GetResource("Blow5.efk", TYPE::Effect, 20);
	mEffectResourceHandle8 = pRm->GetResource("Blow9.efk", TYPE::Effect, 10);
	mEffectResourceHandle9 = pRm->GetResource("hanabi_1.efk", TYPE::Effect, 70);

	//mEffect1 = PlayEffekseer2DEffect(mEffectResourceHandle);
}

void Effect::Update()
{
	if (mStartTimer < 2)
		mStartTimer++;
	if (mStartTimer == 1)
		Play(-200, -200, EFFECT_NUM::EFFECT_START);

	SetPosPlayingEffekseer2DEffect(mEffect1, mPos[0].mX, mPos[0].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect2, mPos[1].mX, mPos[1].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect3, mPos[2].mX, mPos[2].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect4, mPos[3].mX, mPos[3].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect5, mPos[4].mX, mPos[4].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect6, mPos[5].mX, mPos[5].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect7, mPos[6].mX, mPos[6].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect8, mPos[7].mX, mPos[7].mY, 0);

	UpdateEffekseer2D();
}

void Effect::Draw()
{
	DrawEffekseer2D();
}

void Effect::Finalize()
{
	DeleteEffekseerEffect(mEffectResourceHandle);
	DeleteEffekseerEffect(mEffectResourceHandle2);
	DeleteEffekseerEffect(mEffectResourceHandle3);
	DeleteEffekseerEffect(mEffectResourceHandle4);
	DeleteEffekseerEffect(mEffectResourceHandle5);
	DeleteEffekseerEffect(mEffectResourceHandle6);
	DeleteEffekseerEffect(mEffectResourceHandle7); 
	DeleteEffekseerEffect(mEffectResourceHandle8);
	DeleteEffekseerEffect(mEffectResourceHandle9);
}

void Effect::Play(float x,float y, EFFECT_NUM num)
{
	if (num == EFFECT_NUM::EFFECT_1)
	{
		mEffect1 = PlayEffekseer2DEffect(mEffectResourceHandle);
		mPos[0].mX = x;
		mPos[0].mY = y;
	}
	else if (num == EFFECT_NUM::EFFECT_2)
	{
		mEffect2 = PlayEffekseer2DEffect(mEffectResourceHandle2);
		mPos[1].mX = x;
		mPos[1].mY = y;
	}
	else if (num == EFFECT_NUM::EFFECT_3)
	{
		mEffect3 = PlayEffekseer2DEffect(mEffectResourceHandle3);
		mPos[2].mX = x;
		mPos[2].mY = y;
	}
	else if (num == EFFECT_NUM::EFFECT_START)
	{
		mEffect3 = PlayEffekseer2DEffect(mEffectResourceHandle4);
		mPos[2].mX = x;
		mPos[2].mY = y;
	}
	else if (num == EFFECT_NUM::EFFECT_4)
	{
		mEffect4 = PlayEffekseer2DEffect(mEffectResourceHandle5);
		mPos[3].mX = x;
		mPos[3].mY = y;
	}
	else if (num == EFFECT_NUM::EFFECT_5)
	{
		mEffect5 = PlayEffekseer2DEffect(mEffectResourceHandle6);
		mPos[4].mX = x;
		mPos[4].mY = y;
	}
	else if (num == EFFECT_NUM::EFFECT_6)
	{
		mEffect6 = PlayEffekseer2DEffect(mEffectResourceHandle7);
		mPos[5].mX = x;
		mPos[5].mY = y;
	}
	else if (num == EFFECT_NUM::EFFECT_7)
	{
		mEffect7 = PlayEffekseer2DEffect(mEffectResourceHandle8);
		mPos[6].mX = x;
		mPos[6].mY = y;
	}
	else if (num == EFFECT_NUM::EFFECT_8)
	{
		mEffect8 = PlayEffekseer2DEffect(mEffectResourceHandle9);
		mPos[7].mX = x;
		mPos[7].mY = y;
	}
}

void Effect::StopEffect()
{
	StopEffekseer2DEffect(mEffectResourceHandle9);
}