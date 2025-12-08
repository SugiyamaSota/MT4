#include <Novice.h>
#include<imgui.h>
#include"application/struct/Struct.h"
#include"application/HeaderReader.h"
#include <algorithm>

const char kWindowTitle[] = "LC2C_17_スギヤマソウタ_MT4";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

const int kRowHeight = 20;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// カメラ
	Camera* camera = new Camera();
	camera->Initialize(kWindowWidth, kWindowHeight);

	//float deltaTime = 1.0f / 60.0f;

	//
	Quaternion rotation0 = MakeRotateAxisAngleQuaternion(
		Normalize(Vector3{ 0.71f,0.71f,0.f }), 0.3f);
	Quaternion rotation1 = MakeRotateAxisAngleQuaternion(
		Normalize(Vector3{ 0.71f,0.f,0.71f }), 3.141592f);

	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.f);
	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.f);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		// ImGui
		ImGui::Begin("Window");
		if (ImGui::Button("Start")) {

		}
		ImGui::End();

		// カメラ
		camera->Update();

		///
		/// ↑更新処理ここまで
		///

		QuaternionScreenPrintf(0, kRowHeight * 0, interpolate0, " : interporate , 0.f");
		QuaternionScreenPrintf(0, kRowHeight * 1, interpolate1, " : interporate , 0.3f");
		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate2, " : interporate , 0.5f");
		QuaternionScreenPrintf(0, kRowHeight * 3, interpolate3, " : interporate , 0.7f");
		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate4, " : interporate , 1.f");

		///
		/// ↓描画処理ここから
		///

		// グリッド
		DrawGrid(camera);

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