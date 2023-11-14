#pragma once
#include "MyFunc.h"

void CalcAddress(Vector2<int>*address, Vec2 pos, Vec2 size, float radius);

/// <summary>
/// マップチップの押し戻しを行う関数(当たった面も取得できるよ)
/// </summary>
/// <param name="rowMAX"> : マップチップの行数</param>
/// <param name="colMAX"> : マップチップの列数</param>
/// <param name="playerCenterPos"> : プレイヤーの中心座標</param>
/// <param name="playerAddress"> : 現在のプレイヤーの各頂点の番地</param>
/// <param name="playerPreAddress"> : 前フレームのプレイヤーの各頂点の番地</param>
/// <param name="playerSize"> : プレイヤーの縦横幅</param>
/// <param name="playerVelocity"> : プレイヤーの移動量</param>
/// <param name="blockPos"> : ブロック座標</param>
/// <param name="blockType"> : マップチップ</param>
/// <param name="blockSize"> : ブロックの縦横幅</param>
int PushBackMapChip(
	int rowMAX, int colMAX,
	Vec2* playerCenterPos,
	Vector2<int>playerAddress[4], Vector2<int>playerPreAddress[4],
	Vec2 playerSize,
	Vec2 playerVelocity,
	std::vector<std::vector<Vec2>>blockPos,
	std::vector<std::vector<int>>blockType,
	Vec2 blockSize,
	bool& isHitMapChip
);

enum Vertex {
	LeftTop,
	RightTop,
	LeftBottom,
	RightBottom
};

enum HitDirection {
	Top = 1,
	Right = 2,
	Bottom = 3,
	Left = 4
};


//矩形と円の押し戻し関数
void PushBackBox_Ball(
	Vec2 leftTop, Vec2 rightTop, Vec2 leftBottom, Vec2 rightBottom,
	Vec2& ballPos, Vec2 preBallPos, float ballRadius,
	bool& isDrop, bool& isJump, float& dropSpeed, float& jumpSpeed,
	int& hitCount
);