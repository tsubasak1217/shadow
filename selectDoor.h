#pragma once
#include"Map.h"

const int DOOR_MAX = 8;
class SelectDoor {

public:
	//ドア本体の変数
	Vec2 CPos_[DOOR_MAX];//各ドアの中心座標
	Vec2 size_;//各ドアの大きさ
	Vec2 Drawsize_;//描画するSpriteの倍率

	float theta_[DOOR_MAX];//原点からの角度
	bool isDraw_[DOOR_MAX];//表示するか否かのフラグ
	Vec2 vertex_[DOOR_MAX][4];//各頂点


	unsigned int color_;	//ドア本体の色
	unsigned int lightColor_[DOOR_MAX];	//欄間から見える光の色
	bool isStageClear_[DOOR_MAX];//クリアしているか否か

	int GH_;//ドアの画像


	//円周上に並んでいるドアの原点
	Vec2 originPos_;//原点の座標
	Vec2 rotateLength_[DOOR_MAX];//回した長さ
	Vec2 length_;//長さ

	//シーン遷移に移行するフラグ
	bool isChangeScene_;


	//選択された範囲の変数
	int selectNum_;//扉の番号
	Vec2 selectPos_;//範囲の中心座標
	unsigned int selectColor_;//範囲の色

	bool isSelectDraw_;//点滅させるフラグ
	int DrawTimer_;//現在の時間
	int DrawTimerMax_;//リセット用最大時間

	bool isEaseS_;//イージング開始のフラグ
	float easeTimerS_;//フレーム指定
	float selectT_;
	float selectAddT_;
	Vec2  selectMinPos_;//最小地点
	Vec2  selectMaxPos_;//最大地点

	//床の形？？？？
	Vec2 EllSize_;
	Vec2 EllPos_;


	int debugNum = 0;

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

	Vec2 NumVertex_[4];
	int NumGH_;
	int GHSize_;
	unsigned int NumColor_;
	/*セレクトの文字*/
	Vec2 	selectFontCPos_;
	Vec2 	selectFontSize_;
	unsigned int FColor_;

	/*効果音*/
	int lightSEHandle_;//ライトの点滅
	int selectCursorSEHandle_;//扉選択のカーソル音

	SelectDoor() {
		//ドア本体の変数
		for (int i = 0; i < DOOR_MAX; i++) {
			CPos_[i] = { 0 };
			size_ = { 50,100 };
			Drawsize_ = { 0 };
			theta_[i] = { 0 };
			isDraw_[i] = true;
			
			lightColor_[i] =0xFFFFFFFF;
			isStageClear_[i] = false;

			rotateLength_[i] = { 0 };
			for (int j = 0; j < 4; j++) {
				vertex_[i][j] = { 0 };
			}
		}
		color_ = 0x000000FF;
		//0xFFFFFFFF

		GH_ = Novice::LoadTexture("./Resources/images/Door.png");
		//円周上に並んでいるドアの原点
		originPos_ = { 240,512 };
		length_ = { 215,0 };

		//選択範囲の変数
		selectNum_ = 0;
		selectPos_ = { 0 };
		selectColor_ = 0xFF0000FF;
		isSelectDraw_ = false;
		isEaseS_ = false;
		DrawTimerMax_ = 45;
		DrawTimer_ = DrawTimerMax_;
		easeTimerS_ = 2.0f;
		selectT_ = 0.0f;
		selectAddT_ = 0.0f;
		selectMinPos_ = CPos_[0];
		selectMaxPos_ = CPos_[0];
		//床の円
		EllSize_ = { 260,276 };
		EllPos_ = { 240,615 };

		NumlightEllCPos_ = { 240,535 };
		NumlightEllSize_ = { 170,140 };
		isDrawNL_ = false;
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
		for (int j = 0; j < 4; j++) {
			NumVertex_[j] = { 0 };
		}
		NumGH_ = Novice::LoadTexture("./Resources/images/number.png");
		GHSize_ = 25;
		NumColor_ = 0x444444FF;

		selectFontCPos_ = { 240,145 };
		selectFontSize_ = { 440,110 };
		FColor_ = 0xFFFFFFFF;
		isChangeScene_ = false;

		lightSEHandle_ = -1;
		selectCursorSEHandle_ = -1;
	};

	void Draw(Resources rs);

	void Update(char* keys, char* preKeys, const Resources& rs,int starGetCount);
	void Debug(char* keys, char* preKeys);
	void Reset();
};
