#include "AudioPlayer.h"

void AudioPlayer::Draw(const Resources& rs) {

	switch (Scene::sceneNum_) {

	case TITLE:

		//BGMを鳴らす
		if (!Novice::IsPlayingAudio(BGMHandle_[0]) or BGMHandle_[0] == -1) {
			BGMHandle_[0] = Novice::PlayAudio(rs.BGM[0], 1, soundVolume_[0]);
		}
		break;
	case SELECT:
		break;
	case GAME:
		break;
	case CLEAR:

		//BGMを鳴らす
		Novice::StopAudio(BGMHandle_[0]);

		break;
	default:
		break;
	}
}

AudioPlayer::AudioPlayer() {

	for (int i = 0; i < kBGMHandleMax_; i++) {
		BGMHandle_[i] = -1;
		soundVolume_[i] = 0.12f;
	}
}
