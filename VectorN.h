#pragma once

template<typename T>
struct Vector2 final {
	T x = 0;
	T y = 0;

	Vector2 operator+(Vector2 obj) {
		Vector2 result;
		result.x = x + obj.x;
		result.y = y + obj.y;

		return result;
	}

	Vector2 operator+(float obj) {
		Vector2 result;
		result.x = x + obj;
		result.y = y + obj;

		return result;
	}

	Vector2 operator-(Vector2 obj) {
		Vector2 result;
		result.x = x - obj.x;
		result.y = y - obj.y;

		return result;
	}

	Vector2 operator*(Vector2 obj) {
		Vector2 result;
		result.x = x * obj.x;
		result.y = y * obj.y;

		return result;
	}

	Vector2 operator*(float obj) {
		Vector2 result;
		result.x = x * obj;
		result.y = y * obj;

		return result;
	}

	Vector2 operator/(Vector2 obj) {
		Vector2 result;
		result.x = x / obj.x;
		result.y = y / obj.y;

		return result;
	}

	bool operator==(Vector2 other){
		return (x == other.x && y == other.y);
	}
};
using Vec2 = Vector2<float>;

template<typename T>
struct Vector3 final {
	T x = 0;
	T y = 0;
	T z = 0;

	Vector3 operator+(Vector3 obj) {
		Vector3 result;
		result.x = x + obj.x;
		result.y = y + obj.y;
		result.z = z + obj.z;

		return result;
	}

	Vector3 operator-(Vector3 obj) {
		Vector3 result;
		result.x = x - obj.x;
		result.y = y - obj.y;
		result.z = z - obj.z;

		return result;
	}

	Vector3 operator*(Vector3 obj) {
		Vector3 result;
		result.x = x * obj.x;
		result.y = y * obj.y;
		result.z = z * obj.z;

		return result;
	}
};
using Vec3 = Vector3<float>;

template<typename T>
struct Vector4 final {
	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;

	Vector4 operator+(Vector4 obj) {
		Vector4 result;
		result.x = x + obj.x;
		result.y = y + obj.y;
		result.z = z + obj.z;
		result.w = w + obj.w;

		return result;
	}

	Vector4 operator-(Vector4 obj) {
		Vector4 result;
		result.x = x - obj.x;
		result.y = y - obj.y;
		result.z = z - obj.z;
		result.w = w - obj.w;

		return result;
	}

	Vector4 operator*(Vector4 obj) {
		Vector4 result;
		result.x = x * obj.x;
		result.y = y * obj.y;
		result.z = z * obj.z;
		result.w = w * obj.w;

		return result;
	}
};
using Vec4 = Vector4<float>;