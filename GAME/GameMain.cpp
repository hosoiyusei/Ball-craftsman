//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"

#include "TitleScene/TitleScene.h"
#include "PlayScene/PlayScene.h"
#include"RESULTSCENE/Resultscene.h"


// 定数の定義 ==============================================================



// 関数の定義 ==============================================================

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
GameMain::GameMain()
	: mNextScene(GAME_SCENE::NONE)
	, mpScene(nullptr)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
GameMain::~GameMain()
{
}

//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameMain::InitializeGame()
{
	// タイトルシーンの作成
	mpScene = new TitleScene();
	mpScene->Initialize();
}



//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameMain::UpdateGame()
{
	// 次のシーンが設定されていたらシーン切り替え
	if (mNextScene != GAME_SCENE::NONE)
	{
		// シーン削除
		DeleteScene();
		
		// シーン作成
		CreateScene();
	}

	// 実態があれば更新
	if (mpScene != nullptr)
	{
		mNextScene = mpScene->Update();
	}
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameMain::RenderGame()
{
	// 実態があれば描画
	if (mpScene != nullptr)
	{
		mpScene->Draw();
	}
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameMain::FinalizeGame()
{
	DeleteScene();
}

/*--------------------------------------------------
シーンの作成
--------------------------------------------------*/
void GameMain::CreateScene()
{
	// シーンが作成されているときは処理しない
	if (mpScene != nullptr)
	{
		return;
	}

	// 次シーンの作成
	switch (mNextScene)
	{
		case GAME_SCENE::TITLE:
		{
			mpScene = new TitleScene();
			break;
		}
		case GAME_SCENE::PLAY:
		{
			mpScene = new PlayScene();
			break;
		}
		case GAME_SCENE::RESULT:
		{
			mpScene = new ResultScene();
			break;
		}
		default:
		{
			// 例外なので処理を中断
			return;
		}
	}

	// 作成したシーンを初期化
	mpScene->Initialize();
}

/*--------------------------------------------------
シーンの削除
--------------------------------------------------*/
void GameMain::DeleteScene()
{
	// シーンが作成されていなければ処理しない
	if (mpScene == nullptr)
	{
		return;
	}

	// 現シーンの終了処理
	mpScene->Finalize();

	// 現シーンの削除
	delete mpScene;
	mpScene = nullptr;
}
