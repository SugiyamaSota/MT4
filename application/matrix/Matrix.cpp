#include"Matrix.h"
#include<Novice.h>
#include<math.h>
#include"../struct/Struct.h"

Matrix4x4 Add(const  Matrix4x4& matrix1, const  Matrix4x4& matrix2) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 Subtract(const  Matrix4x4& matrix1, const  Matrix4x4& matrix2) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 Multiply(const  Matrix4x4& matrix1, const  Matrix4x4& matrix2) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix1.m[i][0] * matrix2.m[0][j] +
				matrix1.m[i][1] * matrix2.m[1][j] +
				matrix1.m[i][2] * matrix2.m[2][j] +
				matrix1.m[i][3] * matrix2.m[3][j];
		}
	}
	return result;
}

Matrix4x4 Inverse(const Matrix4x4& matrix) {
	Matrix4x4 result = {};
	float A = {};
	A = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] + matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2]
		- matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] - matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]
		- matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] - matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1] - matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]
		+ matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] + matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]
		+ matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] + matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] + matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]
		- matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] - matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] - matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2]
		- matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] - matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] - matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]
		+ matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] + matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] + matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0];

	result.m[0][0] = (+(matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) + (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2])
		- (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) - (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2])) / A;
	result.m[0][1] = (-(matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1]) - (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2])
		+ (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1]) + (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2])) / A;
	result.m[0][2] = (+(matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1]) + (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2])
		- (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1]) - (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2])) / A;
	result.m[0][3] = (-(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1]) - (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2])
		+ (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1]) + (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2])) / A;

	result.m[1][0] = (-(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2])
		+ (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2])) / A;
	result.m[1][1] = (+(matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2])
		- (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2])) / A;
	result.m[1][2] = (-(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2])
		+ (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2])) / A;
	result.m[1][3] = (+(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2])
		- (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2])) / A;

	result.m[2][0] = (+(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1])
		- (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1])) / A;
	result.m[2][1] = (-(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1])
		+ (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1])) / A;
	result.m[2][2] = (+(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1])
		- (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0]) - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1])) / A;
	result.m[2][3] = (-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0]) - (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1])
		+ (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3]) + (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1])) / A;

	result.m[3][0] = (-(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]) - (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1])
		+ (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]) + (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1])) / A;
	result.m[3][1] = (+(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2]) + (matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1])
		- (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1])) / A;
	result.m[3][2] = (-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2]) - (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1])
		+ (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2]) + (matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1])) / A;
	result.m[3][3] = (+(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) + (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1])
		- (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) - (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1])) / A;

	return result;
}

Matrix4x4 Transpose(const Matrix4x4& matrix) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix.m[j][i];
		}
	}
	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[0][0] = std::cos(radian);
	result.m[0][2] = -std::sin(radian);
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);
	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	return result;
}

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		result.m[i][i] = 1.0f;
	}
	return result;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kMatrixColumnWidth, y + (row + 1) * kMatrixRowHeight, "%6.03f", matrix.m[row][column]);
		}
	}
}
