#include "Screen.h"
#include "Player.h"
#include "ImGuiManager.h"

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
	//ChangeScene cs;

	Map map(rs);
	Player player(map);
	Light light(map);
	Screen screen(map, light);

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

		map.Update(keys, rs);
		player.Update(keys);
		light.Update(keys, map, ((3.0f / 4.0f) * float(M_PI)));
		screen.Update(map, light);

		if (keys[DIK_1]) {
			Scene::sceneNum_ = TITLE;
		} else if (keys[DIK_2]) {
			Scene::sceneNum_ = SELECT;
		} else if (keys[DIK_3]) {
			Scene::sceneNum_ = GAME;
		} else if (keys[DIK_4]) {
			Scene::sceneNum_ = CLEAR;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		screen.Draw(map, rs, light);
		light.Draw(map);
		map.Draw(rs);
		player.Draw(rs, map);

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
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
