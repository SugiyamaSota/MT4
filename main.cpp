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

	//
	Vector3 from0 = Normalize(Vector3{ 1.f,0.7f,0.5f });
	Vector3 to0 = -from0;
	Vector3 from1 = Normalize(Vector3{ -0.6f,0.9f,0.2f });
	Vector3 to1 = Normalize(Vector3{ 0.4f,0.7f,-0.5f });

	//float deltaTime = 1.0f / 60.0f;

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

		Matrix4x4 rotateMatrix0 = DirectionToDirection(Normalize(Vector3{ 1.f,0.f,0.f }), Normalize(Vector3{ -1.f,0.f,0.f }));

		Matrix4x4 rotateMatrix1 = DirectionToDirection(from0, to0);
		Matrix4x4 rotateMatrix2 = DirectionToDirection(from1, to1);

		MatrixScreenPrintf(0, 0, rotateMatrix0, "rotateMatrix0");
		MatrixScreenPrintf(0, kRowHeight * 5, rotateMatrix1, "rotateMatrix1");
		MatrixScreenPrintf(0, kRowHeight * 10, rotateMatrix2, "rotateMatrix2");

		// カメラ
		camera->Update();

		///
		/// ↑更新処理ここまで
		///

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