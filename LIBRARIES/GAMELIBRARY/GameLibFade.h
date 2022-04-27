/*
	フェード管理
*/
#pragma once

// フェードイン（画面が見えてくる）の更新
BOOL FadeInUpdate(float time);

// フェードアウト（画面見えなくなる）の更新
BOOL FadeOutUpdate(float time);

// フェードマスクの描画
void FadeDraw(unsigned int color);

// フェードの終了
void FadeEnd();

// フェードアウトしきった状態にする
void SetFadeOut();

// フェードインしきった状態にする
void SetFadeIn();