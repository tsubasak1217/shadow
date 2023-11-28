#pragma once
#include "Scene.h"
#include "localFunc.h"

//シーンを変える間にモーションを入れたりするためのクラス(シーン遷移)

class ChangeScene {

	/*-------------------------------セレクトからゲーム画面への状態遷移変数----------------------------------*/
#pragma region"セレクトからゲームで使う変数の宣言"
	/*セレクト画面のシーン遷移フラグ*/
	//bool isChangeSelect_;

	//escapeでタイトルに戻るフラグ
	bool isPushEscape_;


	//状態遷移イージング用
	//SCはSceneChangeの略
	Vec2 SCCPos_;//状態遷移の扉の中心座標
	Vec2 SCSize_;//中心座標のサイズ
	Vec2 SCVertex_[4];//状態遷移用の扉の４頂点
	float SCT_;//SceneChangeのｔ
	float SCAddT_;//SceneChangeのaddT
	unsigned int  SCColor_;//欄間から見える光の色



	//大きさ・座標の最大最小
	Vec2 minSCSize_;
	Vec2 maxSCSize_;
	Vec2 minSCCPos_;
	Vec2 maxSCCPos_;
	float SCEaseTimer_;
	bool isSetSCPos_;
	bool isEaseSC_;//イージングするときのフラグ


	//扉を開けるイージング用
	float openT_;
	float openAddT_;
	int easeDirO_;
	Vec2 minVertexO_[2];
	Vec2 maxVertexO_[2];
	bool isEaseO_;
	bool isSetVertexO_;

	//暗幕変数(blackoutCurtainと呼称	BC)
	float BCT_;
	float BCAddT_;
	float BCEaseTimer_;
	float BCEaseDir_;
	float maxBCColor_;
	float minBCColor_;
	float addBCColor_;
	bool isChangeColor_;
	unsigned int BCColor_;

	int BCWaitTimer_;
	int BCWaitMaxTimer_;
#pragma endregion

#pragma region""

	//ゲーム
	// 
	//EndScene以外の時
	Vec2 GCVertex_[4];//状態遷移用の扉の４頂点
	float GCT_;//SceneChangeのｔ
	float GCAddT_;//SceneChangeのaddT
	unsigned int  GCColor_;//欄間から見える光の色

	//扉を開けるイージング用
	float GopenT_;
	float GopenAddT_;
	int easeDirGO_;
	Vec2 minVertexGO_[2];
	Vec2 maxVertexGO_[2];
	bool isEaseGO_;

	const int kMaxWall = 4;
	const int kMaxStairs = 5;
	int changeTime_ = 0;
	int timeCount_ = 0;

	/*迫ってくる壁*/
	Vec2 wallPos_[4];
	float wallWidth_;
	float wallHeight_;
	Vec2 wallStartPos_[4];
	Vec2 wallEndPos_[4];
	float wallT_;
	int wallMoveTime_;

	/*階段*/
	Vec2 stairsPos_[5];
	float stairsWidth_;
	float stairsHeight_;
	Vec2 stairsStartPos_[5];
	Vec2 stairsEndPos_[5];
	float stairsT_[5];
	static const int stairsMoveTime_ = 120;
	//暗幕変数(blackoutCurtainと呼称	WS)
	float WST_;
	float WSAddT_;
	float WSEaseTimer_;
	float WSEaseDir_;
	float maxWSColor_;
	float minWSColor_;
	float addWSColor_;


	unsigned int  WallStairsColor_;//状態遷移色


	///------------------
#pragma endregion



	/*----------------------------------セレクトからゲーム画面ここまで--------------------------------*/
public:
	bool isStartChange_;
	bool isEndChange_;
	bool preIsStartChange_;
	bool preIsEndChange_;

	
	int openDoorSEHandle_;//扉が開く音
	int SECount_;

	int clearPushSEHandle_;//クリア画面のプレスキー音
	int pushSEHandle_;//セレクト画面のドア選択時ノック音

	ChangeScene() {

#pragma region"セレクトからゲームで使う変数の初期化"
		//isChangeSelect_ = false;
		isPushEscape_ = false;
		isStartChange_ = false;
		isEndChange_ = false;
		preIsStartChange_ = false;
		preIsEndChange_ = false;

		//状態遷移イージング用
		SCCPos_ = { -200,-100 };
		SCSize_ = { 50,100 };
		for (int i = 0; i < 4; i++) {
			SCVertex_[i] = { 0 };
		}
		SCT_ = 0;
		SCAddT_ = 0;
		SCColor_ = 0xFFFFFF00;
		minSCSize_ = { 0 };
		maxSCSize_ = { 0 };
		minSCCPos_ = { 0 };
		maxSCCPos_ = { 0 };
		SCEaseTimer_ = 120;
		isSetSCPos_ = false;
		isEaseSC_ = false;

		//ドアを開くイージング用
		openT_ = 0;
		openAddT_ = 0;
		easeDirO_ = 1;
		for (int j = 0; j < 2; j++) {
			minVertexO_[j] = { 0,0 };
			maxVertexO_[j] = { 0,0 };
		}
		isEaseO_ = false;
		isSetVertexO_ = false;

		//暗幕変数(blackoutCurtainと呼称	BC)
		BCT_ = 0;
		BCAddT_ = 0;
		BCEaseTimer_ = 51;
		BCEaseDir_ = 1;
		maxBCColor_ = 0xff;
		minBCColor_ = 0x0;
		addBCColor_ = 0x0;
		isChangeColor_ = false;
		BCColor_ = 0xFFFFFF00;



		BCWaitMaxTimer_ = 120;
		BCWaitTimer_ = BCWaitMaxTimer_;
#pragma endregion

#pragma region"ゲームからクリアまでの処理"

		//EndScene以外の時
		for (int i = 0; i < 4; i++) {
			GCVertex_[i] = { 0 };//状態遷移用の扉の４頂点
		}
		GCT_ = 0;//SceneChangeのｔ
		GCAddT_ = 0;//SceneChangeのaddT
		GCColor_ = 0xFFFFFFFF;//欄間から見える光の色

		//扉を開けるイージング用
		GopenT_ = 0;
		GopenAddT_ = 0;
		easeDirGO_ = 1;
		for (int j = 0; j < 2; j++) {
			minVertexGO_[j] = { 0 };
			maxVertexGO_[j] = { 0 };
		}
		isEaseGO_ = false;

		/*迫ってくる壁*/

		wallWidth_ = float(Global::windowSize_.x);
		wallHeight_ = float(Global::windowSize_.y);

		//EndScene以外の時
		for (int i = 0; i < 4; i++) {
			wallPos_[i] = { 0 };
			wallStartPos_[i] = { 0 };
			wallEndPos_[i] = { 0 };
		}
		wallT_ = 0;
		wallMoveTime_ = 120;

		/*階段*/

		stairsWidth_ = 41.2f;
		stairsHeight_ = 18.5f;
		for (int i = 0; i < 5; i++) {
			stairsPos_[i] = { 0 };
			stairsStartPos_[i] = { 0 };
			stairsEndPos_[i] = { 0 };
			stairsT_[i] = { 0 };
		}
		//暗幕変数(blackoutCurtainと呼称	WS)
		WST_ = 0;
		WSAddT_ = 0;
		WSEaseTimer_ = 60;
		WSEaseDir_ = 1;
		maxWSColor_ = 0x0;
		minWSColor_ = 0xFF;
		addWSColor_ = 0x0;
		isChangeColor_ = false;

		WallStairsColor_ = 0x000000FF;


#pragma endregion


		openDoorSEHandle_ = -1;

		SECount_ = 0;

		clearPushSEHandle_ = -1;
		pushSEHandle_ = -1;
	}


	void UpDate(char* keys, char* preKeys, bool& isChangeScene, Vec2 CPos[],
		int selectNum, bool& CanCS, Vec2 goalPos, Vec2 goalSize, bool& isPauseSelect, bool& isTitlePush
		, bool& stageReset, const Resources& rs, int& selectLightSEHandle,
		int BGMHandle_[3], float soundVolume_[3]);
	void Draw(int GH, unsigned int DoorColor, Vec2 goalPos, Vec2 goalSize, bool& isPauseSelect);
	void Reset();
	//bool GetIsStart() { return isStartChange_; }
	//bool GetIsEnd() { return isEndChange_; }
};

