#include "AudioPlayer.h"

void AudioPlayer::Draw(const Resources& rs) {

	switch (Scene::sceneNum_) {

	case TITLE:
		//BGMを止める
		Novice::StopAudio(BGMHandle_[0]);
		//BGMを鳴らす
		if (!Novice::IsPlayingAudio(BGMHandle_[2]) or BGMHandle_[2] == -1) {
			BGMHandle_[2] = Novice::PlayAudio(rs.BGM[2], 1, soundVolume_[2]);
		}

		break;
	case SELECT:
		Novice::StopAudio(BGMHandle_[1]);
		Novice::StopAudio(BGMHandle_[2]);

		//BGMを鳴らす
		if (!Novice::IsPlayingAudio(BGMHandle_[0]) or BGMHandle_[0] == -1) {
			BGMHandle_[0] = Novice::PlayAudio(rs.BGM[0], 1, soundVolume_[0]);
		}
		Novice::ResumeAudio(BGMHandle_[0]);




		break;
	case GAME:
		Novice::StopAudio(BGMHandle_[1]);
		Novice::StopAudio(BGMHandle_[2]);



		break;
	case CLEAR:

		//BGMを止める
		Novice::StopAudio(BGMHandle_[0]);
		//BGMを鳴らす
		if (!Novice::IsPlayingAudio(BGMHandle_[1]) or BGMHandle_[1] == -1) {
			BGMHandle_[1] = Novice::PlayAudio(rs.BGM[1], 1, soundVolume_[1]);
		}


		break;
	default:
		break;
	}
}

AudioPlayer::AudioPlayer() {

	for (int i = 0; i < kBGMHandleMax_; i++) {
		BGMHandle_[i] = -1;
		soundVolume_[i] = 0;
	}
	//タイトルなので最初から音が出るようにする
	soundVolume_[2] = 0.06f;
	
		for (int i = 0; i < kSEHandleMax_; i++) {
		SEHandle_[i] = -1;
		SEsoundVolume_[i] = 0.12f;
	}

}
