#pragma once
#include "LocalFunc.h"
class Resources {

	std::string mapCsv_[8] = {
		"./Resources/csv/stage1/mapChip.csv",
		"./Resources/csv/stage2/mapChip.csv",
		"./Resources/csv/stage3/mapChip.csv",
		"./Resources/csv/stage4/mapChip.csv",
		"./Resources/csv/stage5/mapChip.csv",
		"./Resources/csv/stage6/mapChip.csv",
		"./Resources/csv/stage7/mapChip.csv",
		"./Resources/csv/stage8/mapChip.csv"
	};

	std::string screenCsv_[8] = {
		"./Resources/csv/stage1/mapChip.csv",
		"./Resources/csv/stage2/mapChip.csv",
		"./Resources/csv/stage3/mapChip.csv",
		"./Resources/csv/stage4/mapChip.csv",
		"./Resources/csv/stage5/mapChip.csv",
		"./Resources/csv/stage6/mapChip.csv",
		"./Resources/csv/stage7/mapChip.csv",
		"./Resources/csv/stage8/mapChip.csv"
	};

public:
	int whiteGH = Novice::LoadTexture("white1x1.png");

	Resources() {
	}
};

