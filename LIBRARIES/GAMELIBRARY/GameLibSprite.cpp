/*
	画像を描画するための構造体
*/

/*---------------------------------------------------
コンストラクタ
---------------------------------------------------*/
SpriteData::SpriteData()
	: pos{ 0.0f, 0.0f }
	, src{ 0, 0 }
	, size{ 0, 0 }
	, center{ 0.5f, 0.5f }
	, scale{ 1.0f, 1.0f }
	, rot(0.0)
	, alpha(1.0f)
	, textureHandle(0)
{
}

/*---------------------------------------------------
デストラクタ
---------------------------------------------------*/
SpriteData::~SpriteData()
{
}

/*---------------------------------------------------
画像の読み込み
引数	：	const char* filename(画像のファイルパス)
---------------------------------------------------*/
void SpriteData::SetTexture(int handle)
{
	textureHandle = handle;

	// 画像サイズの取得
	int sizeX = 0;
	int sizeY = 0;
	GetGraphSize(textureHandle, &sizeX, &sizeY);

	size.x = sizeX;
	size.y = sizeY;
}

/*---------------------------------------------------
画像の描画
---------------------------------------------------*/
void SpriteData::Draw()
{
	// 中央位置の設定
	float cx = size.x * center.x;
	float cy = size.y * center.y;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(alpha * 255.0f));

	DrawRectRotaGraph3F(
		pos.x, pos.y,
		src.x, src.y,
		size.x, size.y,
		cx, cy,
		(double)scale.x, (double)scale.y,
		rot,
		textureHandle,
		TRUE
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}