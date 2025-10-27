#include "Conversion.h"

#include<math.h>

#include"../vector/Vector.h"
#include"../matrix/Matrix.h"

using namespace std;

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle) {
	float a = (1 - std::cos(angle));

	Vector3 n = Normalize(axis);

	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = n.x * n.x * a + std::cos(angle);
	result.m[0][1] = n.x * n.y * a + n.z * std::sin(angle);
	result.m[0][2] = n.x * n.z * a - n.y * std::sin(angle);
	result.m[0][3] = 0;
	result.m[1][0] = n.x * n.y * a - n.z * std::sin(angle);
	result.m[1][1] = n.y * n.y * a + std::cos(angle);
	result.m[1][2] = n.y * n.z * a + n.x * std::sin(angle);
	result.m[1][3] = 0;
	result.m[2][0] = n.x * n.z * a + n.y * std::sin(angle);
	result.m[2][1] = n.y * n.z * a - n.x * std::sin(angle);
	result.m[2][2] = n.z * n.z * a + std::cos(angle);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {
    // 1. 入力ベクトルの正規化
    Vector3 norm_from = Normalize(from);
    Vector3 norm_to = Normalize(to);

    // 2. cosθの計算とクランプ
    float cos_theta = Dot(norm_from, norm_to);

    // 浮動小数点誤差対策として[-1, 1]の範囲にクランプ
    cos_theta = std::fmaxf(-1.0f, std::fminf(1.0f, cos_theta));

    // 角度θの計算（正しい方法：acos）
    float theta = std::acos(cos_theta);

    // 3. 許容誤差の定義
    const float kEpsilon = 1.0e-5f;

    // -----------------------------------------------------------
    // 4. 特異点処理（from == to、または from == -to のケース）
    // -----------------------------------------------------------

    // ケース A: from == to (回転不要)
    if (cos_theta > 1.0f - kEpsilon) { // cosθ ≈ 1
        return MakeIdentity4x4();
    }

    // ケース B: from == -to (180度回転の特異点)
    if (cos_theta < -1.0f + kEpsilon) { // cosθ ≈ -1 (θ = π)

        // 180度回転の軸nを求める
        // fromと直交する適当なベクトルを見つける（最も成分が小さい軸と外積を取る）
        Vector3 axis;
        if (std::abs(norm_from.x) < std::abs(norm_from.y) && std::abs(norm_from.x) < std::abs(norm_from.z)) {
            // X成分が最小なら、X軸との外積
            axis = Cross(norm_from, Vector3{ 1.0f, 0.0f, 0.0f });
        } else {
            // YまたはZ成分が最小なら、Y軸との外積
            axis = Cross(norm_from, Vector3{ 0.0f, 1.0f, 0.0f });
        }

        // nは正規化された回転軸
        Vector3 n = Normalize(axis);

        // θをπに固定し、cosθ=-1, sinθ=0 を使用して回転行列を構築する
        // 180度回転行列を生成する専用の関数があればそれを使うのがベスト。
        // ここではロドリゲスの公式にそのまま代入し、特異点回避後の値を使う
        float c = -1.0f; // cos(π)
        float s = 0.0f;  // sin(π)
        float t = 1.0f - c; // 2.0f

        // ロドリゲスの回転公式（n, c, s, t=1-c を使用）
        Matrix4x4 result = MakeIdentity4x4();
        result.m[0][0] = n.x * n.x * t + c;
        result.m[0][1] = n.x * n.y * t - n.z * s; // n.z * s は0
        result.m[0][2] = n.x * n.z * t + n.y * s; // n.y * s は0
        result.m[1][0] = n.x * n.y * t + n.z * s; // n.z * s は0
        result.m[1][1] = n.y * n.y * t + c;
        result.m[1][2] = n.y * n.z * t - n.x * s; // n.x * s は0
        result.m[2][0] = n.x * n.z * t - n.y * s; // n.y * s は0
        result.m[2][1] = n.y * n.z * t + n.x * s; // n.x * s は0
        result.m[2][2] = n.z * n.z * t + c;

        return result;
    }


    // -----------------------------------------------------------
    // 5. 通常の回転（0 < θ < π）
    // -----------------------------------------------------------

    // 回転軸 n の計算 (Crossの結果が非ゼロであることを特異点処理で保証済み)
    Vector3 n = Normalize(Cross(norm_from, norm_to));

    // ロドリゲスの公式に必要な値
    float c = cos_theta; // cos(θ)
    float s = std::sin(theta); // sin(θ)
    float temporaryValue = 1.0f - c; // 1 - cos(θ)

    // ロドリゲスの回転公式の適用
    Matrix4x4 result = MakeIdentity4x4();
    result.m[0][0] = n.x * n.x * temporaryValue + c;
    result.m[0][1] = n.x * n.y * temporaryValue - n.z * s; // 符号が逆
    result.m[0][2] = n.x * n.z * temporaryValue + n.y * s;

    result.m[1][0] = n.x * n.y * temporaryValue + n.z * s; // 符号が逆
    result.m[1][1] = n.y * n.y * temporaryValue + c;
    result.m[1][2] = n.y * n.z * temporaryValue - n.x * s;

    result.m[2][0] = n.x * n.z * temporaryValue - n.y * s;
    result.m[2][1] = n.y * n.z * temporaryValue + n.x * s;
    result.m[2][2] = n.z * n.z * temporaryValue + c;

    // 最後の行/列はアイデンティティのままとする
    result.m[0][3] = result.m[1][3] = result.m[2][3] = 0;
    result.m[3][0] = result.m[3][1] = result.m[3][2] = 0;
    result.m[3][3] = 1;

    return result;
}