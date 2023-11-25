#pragma once
#include "LocalFunc.h"

class Resources {

public:

	std::string mapCsv_[8];
	std::string screenCsv_[8];
	int whiteGH_;
	int doorGH_;
	int titleFontGH_;
	int pressSpaceFontGH_;
	int rengaGH_;
	int titleBGGH_;

	Resources();
	~Resources();

	std::string GetMapCsv(int stageNum) { return mapCsv_[stageNum]; }
};

