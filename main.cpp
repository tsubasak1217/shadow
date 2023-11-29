
#include "Particle.h"
#include"Title.h"
#include "selectDoor.h"
#include "selectLightParticle.h"
#include"stageClearEffect.h"
#include"stageClear.h"
#include"Pause.h"
#include "ImGuiManager.h"
#include "AudioPlayer.h"

//======================================================
//					グローバル変数/定数
//======================================================

const char kWindowTitle[] = "1207_迷暗";

//======================================================
//					  構造体など
//======================================================

void DrawTutorial(const Resources& rs);

//======================================================
//					  main関数
//======================================================

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Global global;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, global.windowSize_.x, global.windowSize_.y);

	unsigned int currentTime = unsigned int(time(nullptr));
	srand(currentTime);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Resources rs;
	AudioPlayer audio;

	Scene scene;
	ChangeScene cs;


	Emitter emitter;
	Particle particle[120];

	Map map(rs);
	Player player(map);
	Light light(map);
	Screen screen(map, light);
	Shadow shadow(rs, screen);
	PlayerShadow playerShadow(screen, shadow);
	Title title;
	SelectDoor door;//セレクト画面
	StageClear stageClear;//ステージクリア
	SCE SCE;//ステージクリアのパーティクル
	Pause pause;

	SelectLightParticle SLParticle[120];

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		global.Update();

		cs.UpDate(keys, preKeys, door.isChangeScene_, door.CPos_, door.selectNum_, stageClear.canSceneChange,
			shadow.GetGoalPos(), shadow.GetGoalSize(), pause.isSelect_, title.isPush_,pause.isStageReset_,rs,door.lightSEHandle_,audio.BGMHandle_, audio.soundVolume_);

		map.Update(keys, rs, cs);
		player.Update(keys, cs, map, pause.isPause_,rs);
		light.Update(keys, cs, map, ((3.0f / 4.0f) * float(M_PI)), pause.isPause_);

		screen.Update(keys, cs, map, light);
		shadow.Update(keys, cs, rs, screen, map);

		SCE.Update(stageClear, playerShadow.GetstarCount());
		playerShadow.Update(keys, preKeys, rs, cs, screen, shadow, player, map, light, pause.isPause_);
		for (int i = 0; i < 120; i++) {
			particle[i].Update(emitter, playerShadow, shadow, screen);
		}

		title.Update(keys, preKeys, rs);
		door.Update(keys, preKeys, rs);
		stageClear.Update(cs.isStartChange_, playerShadow.GetstarCount());

		pause.Update(cs, keys, preKeys,rs,audio.BGMHandle_[0],audio.soundVolume_[0]);

		for (int i = 0; i < 120; i++) {
			SLParticle[i].Update(door, light);
		}

		//stageClear.Debug(keys, preKeys);

		//デバックでのみ操作可能
#if _DEBUG
		/*シーン遷移が終了した状態でしかシーンを移動できない*/
		if (!cs.isEndChange_ && !cs.isStartChange_) {
			if (keys[DIK_1]) {
				Scene::sceneNum_ = TITLE;
			} else if (keys[DIK_2]) {
				Scene::sceneNum_ = SELECT;
			} else if (keys[DIK_3]) {
				Scene::sceneNum_ = GAME;
			} else if (keys[DIK_4]) {
				Scene::sceneNum_ = CLEAR;
			}
		}
#endif DEBUG

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		map.DrawBG(rs);
		map.DrawSwitch(rs);
		screen.DrawBG(rs);

		playerShadow.Draw(keys, rs, screen);
		shadow.Draw(rs);
		screen.Draw(map, rs, light);

		for (int i = 0; i < 120; i++) {
			particle[i].Draw();

		}

		light.Draw(rs, map, cs);
		map.Draw(rs);
		player.Draw(keys, rs);


		title.Draw(rs);
		door.Draw(rs);
		stageClear.Draw(rs);


		for (int i = 0; i < 120; i++) {
			SLParticle[i].Draw(keys);
		}

		DrawTutorial(rs);

		playerShadow.PlayerShadowManager(rs, playerShadow);

		SCE.Draw(playerShadow.GetstarCount());

		pause.Draw(rs);

		audio.Draw(rs);
		
		/*シーンチェンジ一番前*/
		cs.Draw(door.GH_, door.color_, shadow.GetGoalPos(), shadow.GetGoalSize(), pause.isSelect_);

		if (keys[DIK_H] && !preKeys[DIK_H]) {
			if (cs.isEndChange_) {
				cs.isEndChange_ = false;

			} else {
				cs.isEndChange_ = true;
			}
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

void DrawTutorial(const Resources& rs) {

	if (Scene::sceneNum_ == GAME) {

	for (int i = 0; i < 5; i++) {//下地

		Novice::DrawBox(
			-67 - i * 2,-10 - i * 2,
			128 + i * 4,
			64 + i * 4,
			0.0f,
			0x00000015,
			kFillModeSolid
		);

		Novice::DrawBox(
			int(Global::windowSize_.x - 90 - i * 2),
			int(-10 - i * 2),
			128 + i * 4,
			64 + i * 4,
			0.0f,
			0x00000015,
			kFillModeSolid
		);
	}

		//esc
		Novice::DrawSpriteRect(
			-18, -5,
			128, 0,
			128, 64,
			rs.tutorial_[1],
			(128.0f / 256.0f) / 1.2f,
			(64.0f / 128.0f) / 1.2f,
			0.0f,
			0xffffffff
		);


		//reset
		Novice::DrawSpriteRect(
			Global::windowSize_.x - 110, 0,
			0, 64,
			128, 64,
			rs.tutorial_[1],
			(128.0f / 256.0f),
			(64.0f / 128.0f),
			0.0f,
			0xffffffff
		);


	}
}