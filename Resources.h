#pragma once
#include "LocalFunc.h"

class Resources {

public:

	std::string mapCsv_[8];
	std::string screenCsv_[8];
	int whiteGH_;

	Resources();
	~Resources();

	std::string GetMapCsv(int stageNum) { return mapCsv_[stageNum]; }
};

