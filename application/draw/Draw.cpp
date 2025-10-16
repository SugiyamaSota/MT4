#include"Draw.h"
#include<Novice.h>
#include"../camera/Camera.h"
#include"../struct/Struct.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"../vector/Vector.h"

void DrawGrid(Camera* camera) {
	const float kGridHalfWidth = 2.0f;
	const int kSubDivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubDivision);

	for (int xIndex = 0; xIndex <= kSubDivision; ++xIndex) {
		Vector3 startPos = { (xIndex - 5) * kGridEvery,0.0f,-kGridHalfWidth };
		Vector3 endPos = { (xIndex - 5) * kGridEvery,0.0f,kGridHalfWidth };
		;
		Vector3 screenStartPos = camera->Conversion(startPos);
		Vector3 screenEndPos = camera->Conversion(endPos);

		int color;
		if (xIndex - 5 == 0) {
			color = BLACK;
		} else {
			color = 0xAAAAAAFF;
		}

		Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), color);
	}

	for (int zIndex = 0; zIndex <= kSubDivision; ++zIndex) {
		Vector3 startPos = { -kGridHalfWidth,0.0f,(zIndex - 5) * kGridEvery };
		Vector3 endPos = { kGridHalfWidth,0.0f,(zIndex - 5) * kGridEvery };

		Vector3 screenStartPos = camera->Conversion(startPos);
		Vector3 screenEndPos = camera->Conversion(endPos);

		int color;
		if (zIndex - 5 == 0) {
			color = BLACK;
		} else {
			color = 0xAAAAAAFF;
		}

		Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), color);
	}
}

void DrawSegment(const Segment& segment, Camera* camera, uint32_t color) {
	Vector3 startPos = camera->Conversion(segment.origin);
	Vector3 endPos = camera->Conversion(segment.origin + segment.diff);

	Novice::DrawLine(int(startPos.x), int(startPos.y), int(endPos.x), int(endPos.y), color);
}

void DrawSphere(const Sphere& sphere, Camera* camera, uint32_t color) {
	const int kSubdivision = 10;
	const float kLonEvery = float(2 * M_PI / kSubdivision);
	const float kLatEvery = float(M_PI / kSubdivision);

	const int vertexCount = (kSubdivision + 1) * (kSubdivision + 1);
	Vector3 vertices[vertexCount] = {};
	int vertexIndex = 0;

	for (int latIndex = 0; latIndex <= kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;
		for (int lonIndex = 0; lonIndex <= kSubdivision; ++lonIndex) {
			float lon = kLonEvery * lonIndex;

			Vector3 pos = {};
			pos.x = sphere.radius * cosf(lat) * cosf(lon) + sphere.center.x;
			pos.y = sphere.radius * sinf(lat) + sphere.center.y;
			pos.z = sphere.radius * cosf(lat) * sinf(lon) + sphere.center.z;
			vertices[vertexIndex++] = pos;
		}
	}

	for (int latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		for (int lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			int index = latIndex * (kSubdivision + 1) + lonIndex;
			int nextLonIndex = (lonIndex + 1) % (kSubdivision + 1);
			int nextLatIndex;
			if (latIndex + 1 < kSubdivision) {
				nextLatIndex = latIndex + 1;
			} else {
				nextLatIndex = kSubdivision;
			}

			Vector3 v0_world = vertices[index];
			Vector3 v1_world = vertices[latIndex * (kSubdivision + 1) + nextLonIndex];
			Vector3 v2_world = vertices[nextLatIndex * (kSubdivision + 1) + lonIndex];
			Vector3 v3_world = vertices[nextLatIndex * (kSubdivision + 1) + nextLonIndex];

			Vector3 v0_screen = camera->Conversion(v0_world);
			Vector3 v1_screen = camera->Conversion(v1_world);
			Vector3 v2_screen = camera->Conversion(v2_world);
			Vector3 v3_screen = camera->Conversion(v3_world);

			Novice::DrawLine(int(v0_screen.x), int(v0_screen.y), int(v1_screen.x), int(v1_screen.y), color);
			Novice::DrawLine(int(v0_screen.x), int(v0_screen.y), int(v2_screen.x), int(v2_screen.y), color);
			Novice::DrawLine(int(v1_screen.x), int(v1_screen.y), int(v3_screen.x), int(v3_screen.y), color);
			Novice::DrawLine(int(v2_screen.x), int(v2_screen.y), int(v3_screen.x), int(v3_screen.y), color);
		}
	}
}

void DrawPlane(const Plane& plane, Camera* camera, uint32_t color) {
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicuar(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = camera->Conversion(point);
	}
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), color);
}

void DrawTriangle(const Triangle& triangle, Camera* camera, uint32_t color) {
	Vector3 screenVertices[3];
	for (int i = 0; i < 3; i++) {
		screenVertices[i] = camera->Conversion(triangle.vertices[i]);
	}

	Novice::DrawTriangle(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), int(screenVertices[2].x), int(screenVertices[2].y),
		color, kFillModeWireFrame);
}

void DrawAABB(const AABB& aabb, Camera* camera, uint32_t color) {
	// AABBの8つの頂点を計算
	Vector3 vertices[8];
	vertices[0] = { aabb.min.x, aabb.min.y, aabb.min.z }; // P0 (min.x, min.y, min.z)
	vertices[1] = { aabb.max.x, aabb.min.y, aabb.min.z }; // P1 (max.x, min.y, min.z)
	vertices[2] = { aabb.min.x, aabb.max.y, aabb.min.z }; // P2 (min.x, max.y, min.z)
	vertices[3] = { aabb.max.x, aabb.max.y, aabb.min.z }; // P3 (max.x, max.y, min.z)

	vertices[4] = { aabb.min.x, aabb.min.y, aabb.max.z }; // P4 (min.x, min.y, max.z)
	vertices[5] = { aabb.max.x, aabb.min.y, aabb.max.z }; // P5 (max.x, min.y, max.z)
	vertices[6] = { aabb.min.x, aabb.max.y, aabb.max.z }; // P6 (min.x, max.y, max.z)
	vertices[7] = { aabb.max.x, aabb.max.y, aabb.max.z }; // P7 (max.x, max.y, max.z)

	// 各頂点をスクリーン座標に変換
	Vector3 screenVertices[8];
	for (int i = 0; i < 8; ++i) {
		screenVertices[i] = camera->Conversion(vertices[i]);
	}

	// AABBの12本の辺を描画
	// 各辺のインデックスペアを定義
	const int indices[12][2] = {
		{0, 1}, {0, 2}, {0, 4}, // min.z 面の3辺 (P0から伸びる辺)
		{1, 3}, {1, 5},         // P1から伸びる辺
		{2, 3}, {2, 6},         // P2から伸びる辺
		{4, 5}, {4, 6},         // max.z 面の3辺 (P4から伸びる辺)
		{3, 7},                 // P3から伸びる辺
		{5, 7},                 // P5から伸びる辺
		{6, 7}                  // P6から伸びる辺
	};

	for (int i = 0; i < 12; ++i) {
		int idx1 = indices[i][0];
		int idx2 = indices[i][1];
		Novice::DrawLine(
			static_cast<int>(screenVertices[idx1].x), static_cast<int>(screenVertices[idx1].y),
			static_cast<int>(screenVertices[idx2].x), static_cast<int>(screenVertices[idx2].y),
			color
		);
	}
}

void DrawBezier(const Bezier& bezier, Camera* camera, uint32_t color) {

	const int SEGMENTS = 32; // 曲線をどれくらいの数の線分で近似するか

	// 最初の点もカメラ変換してスクリーン座標にする
	Vector3 previousScreenPoint = camera->Conversion(bezier.startPoint);

	for (int i = 1; i <= SEGMENTS; ++i) {
		float t = static_cast<float>(i) / SEGMENTS;

		// ステップ1: 制御点0と制御点1の間をtで補間した点 A を計算
		Vector3 point_A = Lerp(bezier.startPoint, bezier.anchorPoint, t);

		// ステップ2: 制御点1と制御点2の間をtで補間した点 B を計算
		Vector3 point_B = Lerp(bezier.anchorPoint, bezier.endPoint, t);

		// ステップ3: 点 A と点 B の間をtで補間した点がベジェ曲線上の点となる
		Vector3 worldPoint = Lerp(point_A, point_B, t);

		// ベジェ曲線上の点をカメラを使ってスクリーン座標に変換
		Vector3 currentScreenPoint = camera->Conversion(worldPoint);

		Novice::DrawLine(int(previousScreenPoint.x), int(previousScreenPoint.y), int(currentScreenPoint.x), int(currentScreenPoint.y), color);

		// 次の線分のために現在の点を記憶
		previousScreenPoint = currentScreenPoint;
	}
}