#pragma once
///// 前方宣言 /////
struct Matrix4x4;

//===計算関数===//
//行列の加法
Matrix4x4 Add(const  Matrix4x4& matrix1, const  Matrix4x4& matrix2);

//行列の減法
Matrix4x4 Subtract(const  Matrix4x4& matrix1, const  Matrix4x4& matrix2);

//行列の積
Matrix4x4 Multiply(const  Matrix4x4& matrix1, const  Matrix4x4& matrix2);

//逆行列
Matrix4x4 Inverse(const Matrix4x4& matrix);

//転置行列
Matrix4x4 Transpose(const Matrix4x4& matrix);

// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// Y軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

//単位行列の作成
Matrix4x4 MakeIdentity4x4();

///// 描画関数 /////
static const int kMatrixRowHeight = 20;
static const int kMatrixColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

