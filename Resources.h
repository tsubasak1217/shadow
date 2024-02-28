#pragma once
#include "LocalFunc.h"

class Resources {

public:

	std::string mapCsv_[16];
	std::string screenCsv_[16];
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

	int tutorial_[2] = {
		Novice::LoadTexture("./Resources/images/tutorial1.png"),
		Novice::LoadTexture("./Resources/images/tutorial2.png"),//
	};

	int textureGH_[2] = {
		Novice::LoadTexture("./Resources/images/texture_paper.png"),
		Novice::LoadTexture("./Resources/images/texture_ground.png"),
	};

	int changeGH_[2] = {
		Novice::LoadTexture("./Resources/images/change1.png"),
		Novice::LoadTexture("./Resources/images/change2.png")
	};

	int crossKeyGH_[2] = {
		Novice::LoadTexture("./Resources/images/crossKey.png"),
		Novice::LoadTexture("./Resources/images/crossKey2.png")
	};

	int A_;
	int padGH_;
	int keysGH_;
	int titleFontGH_;
	int pressSpaceFontGH_;
	int pressSpaceFontGH2_;
	int pressSpaceFontGH3_;
	int rengaGH_;
	int titleBGGH_;
	int pauseMenuGH_;
	int pauseGH_;
	int stageClearFontGH_;
	int selectFontGH_;
	int creditFontGH_;
	int creditFontGH2_;
	int slashGH_;
	int WS_;
	int keyboardGH_;

	//sounds
	int BGM[3] = {
		Novice::LoadAudio("./Resources/sounds/BGM/stageBGM.mp3"),
		Novice::LoadAudio("./Resources/sounds/BGM/clearBGM.mp3"),
		Novice::LoadAudio("./Resources/sounds/BGM/titleBGM.mp3"),
	};

	/*ドアの開閉*/
	int openDoorSE_ = Novice::LoadAudio("./Resources/sounds/SE/openTheDoorSE.mp3");
	//pause画面の操作音
	int pauseSelectSE_ = Novice::LoadAudio("./Resources/sounds/SE/pauseSelectCursorSE.mp3");
	int pausePushSE_ = Novice::LoadAudio("./Resources/sounds/SE/pausePushSE.mp3");

	//アイテム入手
	int itemGetSE_ = Novice::LoadAudio("./Resources/sounds/SE/itemGetSE.mp3");
	//タイトルプレスキー
	int titlePushSE_ = Novice::LoadAudio("./Resources/sounds/SE/titleScenePushSE.mp3");
	//セレクトのライト点滅音
	int selectLightSE_ = Novice::LoadAudio("./Resources/sounds/SE/selectSceneLightSE.mp3");
	//パズルの自機が木箱を押す引きする音
	int moveBoxSE_= Novice::LoadAudio("./Resources/sounds/SE/moveBoxSE.mp3");
	//スイッチのON
	int swicthOnSE_= Novice::LoadAudio("./Resources/sounds/SE/swicthOnSE.mp3");
	//クリアプレスキー
	int clearPushSE_ = Novice::LoadAudio("./Resources/sounds/SE/clearScenePushSE.mp3");

	//select画面の操作音
	int selectCursorSE_ = Novice::LoadAudio("./Resources/sounds/SE/selectSceneCursor.mp3");
	int selectPushSE_ = Novice::LoadAudio("./Resources/sounds/SE/selectScenePushSE.mp3");

	//自機が死亡する
	int playerKilledSE_ = Novice::LoadAudio("./Resources/sounds/SE/playerKilledSE.mp3");

	//自機が死亡する
	int playerRespawnSE_ = Novice::LoadAudio("./Resources/sounds/SE/playerRespawnSE.mp3");

	//ブロックが動かせない音
	int moveFailSE_ = Novice::LoadAudio("./Resources/sounds/SE/moveFail.mp3");

	Resources();
	~Resources();

	std::string GetMapCsv(int stageNum) { return mapCsv_[stageNum]; }
};

