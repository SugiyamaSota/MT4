#pragma once
#include<cmath>
#include<array>

//4x4行列
struct Matrix4x4 {
  
    // 行列の定義
    std::array<std::array<float, 4>, 4> m;

    // デフォルトコンストラクタ
    Matrix4x4() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }

    // 値を指定するコンストラクタ
    Matrix4x4(float _m00, float _m01, float _m02, float _m03,
        float _m10, float _m11, float _m12, float _m13,
        float _m20, float _m21, float _m22, float _m23,
        float _m30, float _m31, float _m32, float _m33) {
        m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
        m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
        m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
        m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
    }

    // 加算
    Matrix4x4 operator+(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = m[i][j] + other.m[i][j];
            }
        }
        return result;
    }

    // 減算
    Matrix4x4 operator-(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = m[i][j] - other.m[i][j];
            }
        }
        return result;
    }

    // 乗算
    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result; // デフォルトで単位行列で初期化されるが、上書きされる
        for (int i = 0; i < 4; ++i) { // resultの行
            for (int j = 0; j < 4; ++j) { // resultの列
                result.m[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k) { // 積和演算
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }

    // スカラー乗算
    Matrix4x4 operator*(float scalar) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = m[i][j] * scalar;
            }
        }
        return result;
    }

    // 等価比較
    bool operator==(const Matrix4x4& other) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (m[i][j] != other.m[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // 非等価比較
    bool operator!=(const Matrix4x4& other) const {
        return !(*this == other);
    }
};



struct Vector2 {
    float x;
    float y;

    // デフォルトコンストラクタ
    Vector2() : x(0.0f), y(0.0f) {}

    // 値を指定するコンストラクタ
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    // 加算
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // 減算
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // スカラー乗算
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // 加算代入
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // 等価比較
    bool operator==(const Vector2& other) const {
        return (x == other.x && y == other.y);
    }

    // 非等価比較
    bool operator!=(const Vector2& other) const {
        return !(*this == other); // == 演算子を利用
    }
};

//三次元ベクトル
struct Vector3 {
    float x;
    float y;
    float z;

    // デフォルトコンストラクタ
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    // 値を指定するコンストラクタ
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // 加算
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // 減算
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // スカラー乗算
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // スカラー除算
    Vector3 operator/(float scalar) const {
        if (scalar == 0.0f) {
            return Vector3();
        }
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // ドット積
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // クロス積
    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    // ベクトルの長さ
    float magnitude() const {
        return std::sqrtf(x * x + y * y + z * z);
    }

    // ベクトルの正規化
    Vector3 normalized() const {
        float mag = magnitude();
        if (mag == 0.0f) {
            return Vector3();
        }
        return *this / mag;
    }

    // 加算代入
    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // 減算代入
    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // スカラー乗算代入
    Vector3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // スカラー除算代入
    Vector3& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // 単項減算
    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    // 等価比較
    bool operator==(const Vector3& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    // 非等価比較
    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }
};

struct Quaternion {
    float x, y, z, w;
};

//球
struct Sphere {
	Vector3 center;
	float radius;
};

//直線
struct Line {
	Vector3 origin;
	Vector3 diff;
};

//半直線
struct Ray {
	Vector3 origin;
	Vector3 diff;
};

//線分
struct Segment {
	Vector3 origin;
	Vector3 diff;
};

//平面
struct Plane {
	Vector3 normal;
	float distance;
};

//三角形
struct Triangle {
	Vector3 vertices[3];
};

//AABB
struct AABB {
	Vector3 min;
	Vector3 max;
};

// ばね
struct Spring {
    Vector3 anchor;
    float natiralLength;
    float stiffness;
    float dampingCoefficient;
};

struct Ball {
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    float mass;
    float radius;
    unsigned int color;
};

struct Bezier {
    Vector3 startPoint;
    Vector3 anchorPoint;
    Vector3 endPoint;
};

struct WorldTransform {
    Vector3 scale;
    Vector3 rotate;
    Vector3 translate;
};

struct Pendulum {
    Vector3 anchor;
    float length;
    float angle;
    float angularVelocity;
    float angularAcceleration;
};

struct ConicalPendulum {
    Vector3 anchor;
    float length;
    float halfApexAngle;
    float angle;
    float angularVelocity;
};

