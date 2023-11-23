#pragma once
#include "ChangeScene.h"

class Map
{
	//マップチップ
	std::vector<std::vector<Vec2>>pos_;//座標
	std::vector<std::vector<Vec2>>posCopy_;//座標のコピー
	std::vector<std::vector<int>>mapChip_;//マップチップ番号
	std::vector<std::vector<int>>mapChipCopy_;//マップチップ番号のコピー
	std::vector<std::vector<bool>>touchable_;//存在フラグ

	std::vector<std::vector<Vec3>>vertex_;//マップのブロックの各頂点座標(疑似的な三次元)

	Vec3 size_;//ブロックの縦横奥ゆき
	Vec2 puzzleLeftTop_;//パズル(画面下半分ののマップチップ)の左上座標
	Vec2 puzzleMapSize_;//パズル画面の縦横幅

	bool isPressSwitch_;//スイッチが押されたかのフラグ

public:

	static int stageNum_;

	//マップチップから取得したプレイヤーの初期座標を格納する変数		
	Vec2 firstPlayerPos_;

	//コンストラクタ
	Map(const Resources& rs);

	void Init(int sceneNum);

	//
	void Update(char* keys, const Resources& rs);

	//
	void Draw(const Resources& rs);
	void DrawBG();

	//アクセッサ
	std::vector<std::vector<int>>GetMapChip() { return mapChip_; }
	void SetMapChip(int row, int col, int value) { mapChip_[row][col] = value; }
	std::vector<std::vector<int>>GetMapChipCopy() { return mapChipCopy_; }

	Vec3 GetSize() { return size_; }
	Vec2 GetPuzzleLeftTop() { return puzzleLeftTop_; }
	Vec2 GetPuzzleMapSize() { return puzzleMapSize_; }

	std::vector<std::vector<Vec2>>GetPos() { return pos_; }
	Vec2* GetPosP(int row, int col) { return &pos_[row][col]; }
	void SetPos(int row,int col,Vec2 pos) { pos_[row][col] = pos; }

	//ブロックの頂点座標を取得する関数
	std::vector<std::vector<Vec3>>GetVertex() { return vertex_; }
	Vec3 GetVertex(int BlockNum, int vertexNum) { return vertex_[BlockNum][vertexNum]; }

	int GetStageNum(){return stageNum_;}

	//スイッチが押されたかどうかのアクセッサ
	void SetIsPressSwitch(bool flag) { isPressSwitch_ = flag; }
	bool GetIsPressSwitch() { return isPressSwitch_; }
};

enum BlockType {
	EMPTY,
	NORMAL
};

