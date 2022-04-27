/*
	フェード管理
*/
#include "../../Game/GameMain.h"

// フェードの割合
float g_fadeRate = 0.0f;

// フェードの終了フラグ
BOOL g_fadeEnd = FALSE;

/*---------------------------------------------------
フェードイン（画面が見えてくる）の更新
戻り値	：	フェード中かどうか
---------------------------------------------------*/
BOOL FadeInUpdate(float time)
{
	float deltaTime = GetFrameDeltaTime();

	g_fadeRate -= deltaTime / time;

	if (g_fadeRate < 0.0f || g_fadeEnd == TRUE)
	{
		g_fadeRate = 0.0f;

		g_fadeEnd = FALSE;

		return FALSE;
	}

	return TRUE;
}

/*---------------------------------------------------
フェードアウト（画面見えなくなる）の更新
戻り値	：	フェード中かどうか
---------------------------------------------------*/
BOOL FadeOutUpdate(float time)
{
	float deltaTime = GetFrameDeltaTime();

	g_fadeRate += deltaTime / time;

	if (g_fadeRate > 1.0f || g_fadeEnd == TRUE)
	{
		g_fadeRate = 1.0f;

		g_fadeEnd = FALSE;

		return FALSE;
	}

	return TRUE;
}

/*---------------------------------------------------
フェードマスクの描画
引数	：	unsigned int color(マスクの色)
---------------------------------------------------*/
void FadeDraw(unsigned int color)
{
	DrawAlphaBox(
		SCREEN_LEFT,
		SCREEN_TOP,
		SCREEN_RIGHT,
		SCREEN_BOTTOM,
		color,
		g_fadeRate
	);
}

/*---------------------------------------------------
フェードの終了
---------------------------------------------------*/
void FadeEnd()
{
	g_fadeEnd = TRUE;
}

/*---------------------------------------------------
フェードアウトしきった状態にする
---------------------------------------------------*/
void SetFadeOut()
{
	g_fadeRate = 1.0f;
}

/*---------------------------------------------------
フェードインしきった状態にする
---------------------------------------------------*/
void SetFadeIn()
{
	g_fadeRate = 0.0f;
}