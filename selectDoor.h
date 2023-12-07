#pragma once
#include"Map.h"

const int DOOR_MAX = 16;
class SelectDoor {

public:
	//ドア本体の変数
	Vec2 CPos_[DOOR_MAX];//各ドアの中心座標
	Vec2 size_;//各ドアの大きさ
	Vec2 Drawsize_;//描画するSpriteの倍率
	bool isDraw_[DOOR_MAX];//表示するか否かのフラグ
	Vec2 vertex_[DOOR_MAX][4];//各頂点
	unsigned int color_;	//ドア本体の色
	unsigned int lightColor_[DOOR_MAX];	//欄間から見える光の色
	bool isStageClear_[DOOR_MAX];//クリアしているか否か
	int GH_;//ドアの画像

	//扉移動のイージング用
	bool isEaseM_;//イージング開始のフラグ
	float easeTimerM_;//フレーム指定
	float moveT_;
	float moveAddT_;
	Vec2  moveMinPos_;//最小地点
	Vec2  moveMaxPos_;//最大地点

	//シーン遷移に移行するフラグ
	bool isChangeScene_;


	//選択された範囲の変数
	int selectNum_;//扉の番号
	Vec2 selectPos_;//範囲の中心座標
	unsigned int selectColor_;//範囲の色

	bool isSelectDraw_;//点滅させるフラグ
	int DrawTimer_;//現在の時間
	int DrawTimerMax_;//リセット用最大時間

	/*ステージ番号表示のライト*/
	/*表示の円（描画で三段階）*/
	Vec2 NumlightEllCPos_;
	Vec2 NumlightEllSize_;
	bool isDrawNL_;
	/*イージングDrawLight*/
	float DLT_;
	float DLAddT_;
	/*イージングの時間*/
	float DLEaseTimer_;
	/*方向*/
	float DLEaseDir_;

	float maxDLColor_;
	float minDLColor_;
	float addDLColor_;
	/*表示され続ける時間*/
	float DLWaitTimer_;
	float DLWaitTimerMax_;
	/*色*/
	unsigned int DLColor_;


	/*ライトに映るステージ番号の中心座標*/
	Vec2 NumCPos_;
	Vec2 NumCPosTens_;//１０の位
	Vec2 NumCPosOnes_;//１の位
	
	/*ライトに映るステージの番号の各頂点*/
	Vec2 NumVertex_[4];
	Vec2 NumVertexTens_[4];
	Vec2 NumVertexOnes_[4];
	/*番号のリソース*/
	int NumGH_;
	/*描画する左上のサイズ*/
	int GHSize_;
	/*映る番号の色*/
	unsigned int NumColor_;

	// 「/16」を表示する
	Vec2 maxNumCPos_[2];
	Vec2 maxNumSize_;
	Vec2 maxNumVertex_[2][4];
	/*「/」を表示する*/
	Vec2 slashCPos_;
	Vec2 slashSize_;
	Vec2 slashVertex_[4];

	/*セレクトロゴの文字*/
	Vec2 	selectFontCPos_;
	Vec2 	selectFontSize_;
	unsigned int FColor_;


	/*効果音*/
	int lightSEHandle_;//ライトの点滅
	int selectCursorSEHandle_;//扉選択のカーソル音

	SelectDoor() {
		//ドア本体の変数
		for (int i = 0; i < DOOR_MAX; i++) {
			CPos_[i] = { float(Global::windowSize_.x / 2) + (float(Global::windowSize_.x / 2) * i),float(Global::windowSize_.y / 2 - 100) };
			size_ = { 200,400 };
			Drawsize_ = { 0 };
			isDraw_[i] = true;
			lightColor_[i] = 0xFFFFFFFF;
			isStageClear_[i] = false;
			for (int j = 0; j < 4; j++) {
				vertex_[i][j] = { 0 };
			}
		}
		color_ = 0x000000FF;

		//扉移動のイージング用
		isEaseM_ = false;//イージング開始のフラグ
		easeTimerM_ = 20;//フレーム指定
		moveT_ = 0;
		moveAddT_ = 0;
		moveMinPos_ = CPos_[0];//最小地点
		moveMaxPos_ = CPos_[0];//最大地点


		GH_ = Novice::LoadTexture("./Resources/images/Door.png");


		//選択範囲の変数
		selectNum_ = 0;
		selectPos_ = { 0 };
		selectColor_ = 0xFF0000FF;
		isSelectDraw_ = false;
		DrawTimerMax_ = 45;
		DrawTimer_ = DrawTimerMax_;

		/*ライトの変数*/
		NumlightEllCPos_ = { 240,660 };//{ 240,535 };
		NumlightEllSize_ = { 185,85 };  //{ 170,140 };
		isDrawNL_ = false;
		//番号の変数
		NumCPos_ = { 235,652 };//{ 220,645 };
		NumCPosTens_ = { 235,652 };//{ 220,645 };
		NumCPosOnes_ = { 235,652 };//{ 220,645 };

		// 「/16」を表示する
		maxNumCPos_[0] = { 331,704 };
		maxNumCPos_[1] = { 361,704 };
		maxNumSize_ = { 44,22 };
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				maxNumVertex_[i][j] = { 0 };
			}
		}
		slashCPos_ = { 309,696 };
		slashSize_ = { 76,45 };  //{ 170,140 };


		for (int i = 0; i < 4; i++) {
			slashVertex_[i] = { 0 };
			NumVertex_[i] = { 0 };
			NumVertexTens_[i] = { 0 };
			NumVertexOnes_[i] = { 0 };
		}

		NumGH_ = Novice::LoadTexture("./Resources/images/number.png");
		GHSize_ = 25;
		NumColor_ = 0x444444FF;

		/*イージングDrawLight*/
		DLT_ = { 0 };
		DLAddT_ = { 0 };

		/*イージングの時間*/
		DLEaseTimer_ = 60;
		/*方向*/
		DLEaseDir_ = 1;
		maxDLColor_ = 0x22;
		minDLColor_ = 0x0;
		addDLColor_ = 0x0;
		/*表示され続ける時間*/
		DLWaitTimerMax_ = 600;
		DLWaitTimer_ = DLWaitTimerMax_;
		/*色*/
		DLColor_ = 0x00;


		selectFontCPos_ = { 240,85 };
		selectFontSize_ = { 440,110 };
		FColor_ = 0xFFFFFFFF;
		isChangeScene_ = false;

		lightSEHandle_ = -1;
		selectCursorSEHandle_ = -1;
	};

	void Draw(Resources rs);

	void Update(char* keys, char* preKeys, const Resources& rs, int starGetCount);
	void Debug(char* keys, char* preKeys);
	void Reset();
};
