#pragma once

///// 前方宣言 /////
struct Sphere;
struct Plane;
struct Vector3;
struct Segment;
struct Triangle;
struct AABB;

///// 衝突判定 /////
// 球と球
bool IsCollision(const Sphere& s1, const Sphere& s2);

// 球と平面
bool IsCollision(const Sphere& s, const Plane& p);

// 線分と平面
bool IsCollision(const Segment& segment, const Plane& plane);

// 三角形と線分
bool IsCollision(const Triangle& triangle, const Segment& segment);

//AABBとAABB
bool IsCollision(const AABB& aabb1, const AABB& aabb2);

//AABBと球
bool IsCollision(const AABB& aabb, const Sphere& s);

//AABBと線分
bool IsCollision(const AABB& aabb, const Segment& segment);