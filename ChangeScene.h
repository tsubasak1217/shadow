#pragma once
#include "Scene.h"
#include "localFunc.h"

//シーンを変える間にモーションを入れたりするためのクラス(シーン遷移)

class ChangeScene {

	/*-------------------------------セレクトからゲーム画面への状態遷移変数----------------------------------*/
	/**/
	bool isChangeSelect_;


	//状態遷移イージング用
	//SCはSceneChangeの略
	Vec2 SCCPos_;//状態遷移の扉の中心座標
	Vec2 SCSize_;//中心座標のサイズ
	Vec2 SCVertex_[4];//状態遷移用の扉の４頂点
	float SCT_;//SceneChangeのｔ
	float SCAddT_;//SceneChangeのaddT
	unsigned int  SCColor_;

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
	/*----------------------------------セレクトからゲーム画面ここまで--------------------------------*/
public:
	ChangeScene(){
		isChangeSelect_ = false;

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
	}

	void SelectFromGameUpDate(bool&isChangeScene,Vec2 CPos[],int selectNum);
	void SelectFromGameDraw(int GH, unsigned int DoorColor);
	void Reset(bool& isChangeScene);
};

