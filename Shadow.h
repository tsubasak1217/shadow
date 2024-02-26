#pragma once
#include "Screen.h"
#include "Player.h"
#include "SaveData.h"

class Shadow {

	//マップチップ
	std::vector<std::vector<Vec2>>pos_;//座標
	std::vector<std::vector<int>>mapChip_;//マップチップ番号
	std::vector<std::vector<bool>>touchable_;//存在フラグ

	Vec2 size_;//ブロックの縦横
	Vec2 goalPos_;//ゴールの中心座標
	Vec2 goalSize_;//ゴールの縦横
	Vec2 goalVertex_[4];//ゴールの頂点

public:

	int pressTimeCount_;

	//マップチップから取得したプレイヤーの初期座標を格納する変数		
	Vec2 firstPlayerPos_;

	//コンストラクタ
	Shadow(const Resources& rs, Screen screen);

	void Init(const Resources& rs,Screen screen, int sceneNum);

	//
	void Update(char* keys, const ChangeScene& cs, const Resources& rs, const Screen& screen, Map map);

	//
	void Draw(const Resources& rs);

	Vec2 GetSize() { return size_; }
	Vec2 GetGoalPos() { return goalPos_; }
	Vec2 GetGoalSize() { return goalSize_; }
	Vec2 GetGoalLT() { return goalVertex_[0]; }
	Vec2 GetGoalRT() { return goalVertex_[1]; }
	Vec2 GetGoalLB() { return goalVertex_[2]; }
	Vec2 GetGoalRB() { return goalVertex_[3]; }
	std::vector<std::vector<int>>GetMapChip() { return mapChip_; }
	void SetMapChip(int row,int col,int mapchip) { mapChip_[row][col] = mapchip; }
	std::vector<std::vector<Vec2>>GetPos() { return pos_; }
	std::vector<std::vector<bool>>GetTouchable() { return touchable_; }

	void ReturnSavePoint() { mapChip_ = SaveData::savedShadowMap_; }
};

