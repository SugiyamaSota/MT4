#include "Collision.h"
#include"../struct/Struct.h"
#include"../vector/Vector.h"
#include<cmath>
#include<algorithm>

bool IsCollision(const Sphere& s1, const Sphere& s2) {
	float distance = Length(Subtract(s1.center, s2.center));
	if (distance <= s1.radius + s2.radius) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Sphere& s, const Plane& p) {
	float distance = Dot(s.center, p.normal) - p.distance;
	distance = fabs(distance);
	if (distance <= s.radius) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Segment& segment, const Plane& plane) {
	float dot = Dot(plane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (t >= 0.0f && t <= 1.0f) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Triangle& triangle, const Segment& segment) {
	Plane trianglePlane;

	Vector3 v1 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 v2 = Subtract(triangle.vertices[2], triangle.vertices[0]);

	trianglePlane.normal = Normalize(Cross(v1, v2));
	trianglePlane.distance = Dot(trianglePlane.normal, triangle.vertices[0]);

	float dot = Dot(trianglePlane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (trianglePlane.distance - Dot(segment.origin, trianglePlane.normal)) / dot;

	if (t < 0.0f && t > 1.0f) {
		return false;
	}

	Vector3 p = Add(segment.origin, Multiply(t, segment.diff));

	Vector3 v[3];

	v[0] = Subtract(triangle.vertices[0], triangle.vertices[1]);
	v[1] = Subtract(triangle.vertices[1], triangle.vertices[2]);
	v[2] = Subtract(triangle.vertices[2], triangle.vertices[0]);


	Vector3 vp[3];
	vp[0] = Subtract(triangle.vertices[0], p);
	vp[1] = Subtract(triangle.vertices[1], p);
	vp[2] = Subtract(triangle.vertices[2], p);

	Vector3 cross[3];
	for (int i = 0; i < 3; i++) {
		cross[i] = Cross(v[i], vp[i]);
	}

	if (Dot(cross[0], trianglePlane.normal) >= 0.0f && Dot(cross[1], trianglePlane.normal) >= 0.0f && Dot(cross[2], trianglePlane.normal) >= 0.0f) {
		return true;
	} else {
		return false;
	}

}

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const AABB& aabb, const Sphere& s) {
	Vector3 closestPoint{ std::clamp(s.center.x, aabb.min.x, aabb.max.x),
		std::clamp(s.center.y, aabb.min.y, aabb.max.y),
		std::clamp(s.center.z, aabb.min.z, aabb.max.z),
	};
	float distance = Length(Subtract(closestPoint, s.center));
	if (distance <= s.radius) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const AABB& aabb, const Segment& segment) {
	Vector3 p1 = segment.origin;
	
	Vector3 p2 = Add(segment.origin, segment.diff);

	float x_min_seg = std::min(p1.x, p2.x);
	float x_max_seg = std::max(p1.x, p2.x);
	float y_min_seg = std::min(p1.y, p2.y);
	float y_max_seg = std::max(p1.y, p2.y);
	float z_min_seg = std::min(p1.z, p2.z);
	float z_max_seg = std::max(p1.z, p2.z);

	if (x_max_seg < aabb.min.x || x_min_seg > aabb.max.x) return false;
	if (y_max_seg < aabb.min.y || y_min_seg > aabb.max.y) return false;
	if (z_max_seg < aabb.min.z || z_min_seg > aabb.max.z) return false;

	Vector3 dir = segment.diff;

	if (dir.x == 0 && dir.y == 0 && dir.z == 0) {
		return (p1.x >= aabb.min.x && p1.x <= aabb.max.x &&
			p1.y >= aabb.min.y && p1.y <= aabb.max.y &&
			p1.z >= aabb.min.z && p1.z <= aabb.max.z);
	}

	float t_enter = 0.0f;
	float t_exit = 1.0f;

	if (dir.x != 0) {
		float t1 = (aabb.min.x - p1.x) / dir.x;
		float t2 = (aabb.max.x - p1.x) / dir.x;
		if (t1 > t2) std::swap(t1, t2);
		t_enter = std::max(t_enter, t1);
		t_exit = std::min(t_exit, t2);
	} else {
		if (p1.x < aabb.min.x || p1.x > aabb.max.x) return false;
	}

	if (dir.y != 0) {
		float t1 = (aabb.min.y - p1.y) / dir.y;
		float t2 = (aabb.max.y - p1.y) / dir.y;
		if (t1 > t2) std::swap(t1, t2);
		t_enter = std::max(t_enter, t1);
		t_exit = std::min(t_exit, t2);
	} else {
		if (p1.y < aabb.min.y || p1.y > aabb.max.y) return false; 
	}

	if (dir.z != 0) {
		float t1 = (aabb.min.z - p1.z) / dir.z;
		float t2 = (aabb.max.z - p1.z) / dir.z;
		if (t1 > t2) std::swap(t1, t2);
		t_enter = std::max(t_enter, t1);
		t_exit = std::min(t_exit, t2);
	} else {
		if (p1.z < aabb.min.z || p1.z > aabb.max.z) return false;
	}

	if (t_enter > t_exit || t_exit < 0.0f || t_enter > 1.0f) {
		return false;
	}

	return true;
}