//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   WinMain.cpp
//!
//! @brief  ゲームプログラムのエントリーポイント
//!
//! @date   2019/3/26
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "Game\GameMain.h"
#include "Resources\Icon\Icon.h"
#include "EffekseerForDXLib.h"

// 関数定義 ================================================================

//----------------------------------------------------------------------
//! @brief プログラムのエントリーポイント
//!
//! @param[in] hInstance     現在のインスタンスのハンドル
//! @param[in] hPrevInstance 以前のインスタンスのハンドル(常にNULL)
//! @param[in] lpCmdLine     コマンドライン
//! @param[in] nCmdShow      ウィンドウの表示状態
//!
//! @retval  0 正常終了
//! @retval -1 異常終了
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 未使用引数の警告対策
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);


#if defined(_DEBUG)
	// メモリーリーク検出機構のセットアップ
	SetUpMemoryLeakDetector();
#endif


	// デバッグ情報用ログファイルの出力の抑制
	SetOutApplicationLogValidFlag(FALSE);


	// 起動モードの設定
#if defined(_DEBUG)
	ChangeWindowMode(TRUE);	          // ウインドウモードで実行
	SetMainWindowText(GAME_TITLE);    // ウインドウタイトルの設定
	SetWindowIconID(IDI_ICON1);       // ウインドウアイコンの設定
#else
	ChangeWindowMode(TRUE);	      // フルスクリーンで実行
#endif


	// 初期状態の画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	// DXライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;    // エラーが起きたら直ちに終了
	}

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);


	// 描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームクラスの作成
	GameMain* pGameMain = new GameMain();
	
	// ゲームの処理
	pGameMain->InitializeGame();    // ゲームの初期化処理
	
	while (!ProcessMessage() && !CheckHitKey(EXIT_KEY))
	{ 
		UpdateSystem();        // システムの更新
		
		pGameMain->UpdateGame();          // ゲームの更新処理
		pGameMain->RenderGame();          // ゲームの描画処理

		ScreenFlip();          // 裏画面の内容を表画面に反映
		ClearDrawScreen();     // 裏画面の消去
	}

	pGameMain->FinalizeGame();      // ゲームの終了処理

	// ゲームクラスの削除
	delete pGameMain;

	pGameMain = nullptr;

	Effkseer_End();

	// DXライブラリの終了処理
	if (DxLib_End() == -1)
	{
		return -1;    // エラーが起きたら直ちに終了
	}


	return 0;    // 正常終了
}
