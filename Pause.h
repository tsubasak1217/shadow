#pragma once
#include"Map.h"

class Pause {

	//PAUSEの文字
	Vec2 pauseFontPos_;
	Vec2 pauseFontSize_;



	//選択する場所
	float BOffset_;
	float BSpace_;
	Vec2 buttonPos_[3];
	Vec2 buttonSize_[3];
	Vec2 buttonDrawSize_[3];
	Vec2 buttonDrawScale_[3];


	//ボタンの色
	unsigned int buttonColor_[3];//灰色


	//選択された範囲
	int selectNum_;//扉の番号
	unsigned int selectColor_;//選択したところの色（白）



	/*装飾*/
	//猫
	Vec2 catPos_;
	Vec2 catSize_;
	float catDir_;
	float theta_;
	Vec2 originPos_;
	Vec2 length_;//{1150,0}
	Vec2 rotateLength_;
	float maxTheta_;
	float minTheta_;


	//地面
	Vec2 lineStart_;
	Vec2 lineEnd_;

	//猫、line,フォントの色
	unsigned int elseColor_;

	//暗幕変数(blackoutCurtainと呼称	BC)
	float BCT_;
	float BCAddT_;
	float BCEaseTimer_;
	float BCEaseDir_;

	float minColor_;
	float maxBCColor_;
	float addBCColor_;

	float maxElseColor_;
	float addElseColor_;

	//暗幕の色
	unsigned int BCColor_;

	int SelectSEHandle_;
	int PushSEHandle_;


public:

	bool isPause_;//PAUSE画面か否か
	bool isStartPause_;
	bool isEndPause_;
	bool isStageReset_;
	bool isSelect_;//選択するフラグ

	int debugNum = 0;
	Pause() {
		//PAUSEの文字

		pauseFontSize_ = { 265,75 };
		pauseFontPos_ = { 345 ,60 };

		//選択する場所
		BOffset_ = 200;
		BSpace_ = 150;

		for (int i = 0; i < 3; i++) {
			buttonSize_[i] = { 265,75 };
			buttonDrawSize_[i] = { 265,75 };
			buttonDrawScale_[i] = { 0.33f,1.0f };
			buttonPos_[i] = { float(Global::windowSize_.x) / 2,(BSpace_ * i + BOffset_) };
			//全体の色
			buttonColor_[i] = 0x66666600;//灰色
		}


		//選択された範囲
		selectNum_ = 0;//選択する番号
		selectColor_ = 0xFFFFFF00;//選択したところの色（白）


		isSelect_ = false;//選択するフラグ

		/*装飾*/

		//地面
		lineStart_ = { 0,650 };
		lineEnd_ = { float(Global::windowSize_.x),650 };

		//猫
		catSize_ = { 100,100 };
		catPos_ = { -catSize_.x,lineStart_.y - catSize_.y / 2 };
		catDir_ = 1;
		theta_ = 0.0f;
		originPos_ = { -catSize_.x,lineStart_.y - catSize_.y / 2 };//{640,1490}
		length_ = { 200,0 };//{1150,0}
		rotateLength_ = { 0 };
		maxTheta_ = 0;
		minTheta_ = (float(-M_PI));

		BCT_ = 0;
		BCAddT_ = 0;
		BCEaseTimer_ = 30;
		BCEaseDir_ = 1;

		minColor_ = 0x0;
		maxBCColor_ = 0xFD;
		addBCColor_ = minColor_;

		maxElseColor_ = 0xFF;
		addElseColor_ = minColor_;

		BCColor_ = 0x00000000;
		elseColor_ = 0xFFFFFF00;

		isPause_ = false;//PAUSE画面か否か
		isStartPause_ = false;//PAUSE画面か否か
		isEndPause_ = false;//PAUSE画面か否か
		isStageReset_ = false;


		SelectSEHandle_ = -1;
		PushSEHandle_ = -1;

	}
	void Draw(Resources rs);
	void Update(ChangeScene& cs, char* keys, char* preKeys, const Resources& rs);
	void Debug(char* keys, char* preKeys);
	void Reset();
};