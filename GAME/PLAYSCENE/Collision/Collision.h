#pragma once
#include"../../Utility.h"

//‰~‚Ì”»’è—p\‘¢‘Ì
struct CircleCollider
{
	//•Ï”=====================================

	//”¼Œa
	float mRadius;

	//À•W
	Float2 mPos;

	//ŠÖ”======================================

	CircleCollider()
		:mRadius(0.0f)
		,mPos()
	{

	}

	//‚Ù‚©‚Ì‰~‚Æ‚Ì“–‚½‚è”»’è
	bool CheckHit(CircleCollider collider);
};