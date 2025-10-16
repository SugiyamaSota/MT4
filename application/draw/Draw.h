#pragma once
#include<cstdint>
#include"../struct/Struct.h"
#include"../camera/Camera.h"

/// <summary>
/// グリッドの描画
/// </summary>
/// <param name="camera">カメラクラス</param>
void DrawGrid(Camera* camera);

void DrawSegment(const Segment& segment, Camera* camera, uint32_t color);

/// <summary>
/// 球体の描画
/// </summary>
/// <param name="sphere">球体構造体</param>
/// <param name="camera">カメラクラス</param>
/// <param name="color">色</param>
void DrawSphere(const Sphere& sphere, Camera* camera, uint32_t color);

/// <summary>
/// 平面の描画
/// </summary>
/// <param name="plane">平面構造体</param>
/// <param name="camera">カメラクラス</param>
/// <param name="color">色</param>
void DrawPlane(const Plane& plane, Camera* camera, uint32_t color);

/// <summary>
/// 三角形の描画
/// </summary>
/// <param name="triangle">三角形構造体</param>
/// <param name="camera">カメラクラス</param>
/// <param name="color">色</param>
void DrawTriangle(const Triangle& triangle, Camera* camera, uint32_t color);

/// <summary>
/// AABBの描画
/// </summary>
/// <param name="aabb">AABB構造体</param>
/// <param name="camera">カメラクラス</param>
/// <param name="color">色</param>
void DrawAABB(const AABB& aabb, Camera* camera, uint32_t color);


void DrawBezier(const Bezier& bezier,Camera* camera, uint32_t color);