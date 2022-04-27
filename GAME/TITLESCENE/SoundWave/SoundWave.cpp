#include"SoundWave.h"
#include <corecrt_math.h>
#include"../../Framework/ResourceManager.h"

SoundWave::SoundWave()
	: mSoundHandle(0)
	, mSoftSoundHandle(0)
	,mRed(255)
	,mGreen(0)
	,mBlue(0)
	, mColorswitch(0)
{

}

SoundWave::~SoundWave()
{

}

void SoundWave::Initialize()
{
	ResourceManager* pRm = ResourceManager::GetInstance();
	mSoftSoundHandle = pRm->GetResource("TestBGM.mp3", TYPE::Audio_2);

	// ソフトサウンドハンドルからサウンドハンドルを作成( もう一度ファイルから読み込んでも同じです )
	mSoundHandle = LoadSoundMemFromSoftSound(mSoftSoundHandle);
	ChangeVolumeSoundMem(100, mSoundHandle);
	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(100, mSoundHandle);
}

void SoundWave::Update()
{
	// 現在の再生位置を取得
	mSamplePos = static_cast<int>(GetCurrentPositionSoundMem(mSoundHandle));

	// 現在の再生位置から 4096 サンプルを使用して周波数分布を得る
	GetFFTVibrationSoftSound(mSoftSoundHandle, -1, mSamplePos, 4096, mParamList, 800);

	ChangeVolumeSoundMem(100, mSoundHandle);

	switch (mColorswitch)
	{
		case 0:
		{
			mGreen += 5;
			if (mGreen > 250)
				mColorswitch = 1;
			break;
		}
		case 1:
		{
			mRed -= 5;
			
			if (mRed < 5)
				mColorswitch = 5;
			break;
		}
		case 2:
		{
			mGreen -= 5;
			if (mGreen < 5)
				mColorswitch = 3;
			break;
		}
		case 3:
		{
			mRed += 5;
			if (mRed > 250)
				mColorswitch = 4;
			break;
		}
		case 4:
		{
			mBlue -= 5;
			if (mBlue < 5)
				mColorswitch = 0;
			break;
		}
		case 5:
		{
			mBlue += 5;
			if (mBlue > 250)
				mColorswitch = 2;
			break;
		}
		default:
			break;
	}
}

void SoundWave::DrawWave()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	// 周波数分布を画面に描画する
	for (int i = 0; i < 107; i++)
	{
		float Param;

		// 関数から取得できる値を描画に適した値に調整
		Param = static_cast<float>(pow(static_cast<double>(mParamList[i]), static_cast<double>(0.5f)) * 1.5f);

		if ((int)(Param * 400) > 100)
			DrawBox(0, 0, 640, 480, 
				GetColor(
					static_cast<int>(mRed * 0.05f),
					static_cast<int>(mGreen * 0.05f),
					static_cast<int>(mBlue * 0.05f)), TRUE);

		// 縦線を描画
		DrawBox(
			i * 3,
			240 - (int)(Param * 400),
			i * 3 + 3,
			240 + (int)(Param * 400),
			GetColor(mRed, mGreen, mBlue), FALSE);

		// 縦線を描画
		DrawBox(
			-i * 3 + 640,
			240 - (int)(Param * 400),
			-i * 3 + 3 + 640,
			240 + (int)(Param * 400),
			GetColor(mRed, mGreen, mBlue), FALSE);
		// 縦線を描画
		DrawBox(
			i * 3,
			240 - (int)(Param * 400),
			i * 3 + 3,
			240 + (int)(Param * 400),
			GetColor(mRed, mGreen, mBlue), FALSE);

		// 縦線を描画
		DrawBox(
			-i * 3 + 640,
			240 - (int)(Param * 400),
			-i * 3 + 3 + 640,
			240 + (int)(Param * 400),
			GetColor(mRed, mGreen, mBlue), FALSE);


		if (i > 82)
			continue;
		// 縦線を描画
		DrawBox(
			320 - (int)(Param * 400),
			i * 3,
			320 + (int)(Param * 400),
			i * 3 + 3,
			GetColor(mRed, mGreen, mBlue), FALSE);
		// 縦線を描画
		DrawBox(
			320 - (int)(Param * 400),
			-i * 3 + 480,
			320 + (int)(Param * 400),
			-i * 3 + 3 + 480,
			GetColor(mRed, mGreen, mBlue), FALSE);
		if (i > 82)
			continue;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SoundWave::Finalize()
{
	StopSoundMem(mSoundHandle);
	ResourceManager* pRm = ResourceManager::GetInstance();
	pRm->DeleteResource();
}