#include "Quaternion.h"
#include<Novice.h>
#include"../struct/Struct.h"
#include"../vector/Vector.h"
#include"../matrix/Matrix.h"

// 積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) {
    Quaternion result;

    // x成分
    result.x = lhs.w * rhs.x +
        lhs.x * rhs.w +
        lhs.y * rhs.z -
        lhs.z * rhs.y;

    // y成分
    result.y = lhs.w * rhs.y +
        lhs.y * rhs.w +
        lhs.z * rhs.x -
        lhs.x * rhs.z;

    // z成分
    result.z = lhs.w * rhs.z +
        lhs.z * rhs.w +
        lhs.x * rhs.y -
        lhs.y * rhs.x;

    // w成分
    result.w = lhs.w * rhs.w -
        lhs.x * rhs.x -
        lhs.y * rhs.y -
        lhs.z * rhs.z;

    return result;
}

// 単位
Quaternion IdentityQuaternion() {
    return { 0.0f, 0.0f, 0.0f, 1.0f };
}

// 共役
Quaternion Conjugate(const Quaternion& quaternion) {
    Quaternion result;
    result.w = quaternion.w;
    result.x = -quaternion.x;
    result.y = -quaternion.y;
    result.z = -quaternion.z;
    return result;
}

// ノルム
float Norm(const Quaternion& quaternion) {
    return quaternion.w * quaternion.w +
        quaternion.x * quaternion.x +
        quaternion.y * quaternion.y +
        quaternion.z * quaternion.z;
}

// 正規化
Quaternion Normalize(const Quaternion& quaternion) {
    // 長さの二乗を計算
    float norm_squared = Norm(quaternion);

    // 長さ (ノルム) を計算
    float length = std::sqrt(norm_squared);

    // ゼロ除算のチェック（クオータニオンがゼロクオータニオンの場合）
    if (length == 0.0f) {
        // ゼロクオータニオンの場合は単位クオータニオンを返すのが一般的
        return IdentityQuaternion();
    }

    // 各成分を長さで割る
    float inv_length = 1.0f / length; // 逆数

    Quaternion result;
    result.w = quaternion.w * inv_length;
    result.x = quaternion.x * inv_length;
    result.y = quaternion.y * inv_length;
    result.z = quaternion.z * inv_length;

    return result;
}

// 逆
Quaternion Inverse(const Quaternion& quaternion) {
    // ノルム（長さの二乗）を計算
    float norm_squared = Norm(quaternion);

    // ゼロ除算のチェック
    if (norm_squared == 0.0f) {
        // ゼロクオータニオンの逆元は存在しないため、単位クオータニオンを返す
        return IdentityQuaternion();
    }

    // 共役クオータニオンを計算
    Quaternion conjugate = Conjugate(quaternion);

    // 共役をノルムの二乗で割る
    float inv_norm_squared = 1.0f / norm_squared; // ノルムの二乗の逆数

    // 結果を構築
    Quaternion result;
    result.w = conjugate.w * inv_norm_squared;
    result.x = conjugate.x * inv_norm_squared;
    result.y = conjugate.y * inv_norm_squared;
    result.z = conjugate.z * inv_norm_squared;

    return result;
}

static const int kQuaternionColumnWidth = 60;

void  QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label) {
    Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
    Novice::ScreenPrintf(x + kQuaternionColumnWidth, y, "%.02f", quaternion.y);
    Novice::ScreenPrintf(x + kQuaternionColumnWidth * 2, y, "%.02f", quaternion.z);
    Novice::ScreenPrintf(x + kQuaternionColumnWidth * 3, y, "w:%.02f", quaternion.w);
    Novice::ScreenPrintf(x + kQuaternionColumnWidth * 4, y, "%s", label);
}

Vector3 QuaternionToVector3(const Quaternion& q) {
    return Vector3(q.x, q.y, q.z);
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle) {
    // 軸ベクトルの正規化
    Vector3 unit_axis = Normalize(axis);

    // 軸がゼロベクトルの場合、単位クオータニオンを返す
    if (Length(unit_axis) == 0.0f) {
        return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
    }

    // 半角を計算
    float half_angle = angle * 0.5f;

    // cos と sin を計算
    float w = std::cos(half_angle);
    float sin_half_angle = std::sin(half_angle);

    // クオータニオンのベクトル部を計算
    float x = unit_axis.x * sin_half_angle;
    float y = unit_axis.y * sin_half_angle;
    float z = unit_axis.z * sin_half_angle;

    return Quaternion(x, y, z,w);
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) {
    // vectorをクオータニオンに変換
    Quaternion vectorQ = { vector.x,vector.y,vector.z,0.f };

    Quaternion conjugateQ = Conjugate(quaternion);

    // 計算
    Quaternion temp = Multiply(quaternion,vectorQ);
    Quaternion p_prime = Multiply(temp, conjugateQ);

    return QuaternionToVector3(p_prime);
}

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) {
    Matrix4x4 result = MakeIdentity4x4();

    result.m[0][0] = quaternion.w * quaternion.w + quaternion.x * quaternion.x - quaternion.y * quaternion.y - quaternion.z * quaternion.z;
    result.m[0][1] = 2 * (quaternion.x * quaternion.y + quaternion.w * quaternion.z);
    result.m[0][2] = 2 * (quaternion.x * quaternion.z - quaternion.w * quaternion.y);
    result.m[1][0] = 2 * (quaternion.x * quaternion.y - quaternion.w * quaternion.z);
    result.m[1][1] = quaternion.w * quaternion.w - quaternion.x * quaternion.x + quaternion.y * quaternion.y - quaternion.z * quaternion.z;
    result.m[1][2] = 2 * (quaternion.y * quaternion.z + quaternion.w * quaternion.x);
    result.m[2][0] = 2 * (quaternion.x * quaternion.z + quaternion.w * quaternion.y);
    result.m[2][1] = 2 * (quaternion.y * quaternion.z - quaternion.w * quaternion.x);
    result.m[2][2] = quaternion.w * quaternion.w - quaternion.x * quaternion.x - quaternion.y * quaternion.y + quaternion.z * quaternion.z;

    return result;
}

// Slerp
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t) {
    // t は [0, 1] の範囲にクランプ（制限）します。
    // クランプ処理は、使用している環境に合わせて適切な関数（例：std::fmax(0.0f, std::fmin(1.0f, t))）を使用してください。
    // ここでは単純化のために t の値をそのまま使用します。

    Quaternion q_start = q0;
    Quaternion q_end = q1;

    // 2つのクォータニオンの内積を計算
    // q0とq1の間の角度を求めるために使用します
    float dot = q0.w * q1.w + q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;

    // もし内積が負の場合、より短い経路で補間するために
    // q0またはq1の符号を反転させます。（結果は同じ回転を表します）
    if (dot < 0.0f) {
        // q1 のすべての成分の符号を反転
        q_end.w = -q1.w;
        q_end.x = -q1.x;
        q_end.y = -q1.y;
        q_end.z = -q1.z;
        dot = -dot; // 内積も反転
    }

    // 角度が非常に小さい場合（ほぼ同じクォータニオンの場合）、
    // 線形補間（Lerp）にフォールバックして計算誤差を避けます。
    const float kThreshold = 0.9995f;
    if (dot > kThreshold) {
        // 線形補間（Lerp）を行います
        float scale0 = 1.0f - t;
        float scale1 = t;

        Quaternion result;
        result.w = scale0 * q_start.w + scale1 * q_end.w;
        result.x = scale0 * q_start.x + scale1 * q_end.x;
        result.y = scale0 * q_start.y + scale1 * q_end.y;
        result.z = scale0 * q_start.z + scale1 * q_end.z;

        // 結果を正規化して返します（Lerpでは正規化が必要）
        return Normalize(result);
    }

    // 2つのクォータニオン間の角度を計算
    // 内積 (dot) は cos(theta) に等しいです
    float theta = std::acos(dot); // theta は 0 から pi の範囲

    // 補間係数を計算
    float sin_theta = std::sin(theta);
    float scale0 = std::sin((1.0f - t) * theta) / sin_theta;
    float scale1 = std::sin(t * theta) / sin_theta;

    // Slerpの結果を計算
    Quaternion result;
    result.w = scale0 * q_start.w + scale1 * q_end.w;
    result.x = scale0 * q_start.x + scale1 * q_end.x;
    result.y = scale0 * q_start.y + scale1 * q_end.y;
    result.z = scale0 * q_start.z + scale1 * q_end.z;

    return result;
}
