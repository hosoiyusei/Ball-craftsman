#include"ResourceManager.h"
#include "EffekseerForDXLib.h"

/*=============================================================================
テクスチャの追加
=============================================================================*/
int ResourceManager::GetResource(std::string fileName, TYPE type, float size)
{
	switch (type)
	{
		//テクスチャ===========================================================
		case TYPE::Textures:
		{
			std::string fullPath = "Resources/Textures/" + fileName;  //ハンドル

			if (mTexturesHandles.find("Resources/Textures/" + fileName) != mTexturesHandles.end())   //すでにあったらそれを返す
			{
				return mTexturesHandles["Resources/Textures/" + fileName];
			}

			mTexturesHandles["Resources/Textures/" + fileName] = LoadGraph(fullPath.c_str());//ハンドルを登録する

			return mTexturesHandles["Resources/Textures/" + fileName];//ハンドルを返す

			break;
		}
		//サウンド============================================================
		case TYPE::Audio:
		{
			std::string fullPath = "Resources/Audio/" + fileName;//ハンドル

			if (mAudioHandles.find("Resources/Audio/" + fileName) != mAudioHandles.end())//すでにあったらそれを返す
			{
				return mAudioHandles["Resources/Audio/" + fileName];
			}

			mAudioHandles["Resources/Audio/" + fileName] = LoadSoundMem(fullPath.c_str());//ハンドルを登録する

			return mAudioHandles["Resources/Audio/" + fileName];//ハンドルを返す

			break;
		}
		case TYPE::Audio_2:
		{
			std::string fullPath = "Resources/Audio/" + fileName;//ハンドル

			if (mAudioHandles.find("Resources/Audio/" + fileName) != mAudioHandles.end())//すでにあったらそれを返す
			{
				return mAudioHandles["Resources/Audio/" + fileName];
			}

			mAudioHandles["Resources/Audio/" + fileName] = LoadSoftSound(fullPath.c_str());//ハンドルを登録する

			return mAudioHandles["Resources/Audio/" + fileName];//ハンドルを返す

			break;
		}
		//エフェクト============================================================
		case TYPE::Effect:
		{
			std::string fullPath = "Resources/Effect/" + fileName;//ハンドル

			if (mEffectHandles.find("Resources/Effect/" + fileName) != mEffectHandles.end())//すでにあったらそれを返す
			{
				return mEffectHandles["Resources/Effect/" + fileName];
			}

			mEffectHandles["Resources/Effect/" + fileName] = LoadEffekseerEffect(fullPath.c_str(), size);//ハンドルを登録する

			return mEffectHandles["Resources/Effect/" + fileName];//ハンドルを返す

			break;
		}
		default:
			break;
	}
	return 0;
}

/*===========================================================================
テクスチャの削除
===========================================================================*/
void ResourceManager::DeleteResource()
{
	InitSoundMem();
	InitGraph();

	mTexturesHandles.clear();//全て抹消
	mAudioHandles.clear();
	mEffectHandles.clear();
}