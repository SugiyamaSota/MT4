#pragma once

struct Quaternion;

// 積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

// 単位
Quaternion IdentityQuaternion();
// 共役
Quaternion Conjugate(const Quaternion& quaternion);

// ノルム
float Norm(const Quaternion& quaternion);

// 正規化
Quaternion Normalize(const Quaternion& quaternion);

// 逆
Quaternion Inverse(const Quaternion& quaternion);

void  QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label);

