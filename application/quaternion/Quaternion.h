#pragma once

struct Vector3;
struct Quaternion;
struct Matrix4x4;

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

// クオータニオン描画
void  QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label);

Vector3 QuaternionToVector3(const Quaternion& q);

// 任意軸の回転
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

// vectorをクオータニオンで回転
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);