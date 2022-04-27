#include"Collision.h"

/*--------------------------------------------------------
ほかの円との当たり判定
-----------------------------------------------------------*/
bool CircleCollider::CheckHit(CircleCollider collider)
{
	//2点の位置を原点からベクトルにする
	float x = collider.mPos.mX - mPos.mX;
	float y = collider.mPos.mY - mPos.mY;

	//ベクトルの長さを計算
	float l = (x * x) + (y * y);

	//半径の合計を取得
	float circleLen = mRadius + collider.mRadius;

	//半径の合計を2乗する(sqrtは処理が重いため使わないための処置)
	circleLen *= circleLen;

	//ベクトルが2つの円の半径より短ければ当たっている
	if (l <= circleLen)
	{
		return true;
	}

	return false;
}