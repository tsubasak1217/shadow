#pragma once
struct Matrix2x2 final {
	float m[2][2];

	Matrix2x2() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				m[i][j] = 0.0f;
			}
		}
	}
};

struct Matrix3x3 final {
	float m[3][3];

	Matrix3x3() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = 0.0f;
			}
		}
	}
};

struct Matrix4x4 final {
	float m[4][4];

	Matrix4x4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = 0.0f;
			}
		}
	}
};