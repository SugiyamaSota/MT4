#pragma once
#include"../struct/Struct.h"

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);