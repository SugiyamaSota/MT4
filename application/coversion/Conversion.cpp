#include "Conversion.h"

#include<math.h>

#include"../vector/Vector.h"
#include"../matrix/Matrix.h"

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
