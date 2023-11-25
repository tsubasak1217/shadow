#include "PlayerShadow.h"
#include "Player.h"
#include "selectDoor.h"
#include"stageClearEffect.h"
#include"stageClear.h"
#include"Pause.h"
#include"Title.h"
#include "ImGuiManager.h"
#include "selectLightParticle.h"


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



	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Resources rs;

	Scene scene;
	ChangeScene cs;

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
		Novice::ScreenPrintf(0, 0, "StageNum=%d", Map::stageNum_);
		SCE.Init();
		map.Update(keys, rs, cs);
		player.Update(keys, map, cs, pause.isPause_);
		light.Update(keys, cs, map, ((3.0f / 4.0f) * float(M_PI)), pause.isPause_);

		shadow.Update(keys, cs, rs, screen, map);
		screen.Update(keys, cs, map, light);

		title.Update(keys, preKeys);
		door.Update(keys, preKeys);
		cs.UpDate(keys, preKeys, door.isChangeScene_, door.CPos_, door.selectNum_, SCE.canSceneChange, shadow.GetGoalPos(), shadow.GetGoalSize(), pause.isSelect_, title.isPush_);
		stageClear.Update(cs.isStartChange_);
		SCE.Update(stageClear.GetFT());
		playerShadow.Update(keys, cs, screen, shadow, player, pause.isPause_);
		pause.Update(cs, keys, preKeys);

		for (int i = 0; i < 120; i++)
		{
			SLParticle[i].Update(door);
		}
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

		map.DrawBG();
		screen.Draw(map, rs, light);
		shadow.Draw(rs);
		playerShadow.Draw(screen);

		light.Draw(map, cs);
		map.Draw(rs);
		player.Draw(rs);


		title.Draw(rs);
		door.Draw(rs);
		stageClear.Draw(playerShadow.GetstarCount(), rs);
		
		
		for (int i = 0; i < 120; i++)
		{
			SLParticle[i].Draw(keys);
		}
		
		SCE.Draw();

		pause.Draw(rs);
		/*シーンチェンジ一番前*/
		cs.Draw(door.GH_, door.color_, shadow.GetGoalPos(), shadow.GetGoalSize(), pause.isSelect_);



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
