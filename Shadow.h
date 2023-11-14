#pragma once
#include "Screen.h"
#include "Map.h"

class Shadow {

	//マップチップ
	std::vector<std::vector<Vec2>>pos_;//座標
	std::vector<std::vector<int>>mapChip_;//マップチップ番号
	std::vector<std::vector<bool>>touchable_;//存在フラグ

	Vec2 size_;//ブロックの縦横

public:

	//マップチップから取得したプレイヤーの初期座標を格納する変数		
	Vec2 firstPlayerPos_;

	//コンストラクタ
	Shadow(const Resources& rs,Screen screen);

	void Init(const Resources& rs,int sceneNum);

	//
	void Update(char* keys);

	//
	void Draw(const Resources& rs);

	Vec2 GetSize() { return size_; }
	std::vector<std::vector<int>>GetMapChip() { return mapChip_; }
	std::vector<std::vector<Vec2>>GetPos() { return pos_; }
};

