#include <Novice.h>
#include "MyFunc.h"
#include "Screen.h"

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
	Novice::Initialize(kWindowTitle, global.windowSize_.x,global.windowSize_.y);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Resources rs;
	Map map(global);
	Player player(map);
	Light light(global,map);
	Screen screen(map,light);

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

		map.Update(keys,global);
		player.Update(keys);
		light.Update(keys,map,((3.0f/4.0f) * float(M_PI)),global);
		screen.Update(map, light);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		screen.Draw(map,rs,light);
		light.Draw(map);
		map.Draw(rs);
		player.Draw(rs,map);

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
