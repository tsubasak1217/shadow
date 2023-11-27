
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

const char kWindowTitle[] = "LC1A_14_クロカワツバサ_";

//======================================================
//					  構造体など
//======================================================



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
		
		cs.UpDate(keys, preKeys, door.isChangeScene_, door.CPos_, door.selectNum_, SCE.canSceneChange, shadow.GetGoalPos(), shadow.GetGoalSize(), pause.isSelect_, title.isPush_);

		map.Update(keys, rs, cs);
		player.Update(keys, cs, map, pause.isPause_);
		light.Update(keys, cs, map, ((3.0f / 4.0f) * float(M_PI)), pause.isPause_);

		screen.Update(keys, cs, map, light);
		shadow.Update(keys, cs, rs, screen, map);

		SCE.Update(stageClear, playerShadow.GetstarCount());
		playerShadow.Update(keys, preKeys, rs, cs, screen, shadow, player, map, light, pause.isPause_);
		for (int i = 0; i < 120; i++) {
			particle[i].Update(emitter, playerShadow, shadow, screen);
		}

		title.Update(keys, preKeys);
		door.Update(keys, preKeys);
		stageClear.Update(cs.isStartChange_, playerShadow.GetstarCount());

		pause.Update(cs, keys, preKeys);

		for (int i = 0; i < 120; i++)
		{
			SLParticle[i].Update(door,light);
		}

		stageClear.Debug(keys, preKeys);

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

		Novice::ScreenPrintf(0, 0, "StageNum=%d", Map::stageNum_);

		map.DrawBG(rs);
		screen.DrawBG(rs);

		shadow.Draw(rs);
		screen.Draw(map, rs, light);
		playerShadow.Draw(screen);

		for (int i = 0; i < 120; i++) {
			particle[i].Draw();

		}

		light.Draw(rs,map,cs);
		map.Draw(rs);
		player.Draw(rs);


		title.Draw(rs);
		door.Draw(rs);
		stageClear.Draw(rs);


		for (int i = 0; i < 120; i++)
		{
			SLParticle[i].Draw(keys);
		}

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

		//デバッグ
		switch (Scene::sceneNum_) {

		case TITLE:
			Novice::ScreenPrintf(20, 20, "Title");
			break;
		case SELECT:
			Novice::ScreenPrintf(20, 20, "Select");
			break;
		case GAME:
			Novice::ScreenPrintf(20, Global::windowSize_.y - 40, "Game");
			Novice::ScreenPrintf(20, Global::windowSize_.y - 20, "stage %d", map.stageNum_ + 1);
			break;
		case CLEAR:
			Novice::ScreenPrintf(20, 20, "Clear");
			break;
		default:
			break;
		}


		//ImGui::Begin("window");
		//ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		//if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			//break;
		//}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
