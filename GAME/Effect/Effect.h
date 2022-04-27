#pragma once
#include"../Utility.h"

enum class EFFECT_NUM :int
{
	EFFECT_1,
	EFFECT_2,
	EFFECT_3,
	EFFECT_4,
	EFFECT_5,
	EFFECT_6,
	EFFECT_7,
	EFFECT_8,

	EFFECT_START,
};

class Effect
{
private:

	Float2 mPos[8];

	int mEffectResourceHandle;
	int mEffectResourceHandle2;
	int mEffectResourceHandle3;
	int mEffectResourceHandle4;
	int mEffectResourceHandle5;
	int mEffectResourceHandle6;
	int mEffectResourceHandle7;
	int mEffectResourceHandle8;
	int mEffectResourceHandle9;

	int mEffect1;
	int mEffect2;
	int mEffect3;
	int mEffect4;
	int mEffect5;
	int mEffect6;
	int mEffect7;
	int mEffect8;

	int mTimer;

	int mStartTimer;

public:

	Effect();
	~Effect();

	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	void Play(float x,float y, EFFECT_NUM num);

	void StopEffect();
};