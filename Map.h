#pragma once
#include "global.h"

class Map
{
	//変数
	std::vector<std::vector<Vec2>>pos_;
	std::vector<std::vector<int>>mapChip_;
	std::vector<std::vector<bool>>touchable_;

	std::vector<std::vector<Vec3>>vertex_;

	Vec3 size_;
	Vec2 puzzleLeftTop_;
	Vec2 puzzleMapSize_;

public:

	//マップチップから取得したプレイヤーの初期座標を格納する変数		
	Vec2 firstPlayerPos_;

	//コンストラクタ
	Map(Global global);

	void Init();

	//
	void Update(char* keys, Global global);

	//
	void Draw(Resources rs);

	//アクセッサ
	std::vector<std::vector<int>>GetMapChip() { return mapChip_; }
	Vec3 GetSize() { return size_; }
	Vec2 GetPuzzleLeftTop() { return puzzleLeftTop_; }
	Vec2 GetPuzzleMapSize() { return puzzleMapSize_; }

	//ブロックの頂点座標を取得する関数
	std::vector<std::vector<Vec3>>GetVertex() { return vertex_; }
	Vec3 GetVertex(int BlockNum, int vertexNum) { return vertex_[BlockNum][vertexNum]; }
};

enum BlockType {
	EMPTY,
	NORMAL
};

