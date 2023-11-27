#pragma once
#include "LocalFunc.h"

class Resources {

public:

	std::string mapCsv_[8];
	std::string screenCsv_[8];
	int whiteGH_;
	int doorGH_;
	int blockGH_[7] = {
	Novice::LoadTexture("./Resources/images/block_normal.png"),
	Novice::LoadTexture("./Resources/images/block_high.png"),
	Novice::LoadTexture("./Resources/images/hole.png"),
	Novice::LoadTexture("./Resources/images/switch_off.png"),
	Novice::LoadTexture("./Resources/images/switch_on.png"),
	Novice::LoadTexture("./Resources/images/ground.png"),
	Novice::LoadTexture("./Resources/images/light.png"),
	};
	int titleFontGH_;
	int pressSpaceFontGH_;
	int rengaGH_;
	int titleBGGH_;
	int pauseMenuGH_;
	int pauseGH_;
	int stageClearFontGH_;
	int stageClearFont2GH_;
	int selectFontGH_;
	int creditFontGH_;

	//sounds
	int BGM[3] = {
		Novice::LoadAudio("./Resources/sounds/stageBGM.mp3"),
		Novice::LoadAudio("./Resources/sounds/clearBGM.mp3"),
		Novice::LoadAudio("./Resources/sounds/titleBGM.mp3"),
	};

	/*ドアの開閉*/
	int openDoorSE_ = Novice::LoadAudio("./Resources/sounds/SE/openTheDoorSE.mp3");
	//pause画面の操作音
	int pauseSelectSE_ = Novice::LoadAudio("./Resources/sounds/SE/pauseSelectSE.mp3");
	int pausePushSE_ = Novice::LoadAudio("./Resources/sounds/SE/pausePushSE.mp3");
	//アイテム入手
	int itemGetSE_ = Novice::LoadAudio("./Resources/sounds/SE/itemGetSE.mp3");

	int titlePushSE_ = Novice::LoadAudio("./Resources/sounds/SE/titlePushSE.mp3");

	int selectLightSE_ = Novice::LoadAudio("./Resources/sounds/SE/selectLightSE.mp3");

	Resources();
	~Resources();

	std::string GetMapCsv(int stageNum) { return mapCsv_[stageNum]; }
};

