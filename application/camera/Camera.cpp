#include "Camera.h"
#include"imgui.h"
#include<assert.h>
#include<cmath>
#include"../matrix/Matrix.h"

Matrix4x4 Camera::MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}

Matrix4x4 Camera::MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	return result;
}

Vector3 Camera::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result = {};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Matrix4x4 Camera::MakeRotateXMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	return result;
}

Matrix4x4 Camera::MakeRotateYMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[0][0] = std::cos(radian);
	result.m[0][2] = -std::sin(radian);
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);
	return result;
}

Matrix4x4 Camera::MakeRotateZMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	return result;
}

Matrix4x4 Camera::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = MakeIdentity4x4();
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	result = Multiply(Multiply(scaleMatrix, rotateXYZMatrix), translateMatrix);
	return result;
}

Matrix4x4 Camera::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result = {};
	result.m[0][0] = (1 / aspectRatio) * (1 / std::tan(fovY / 2));
	result.m[1][1] = 1 / std::tan(fovY / 2);
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	return result;
}

Matrix4x4 Camera::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	return result;
}

Matrix4x4 Camera::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result = MakeIdentity4x4();
	result.m[0][0] = width / 2;
	result.m[1][1] = -height / 2;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + width / 2;
	result.m[3][1] = top + height / 2;
	result.m[3][2] = minDepth;
	return result;
}

Vector3 Camera::Conversion(const Vector3& v) {
	Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix_, projectionMatrix_); 
	Vector3 ndc = Transform(v, viewProjectionMatrix);

	Vector3 screen = Transform(ndc, viewportMatrix_);

	return screen;
}

void Camera::Initialize(const int kWindowWidth, const int kWindowHeight) {
	kWindowWidth_ = kWindowWidth;
	kWindowHeight_ = kWindowHeight;

	cameraTranslate_ = { 0.0f,1.9f,-6.49f };
	cameraRotate_ = { 0.26f,0.0f,0.0f };

	cameraMatrix_ = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraTranslate_);
	viewMatrix_ = Inverse(cameraMatrix_);
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth_) / float(kWindowHeight_), 0.1f, 100.0f);
	viewportMatrix_ = MakeViewportMatrix(0, 0, float(kWindowWidth_), float(kWindowHeight_), 0.0f, 1.0f);
}

void Camera::Update() {
	ImGui::Begin("Camera");
	ImGui::DragFloat3("CameraTranslate", &cameraTranslate_.x, 0.01f);
	ImGui::DragFloat3("CameraRotate", &cameraRotate_.x, 0.01f);
	ImGui::End();
	cameraMatrix_ = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraTranslate_);
	viewMatrix_ = Inverse(cameraMatrix_);
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth_) / float(kWindowHeight_), 0.1f, 100.0f);
	viewportMatrix_ = MakeViewportMatrix(0, 0, float(kWindowWidth_), float(kWindowHeight_), 0.0f, 1.0f);
}

Vector3 Camera::MakeScreenPosition(const Matrix4x4& worldMatrix) {
	Matrix4x4 uniqueViewProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth_) / float(kWindowHeight_), 0.1f, 100.0f);
	Matrix4x4 uniqueWorldViewProjectionMatrix_ = Multiply(worldMatrix, Multiply(viewMatrix_, uniqueViewProjectionMatrix));
	Matrix4x4 uniqueViewportMatrix_ = MakeViewportMatrix(0, 0, float(kWindowWidth_), float(kWindowHeight_), 0.0f, 1.0f);
	Vector3 worldPos = { worldMatrix.m[2][0],worldMatrix.m[2][1], worldMatrix.m[2][2] };
	Vector3 ndc = Transform(worldPos, uniqueWorldViewProjectionMatrix_);
	Vector3 screen = Transform(ndc, uniqueViewportMatrix_);
	return screen;
}
