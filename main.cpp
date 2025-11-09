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

	Quaternion q1 = { 2.f,3.f,4.f,1.f };
	Quaternion q2 = { 1.f,3.f,5.f,2.f };
	Quaternion identity = IdentityQuaternion();
	Quaternion conj = Conjugate(q1);
	Quaternion inv = Inverse(q1);
	Quaternion normal = Normalize(q1);
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	float norm = Norm(q1);

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


		int y = 50;
		int lineHeight = 40; // 1行の表示に十分な高さ

		

		// --- 結果の出力 ---

		// Identity
		QuaternionScreenPrintf(0, y, identity, "Identity:");
		y += lineHeight;

		// Conjugate
		QuaternionScreenPrintf(0, y, conj, "Conjugate(Q1):");
		y += lineHeight;

		// Inverse
		QuaternionScreenPrintf(0, y, inv, "Inverse(Q1):");
		y += lineHeight;

		// Normalize
		QuaternionScreenPrintf(0, y, normal, "Normalize(Q1):");
		y += lineHeight;

		// Norm (ノルムの二乗はfloatなので通常のScreenPrintfを使用)
		Novice::ScreenPrintf(0, y, "Norm(Q1): %.02f", norm);
		y += lineHeight;

		// Multiply (q1 * q2)
		QuaternionScreenPrintf(0, y, mul1, "Multiply(Q1, Q2):");
		y += lineHeight;

		// Multiply (q2 * q1) - 非可換性を確認
		QuaternionScreenPrintf(0, y, mul2, "Multiply(Q2, Q1):");
		y += lineHeight;

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