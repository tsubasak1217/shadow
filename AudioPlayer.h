#pragma once
#include "PlayerShadow.h"

class AudioPlayer {

public:
	static const int kBGMHandleMax_ = 1;
	int BGMHandle_[kBGMHandleMax_] = { 0 };
	float soundVolume_[kBGMHandleMax_] = { 0 };

	void Draw(const Resources& rs);

	AudioPlayer();

};

