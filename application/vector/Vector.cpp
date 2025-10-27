#include"Vector.h"
#include<math.h>
#include<Novice.h>
#include"../struct/Struct.h"


Vector3 Add(const Vector3& vector1, const Vector3& vector2) {
	Vector3 result = {};
	result.x = vector1.x + vector2.x;
	result.y = vector1.y + vector2.y;
	result.z = vector1.z + vector2.z;
	return result;
}

Vector3 Subtract(const Vector3& vector1, const Vector3& vector2) {
	Vector3 result = {};
	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return result;
}

Vector3 Multiply(float scalar, const Vector3& vector) {
	Vector3 result = {};
	result.x = scalar * vector.x;
	result.y = scalar * vector.y;
	result.z = scalar * vector.z;
	return result;
}

float Dot(const Vector3& vector1, const Vector3& vector2) {
	float result = {};
	result = vector1.x * vector2.x +
		vector1.y * vector2.y +
		vector1.z * vector2.z;
	return result;
}

float Length(const Vector3& vector) {
	float result = {};
	result = vector.x * vector.x +
		vector.y * vector.y +
		vector.z * vector.z;
	result = sqrtf(result);
	return result;
}

Vector3 Normalize(const Vector3& vector) {
	Vector3 result = {};
	float length = {};
	length = vector.x * vector.x +
		vector.y * vector.y +
		vector.z * vector.z;
	length = 1.0f / sqrtf(length);
	result.x = length * vector.x;
	result.y = length * vector.y;
	result.z = length * vector.z;
	return result;
}

Vector3 Cross(const Vector3& vector1, const Vector3& vector2) {
	Vector3 result = {};
	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = vector1.z * vector2.x - vector1.x * vector2.z;
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return result;
}

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};
	result = Multiply(Dot(v1, Normalize(v2)), Normalize(v2));
	return result;
}

Vector3 ClosestPoint(const Vector3& point,  Segment& segment) {
	Vector3 result = {};
	result = Add(segment.origin, Project(Subtract(point, segment.origin), segment.diff));
	return result;
}

Vector3 Perpendicuar(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return{ 0.0f,-vector.z,vector.y };
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result = {};
	result.x = (v1.x * (1.0f - t)) + (v2.x * t);
	result.y = (v1.y * (1.0f - t)) + (v2.y * t);
	result.z = (v1.z * (1.0f - t)) + (v2.z * t);
	return result;
}

void  VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kVectorColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kVectorColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kVectorColumnWidth * 3, y, "%s", label);
}

