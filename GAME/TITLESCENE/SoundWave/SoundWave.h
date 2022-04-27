#pragma once

class SoundWave
{
private:

	int mSoundHandle;
	int mSoftSoundHandle;
	float mParamList[800];
	int mSamplePos;

	int mRed, mGreen, mBlue;

	int mColorswitch;

public:

	SoundWave();
	~SoundWave();

	void Initialize();

	void Update();

	void DrawWave();

	void Finalize();
};