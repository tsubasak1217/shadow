#pragma once
#include "LocalFunc.h"

class Resources {

public:

	std::string mapCsv_[8];
	std::string screenCsv_[8];
	int whiteGH_;
	int doorGH_;
	int blockGH_[6] = {
	Novice::LoadTexture("./Resources/images/block_normal.png"),
	Novice::LoadTexture("./Resources/images/block_high.png"),
	Novice::LoadTexture("./Resources/images/hole.png"),
	Novice::LoadTexture("./Resources/images/switch_off.png"),
	Novice::LoadTexture("./Resources/images/switch_on.png"),
	Novice::LoadTexture("./Resources/images/ground.png"),
	};

	Resources();
	~Resources();

	std::string GetMapCsv(int stageNum) { return mapCsv_[stageNum]; }
};

