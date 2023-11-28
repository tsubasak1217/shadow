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

	int tutorial_[2] = {
		Novice::LoadTexture("./Resources/images/tutorial1.png"),
		Novice::LoadTexture("./Resources/images/block_high.png"),//
	};

	int textureGH_[2] = {
		Novice::LoadTexture("./Resources/images/texture_paper.png"),
		Novice::LoadTexture("./Resources/images/texture_ground.png"),
	};

	int keysGH_;
	int titleFontGH_;
	int pressSpaceFontGH_;
	int rengaGH_;
	int titleBGGH_;
	int pauseMenuGH_;
	int pauseGH_;
	int stageClearFontGH_;
	int stageClearFont2GH_;
	int selectFontGH_;

	//sounds
	int BGM[1] = {
		Novice::LoadAudio("./Resources/sounds/stageBGM.mp3"),
	};

	int WindowGH_;

	Resources();
	~Resources();

	std::string GetMapCsv(int stageNum) { return mapCsv_[stageNum]; }
};

