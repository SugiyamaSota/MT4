#include "Quaternion.h"
#include<Novice.h>
#include"../struct/Struct.h"

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

