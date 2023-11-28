#pragma once
#include "PlayerShadow.h"

class AudioPlayer {

public:
	static const int kBGMHandleMax_ = 3;
	int BGMHandle_[kBGMHandleMax_] = { 0 };
	float soundVolume_[kBGMHandleMax_] = { 0 };


	static const int kSEHandleMax_ = 1;
	int SEHandle_[kSEHandleMax_] = {0};
	float SEsoundVolume_[kSEHandleMax_] = { 0 };


	void Draw(const Resources& rs);

	AudioPlayer();

};

