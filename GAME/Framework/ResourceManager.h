#pragma once
#include<string>
#include <map>

enum class TYPE :int
{
	Textures,
	Audio,
	Audio_2,
	Effect,
};

class ResourceManager
{
public:

	//インライン関数
	static ResourceManager* GetInstance()
	{
		static ResourceManager Rm;

		return &Rm;
	}

private:

	std::map<std::string, int> mTexturesHandles;

	std::map<std::string, int> mAudioHandles;

	std::map<std::string, int> mEffectHandles;

public:

	//テクスチャの取得
	int GetResource(std::string fileName, TYPE type, float size = 1.0f);

	//テクスチャの削除
	void DeleteResource();
};