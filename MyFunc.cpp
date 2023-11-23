#include "MyFunc.h"

//何もしない関数
void Void() { ; }

//================================================================
//                     ファイル操作の関数
//================================================================
//csvを読み込む関数
std::vector<std::vector<int>>LoadFile(const std::string& csvFilePath) {

	//最終結果を入れる配列
	std::vector<std::vector<int>> intArray;

	//ファイルの依り代、"file"
	std::ifstream file(csvFilePath);

	//ファイルの数値を入れる変数
	std::string line, value;

	// ファイルから読み取った1行をlineに格納 (改行区切り)
	while (std::getline(file, line)) {

		// 一行ごとの最終結果を入れる配列
		std::vector<int> row;

		// 1行ごとの文字列を入れる変数 (カンマ込み)
		std::istringstream issLine(line);

		/*issLineからカンマ区切りでデータを読み込みvalueに格納
		(行の値を1文字ずつに切り分ける)*/
		while (std::getline(issLine, value, ',')) {

			// 切り分けた一文字を char → int型に変換
			int intValue = atoi(value.c_str());

			// 行にint型の値を入れる
			row.push_back(intValue);
		}

		// std::vector<int>型の1行を配列に入れていく
		intArray.push_back(row);
	}

	return intArray;
}


//================================================================
//                       時間の関数
//================================================================
//フレーム数を時計に変換する関数
int FrameToClock(int count, int tranceMode) {

	int result = 0;
	enum TranceMode {
		Sec,
		Min,
		Hour
	};

	switch (tranceMode) {
	case Sec:
		result = count / 60;
		break;

	case Min:
		result = (count / 60) / 60;
		break;

	case Hour:
		result = ((count / 60) / 60) / 60;
		break;

	default:
		break;
	}

	return result;

};

//================================================================
//                      数学的な関数
//================================================================

//長さを求める関数
float CheckLength(Vec2 pos1, Vec2 pos2) {
	float xLength = (pos1.x - pos2.x);
	float yLength = (pos1.y - pos2.y);
	return sqrtf(xLength * xLength + yLength * yLength);
}
float CheckLength(float pos1x, float pos1y, float pos2x, float pos2y) {
	float xLength = pos2x - pos1x;
	float yLength = pos2y - pos1y;
	return sqrtf(xLength * xLength + yLength * yLength);
}

//ノーマライズ関数
Vec2 Normalize(Vec2 pos1, Vec2 pos2) {

	float xLength = (pos1.x - pos2.x);
	float yLength = (pos1.y - pos2.y);
	float length = CheckLength(pos1, pos2);

	if (length != 0) {
		return {
			xLength / length,
			yLength / length,
		};
	} else {
		return { 0,0 };
	}
};

//内積を求める関数(正規化する)
float Dot(Vec2 pos1, Vec2 pos2, Vec2 targetPos) {

	Vec2 lineVector = { pos2.x - pos1.x,pos2.y - pos1.y };
	float lineLength = sqrtf(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
	Vec2 forTarget = { targetPos.x - pos1.x,targetPos.y - pos1.y };

	return ((lineVector.x * forTarget.x) + (lineVector.y * forTarget.y)) / lineLength;
};

//内積を求める関数(正規化しない)
float NoInitDot(Vec2 pos1, Vec2 pos2, Vec2 targetPos) {

	Vec2 lineVector = { pos2.x - pos1.x,pos2.y - pos1.y };
	Vec2 forTarget = { targetPos.x - pos1.x,targetPos.y - pos1.y };

	return ((lineVector.x * forTarget.x) + (lineVector.y * forTarget.y));
};

//外積を求める関数
float Cross(
	float lineStartX, float lineStartY,
	float lineEndX, float lineEndY,
	float targetX, float targetY
) {
	float lineLengthX = lineEndX - lineStartX;
	float lineLengthY = lineEndY - lineStartY;
	float lineLength = sqrtf(lineLengthX * lineLengthX + lineLengthY * lineLengthY);

	float line2TargetX = targetX - lineStartX;
	float line2TargetY = targetY - lineStartY;

	return ((lineLengthX * line2TargetY) - (lineLengthY * line2TargetX)) / lineLength;
}

float Cross(Vec2 pos1, Vec2 pos2, Vec2 targetPos) {
	Vec2 lineVector = { pos2.x - pos1.x,pos2.y - pos1.y };
	float lineLength = sqrtf(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
	Vec2 forTarget = { targetPos.x - pos1.x,targetPos.y - pos1.y };

	return ((lineVector.x * forTarget.y) - (lineVector.y * forTarget.x)) / lineLength;
}

//正規化しないもの
float NoInitCross(Vec2 pos1, Vec2 pos2, Vec2 targetPos) {
	Vec2 lineVector = { pos2.x - pos1.x,pos2.y - pos1.y };
	Vec2 forTarget = { targetPos.x - pos1.x,targetPos.y - pos1.y };

	return (lineVector.x * forTarget.y) - (lineVector.y * forTarget.x);
}


// ベクトルの交点を求める関数
Vec2 CrossPos(Vec2 line1Pos1, Vec2 line1Pos2, Vec2 line2Pos1, Vec2 line2Pos2) {
	float s1 =
		((line2Pos2.x - line2Pos1.x) * (line1Pos1.y - line2Pos1.y) -
			(line2Pos2.y - line2Pos1.y) * (line1Pos1.x - line2Pos1.x)) / 2.0f;

	float s2 =
		((line2Pos2.x - line2Pos1.x) * (line2Pos1.y - line1Pos2.y) -
			(line2Pos2.y - line2Pos1.y) * (line2Pos1.x - line1Pos2.x)) / 2.0f;

	Vec2 crossPos = {
		line1Pos1.x + (line1Pos2.x - line1Pos1.x) * s1 / (s1 + s2),
		line1Pos1.y + (line1Pos2.y - line1Pos1.y) * s1 / (s1 + s2)
	};

	return crossPos;
}

//内積で角度を計算する関数
float CalcAngle(Vec2 pos1, Vec2 pos2, Vec2 pos3) {
	// ベクトルAとBの内積
	float dotProduct = NoInitDot(pos1, pos2, pos3);

	// ベクトルの大きさ
	float magnitudeA = CheckLength(pos1, pos2);
	float magnitudeB = CheckLength(pos1, pos3);

	// 角度を求める
	float angle = dotProduct / (magnitudeA * magnitudeB);

	return angle;
}


// 線を平行移動する関数
Vec2 ShiftLine(Vec2 pos1, Vec2 pos2, float distance) {

	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float length = sqrtf(dx * dx + dy * dy);
	float normalizedX = dx / length;
	float normalizedY = dy / length;

	return{
	normalizedY * distance,
	-normalizedX * distance
	};
}

void ShiftLineCtrl(Vec2 pos1, Vec2 pos2, float distance) {

	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float length = sqrtf(dx * dx + dy * dy);
	float normalizedX = dx / length;
	float normalizedY = dy / length;

	Vec2 pos = {
	normalizedY * distance,
	-normalizedX * distance
	};
}


//ベクトルの垂直ベクトルを求める関数
Vec2 VerticleVec(Vec2 pos1, Vec2 pos2) {
	return { pos2.y - pos1.y,-(pos2.x - pos1.x) };
}


//================================================================
//                        行列関数
//================================================================

// 加算
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}

	return result;
};
Matrix3x3 Add(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	Matrix3x3 result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}

	return result;
};

// 減算
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return result;
};
Matrix3x3 Subtract(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	Matrix3x3 result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return result;
};

//割る
Matrix2x2 Devide(Matrix2x2 matrix, float devideNum) {
	Matrix2x2 result;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix.m[i][j] / devideNum;
		}
	}

	return result;
};

Matrix3x3 Devide(Matrix3x3 matrix, float devideNum) {

	Matrix3x3 result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = matrix.m[i][j] / devideNum;
		}
	}

	return result;
};

// 乗算
Vec2 Multiply(Vec2 vector, Matrix2x2 matrix) {

	return {
		vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0],
		vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1]
	};
};
Vec2 Multiply(Vec2 vector, Matrix3x3 matrix) {
	Vec2 result;
	float w;


	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	assert(w != 0);

	result.x /= w;
	result.y /= w;

	return result;
};
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {

			result.m[i][j] =
				(matrix1.m[i][0] * matrix2.m[0][j]) +
				(matrix1.m[i][1] * matrix2.m[1][j]);
		}
	}

	return result;
};
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	Matrix3x3 result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			result.m[i][j] =
				(matrix1.m[i][0] * matrix2.m[0][j]) +
				(matrix1.m[i][1] * matrix2.m[1][j]) +
				(matrix1.m[i][2] * matrix2.m[2][j]);
		}
	}

	return result;
};
// 値を直接変える
void Transform(Vec2& vector, Matrix3x3 matrix) {
	Vec2 result;
	float w;


	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	assert(w != 0);

	result.x /= w;
	result.y /= w;

	vector = result;
};

// 拡大縮小行列を作る関数
Matrix3x3 ScaleMatrix(float scaleX, float scaleY) {
	Matrix3x3 matrix;
	matrix.m[0][0] = scaleX;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = scaleY;
	matrix.m[1][2] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = 1;

	return matrix;
};

Matrix3x3 ScaleMatrix(Vec2 scaleXY) {
	Matrix3x3 matrix;
	matrix.m[0][0] = scaleXY.x;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = scaleXY.y;
	matrix.m[1][2] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = 1;

	return matrix;
};
// 回転行列を作る関数
Matrix3x3 RotateMatrix(float theta) {

	Matrix3x3 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[0][2] = 0.0f;

	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[1][2] = 0.0f;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;

	return result;
};
// 平行移動行列を作る関数
Matrix3x3 TranslateMatrix(float tx, float ty) {
	Matrix3x3 matrix;
	matrix.m[0][0] = 1;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = 1;
	matrix.m[1][2] = 0;

	matrix.m[2][0] = tx;
	matrix.m[2][1] = ty;
	matrix.m[2][2] = 1;

	return matrix;
}

Matrix3x3 TranslateMatrix(Vec2 txy) {
	Matrix3x3 matrix;
	matrix.m[0][0] = 1;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = 1;
	matrix.m[1][2] = 0;

	matrix.m[2][0] = txy.x;
	matrix.m[2][1] = txy.y;
	matrix.m[2][2] = 1;

	return matrix;
}

// アフィン行列を作る関数
Matrix3x3 AffineMatrix(Vec2 scale, float rotateTheta, Vec2 translate) {

	Matrix3x3 matrix;
	matrix.m[0][0] = scale.x * cosf(rotateTheta);
	matrix.m[0][1] = scale.x * sinf(rotateTheta);
	matrix.m[0][2] = 0;

	matrix.m[1][0] = scale.y * -sinf(rotateTheta);
	matrix.m[1][1] = scale.y * cosf(rotateTheta);
	matrix.m[1][2] = 0;

	matrix.m[2][0] = translate.x;
	matrix.m[2][1] = translate.y;
	matrix.m[2][2] = 1;

	return matrix;
};


//逆行列を求める関数
Matrix2x2 InverseMatrix(Matrix2x2 matrix) {

	float det = (matrix.m[0][0] * matrix.m[1][1]) - (matrix.m[0][1] * matrix.m[1][0]);
	assert(det != 0);


	Matrix2x2 result;
	result.m[0][0] = matrix.m[1][1];
	result.m[0][1] = -matrix.m[0][1];

	result.m[1][0] = -matrix.m[1][0];
	result.m[1][1] = matrix.m[0][0];

	return Devide(result, det);
};

Matrix3x3 InverseMatrix(Matrix3x3 matrix) {

	float det =
		(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) +
		(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) +
		(matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
		(matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) -
		(matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) -
		(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	assert(det != 0);

	Matrix3x3 result;
	result.m[0][0] = matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1];
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1];

	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	result.m[1][1] = matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0];
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	result.m[2][0] = matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0];
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];

	return Devide(result, det);
};

//転置行列を求める関数
Matrix2x2 Transpose(Matrix2x2 matrix) {

	Matrix2x2 result;
	result.m[0][0] = matrix.m[0][0];
	result.m[0][1] = matrix.m[1][0];

	result.m[1][0] = matrix.m[0][1];
	result.m[1][1] = matrix.m[1][1];

	return result;
};

Matrix3x3 Transpose(Matrix3x3 matrix) {

	Matrix3x3 result;
	result.m[0][0] = matrix.m[0][0];
	result.m[0][1] = matrix.m[1][0];
	result.m[0][2] = matrix.m[2][0];

	result.m[1][0] = matrix.m[0][1];
	result.m[1][1] = matrix.m[1][1];
	result.m[1][2] = matrix.m[2][1];

	result.m[2][0] = matrix.m[0][2];
	result.m[2][1] = matrix.m[1][2];
	result.m[2][2] = matrix.m[2][2];

	return result;
};


//正射影行列を求める関数
Matrix3x3 OrthoMatrix(float left, float right, float top, float bottom) {

	Matrix3x3 result;

	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;

	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1;

	return result;
};

//ビューポート変換行列を求める関数
Matrix3x3 ViewportMatrix(Vec2 size, Vec2 LeftTop) {

	Matrix3x3 result;

	result.m[0][0] = size.x * 0.5f;
	result.m[0][1] = 0;
	result.m[0][2] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -(size.y * 0.5f);
	result.m[1][2] = 0;

	result.m[2][0] = LeftTop.x + (size.x * 0.5f);
	result.m[2][1] = LeftTop.y + (size.y * 0.5f);
	result.m[2][2] = 1;

	return result;
};


//レンダリングパイプライン作る関数
Matrix3x3 WvpVpMatrix(
	Vec2 playerPos, Vec2 playerScale, float playerAngle,
	Vec2 cameraPos, Vec2 cameraScale, float cameraAngle,
	Vec2 cameraRange, Vec2 leftTop,
	Vec2 screenSize
) {

	Matrix3x3 worldMatrix;
	Matrix3x3 cameraMatrix;
	Matrix3x3 viewMatrix;
	Matrix3x3 orthoMatrix;
	Matrix3x3 viewPortMatrix;
	Matrix3x3 result;

	worldMatrix = AffineMatrix(playerScale, playerAngle, playerPos);//プレイヤーのワールド行列
	cameraMatrix = AffineMatrix(cameraScale, cameraAngle, cameraPos);
	viewMatrix = InverseMatrix(cameraMatrix);//カメラの逆行列
	orthoMatrix = OrthoMatrix(//正射影行列
		-(cameraRange.x * 0.5f),
		cameraRange.x * 0.5f,
		-(cameraRange.y * 0.5f),
		cameraRange.y * 0.5f
	);
	viewPortMatrix = ViewportMatrix(//ビューポート行列
		screenSize, leftTop
	);

	//行列の合成
	result = Multiply(worldMatrix, viewMatrix);
	result = Multiply(result, orthoMatrix);
	result = Multiply(result, viewPortMatrix);

	return result;
}

//================================================================
//                        行列の表示の関数
//================================================================

void MatrixScreenPrintf(int posX, int posY, Matrix2x2 matrix) {

	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {

			Novice::ScreenPrintf(
				posX + col * 64,
				posY + row * 20,
				"%.02f",
				matrix.m[row][col]
			);
		}
	}
};

void MatrixScreenPrintf(int posX, int posY, Matrix3x3 matrix) {

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {

			Novice::ScreenPrintf(
				posX + col * 64,
				posY + row * 20,
				"%.02f",
				matrix.m[row][col]
			);
		}
	}
};

void Vec2ScreenPrintf(int posX, int posY, Vec2 vector) {

	Novice::ScreenPrintf(posX, posY, "%.02f", vector.x);
	Novice::ScreenPrintf(posX + 64, posY, "%.02f", vector.y);
};

//================================================================
//                     当たり判定関数
//================================================================

//回転していない矩形と円の当たり判定
bool IsHitBox_Ball(Vec2 boxCenter, Vec2 ballPos, Vec2 boxSize, float ballRasius) {

	float distX = ballPos.x - boxCenter.x;
	float distY = ballPos.y - boxCenter.y;

	if (distX >= -boxSize.x / 2.0f && distX <= boxSize.x / 2.0f) {

		if (distY >= (-boxSize.y / 2.0f) - ballRasius && distY <= (boxSize.y / 2.0f) + ballRasius) {

			return true;

		} else {
			return false;
		}

	} else if (distY >= -boxSize.y / 2.0f && distY <= boxSize.y / 2.0f) {

		if (distX >= (-boxSize.x / 2.0f) - ballRasius && distX <= (boxSize.x / 2.0f) + ballRasius) {
			return true;

		} else {
			return false;
		}

	} else {

		if (distX < 0 && distY < 0) {
			if (
				CheckLength(boxCenter.x - boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}
		} else if (distX >= 0 && distY < 0) {
			if (
				CheckLength(boxCenter.x + boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}

		} else if (distX < 0 && distY >= 0) {
			if (
				CheckLength(boxCenter.x - boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}

		} else {
			if (
				CheckLength(boxCenter.x + boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}
		}
	}
}
//回転していない矩形と円の当たり判定(当たった面を返す)
int IsHitBox_BallDirection(Vec2 boxCenter, Vec2 ballPos, Vec2 boxSize, float ballRasius) {

	float distX = ballPos.x - boxCenter.x;
	float distY = ballPos.y - boxCenter.y;

	if (distX >= -boxSize.x / 2.0f && distX <= boxSize.x / 2.0f) {

		if (distY >= (-boxSize.y / 2.0f) - ballRasius && distY <= (boxSize.y / 2.0f) + ballRasius) {

			if (distY >= 0) {
				return 1;//上面に当たった
			} else {
				return 3;//下面に当たった
			}

		} else {
			return false;
		}

	} else if (distY >= -boxSize.y / 2.0f && distY <= boxSize.y / 2.0f) {

		if (distX >= (-boxSize.x / 2.0f) - ballRasius && distX <= (boxSize.x / 2.0f) + ballRasius) {

			if (distX >= 0) {
				return 2;//右面に当たった
			} else {
				return 4;//左面に当たった
			}

		} else {
			return false;
		}

	} else {

		if (distX < 0 && distY >= 0) {//左上
			if (CheckLength(boxCenter.x - boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if (sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 1;//上面に当たった
				} else {
					return 4;//左面に当たった
				}

			} else {
				return false;
			}
		} else if (distX >= 0 && distY >= 0) {//右上
			if (CheckLength(boxCenter.x + boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if (sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 1;//上面に当たった
				} else {
					return 2;//右面に当たった
				}

			} else {
				return false;
			}

		} else if (distX < 0 && distY < 0) {//左下
			if (CheckLength(boxCenter.x - boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if (sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 3;//上面に当たった
				} else {
					return 4;//左面に当たった
				}

			} else {
				return false;
			}

		} else {//右下
			if (CheckLength(boxCenter.x + boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if (sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 3;//上面に当たった
				} else {
					return 2;//左面に当たった
				}

			} else {
				return false;
			}
		}
	}
}


//矩形と円(矩形がどの角度でもいい)
bool ColisionBox_Ball(Vec2 leftTop, Vec2 rightTop, Vec2 leftBottom, Vec2 rightBottom, Vec2 ballPos, float ballRadius) {

	float cross[4] = { 0.0f };
	int crossInCount = 0;

	cross[0] = Cross(leftTop, rightTop, ballPos);
	cross[1] = Cross(rightTop, rightBottom, ballPos);
	cross[2] = Cross(rightBottom, leftBottom, ballPos);
	cross[3] = Cross(leftBottom, leftTop, ballPos);

	for (int i = 0; i < 4; i++) {
		if (cross[i] > -ballRadius) {
			crossInCount++;
		}

	}

	//円が矩形に完全に含まれていればtrue
	if (crossInCount >= 4) {
		return true;
	};

	//各ベクトルどれかに触れていればtrue
	for (int i = 0; i < 4; i++) {
		if (cross[i] > -ballRadius && cross[i] < ballRadius) {

			float dot = 0.0f;

			switch (i) {

			case 0:
				dot = NoInitDot(leftTop, rightTop, ballPos);
				break;

			case 1:
				dot = NoInitDot(rightTop, rightBottom, ballPos);
				break;

			case 2:
				dot = NoInitDot(rightBottom, leftBottom, ballPos);
				break;

			case 3:
				dot = NoInitDot(leftBottom, leftTop, ballPos);
				break;

			default:
				break;
			}

			if (dot >= 0.0f && dot <= 1.0f) {
				return true;
			}
		}
	}

	//当てはまらなければfalse
	return false;
};


//================================================================
//                     オリジナル描画関数
//================================================================

// 中心点を基準に矩形を描く関数
/// <summary>
/// 中心点を基準に矩形を描く関数
/// </summary>
/// <param name="center">中心座標</param>
/// <param name="size">縦横幅</param>
/// <param name="drawPosX">表示したい画像上の左上座標X</param>
/// <param name="drawPosY">表示したい画像上の左上座標Y</param>
/// <param name="drawWidth">表示したい画像の横幅</param>
/// <param name="drawHight">表示したい画像の縦幅</param>
/// <param name="scaleX">表示倍率X</param>
/// <param name="scaleY">表示倍率Y</param>
/// <param name="GH">グラフハンドル</param>
/// <param name="theta">矩形の角度</param>
/// <param name="color">画像のカラーコード</param>
void My::DrawQuad(
	Vec2 center,
	Vec2 size,
	int drawPosX, int drawPosY,
	int drawWidth, int drawHight,
	float scaleX, float scaleY,
	int GH, float theta, int color
) {

	Vec2 vertex[4] = {
		{center.x - (size.x * scaleX) * 0.5f,center.y - (size.y * scaleY) * 0.5f},
		{center.x + (size.x * scaleX) * 0.5f,center.y - (size.y * scaleY) * 0.5f},
		{center.x - (size.x * scaleX) * 0.5f,center.y + (size.y * scaleY) * 0.5f},
		{center.x + (size.x * scaleX) * 0.5f,center.y + (size.y * scaleY) * 0.5f},
	};

	Vec2 preVertex[4];

	//回転
	for (int i = 0; i < 4; i++) {

		preVertex[i] = vertex[i];

		preVertex[i].x -= center.x;
		preVertex[i].y -= center.y;

		vertex[i].x = preVertex[i].x * cosf(theta) - preVertex[i].y * sinf(theta);
		vertex[i].y = preVertex[i].x * sinf(theta) + preVertex[i].y * cosf(theta);

		vertex[i].x += center.x;
		vertex[i].y += center.y;
	}

	Novice::DrawQuad(
		int(vertex[0].x),
		int(vertex[0].y),
		int(vertex[1].x),
		int(vertex[1].y),
		int(vertex[2].x),
		int(vertex[2].y),
		int(vertex[3].x),
		int(vertex[3].y),
		drawPosX, drawPosY,
		drawHight, drawWidth,
		GH, color
	);

};

// 中心点を基準に三角形を描く関数
/// <summary>
/// 中心点を基準に三角形を描く関数
/// </summary>
/// <param name="center">中心座標</param>
/// <param name="radius">三角形の半径</param>
/// <param name="theta">三角形の角度</param>
/// <param name="color">三角形の色</param>
void My::DrawTriangle(Vec2 center, float radius, float theta, int color) {

	Vec2 vertex[3];
	Vec2 preVertex[3];

	//初期座標
	for (int i = 0; i < 3; i++) {
		vertex[i].x = center.x + cosf((-(1.0f / 2.0f) + (i * (2.0f / 3.0f))) * float(M_PI)) * radius;
		vertex[i].y = center.y + sinf((-(1.0f / 2.0f) + (i * (2.0f / 3.0f))) * float(M_PI)) * radius;
	}

	//回転
	for (int i = 0; i < 3; i++) {

		preVertex[i] = vertex[i];

		preVertex[i].x -= center.x;
		preVertex[i].y -= center.y;

		vertex[i].x = preVertex[i].x * cosf(theta) - preVertex[i].y * sinf(theta);
		vertex[i].y = preVertex[i].x * sinf(theta) + preVertex[i].y * cosf(theta);

		vertex[i].x += center.x;
		vertex[i].y += center.y;
	}

	//描画
	Novice::DrawTriangle(
		int(vertex[0].x),
		int(vertex[0].y),
		int(vertex[1].x),
		int(vertex[1].y),
		int(vertex[2].x),
		int(vertex[2].y),
		color,
		kFillModeSolid
	);

};

// 中心点から星を描く関数
/// <summary>
/// 中心点を基準に星を描く関数
/// </summary>
/// <param name="center">中心座標</param>
/// <param name="radius">三角形の半径</param>
/// <param name="theta">三角形の角度</param>
/// <param name="color">三角形の色</param>
void My::DrawStar(Vec2 center, float radius, float theta, int color) {

	Vec2 vertex[5];
	Vec2 preVertex[5];
	Vec2 crossPos[3];

	//初期座標
	for (int i = 0; i < 5; i++) {

		vertex[i].x = center.x + radius * cosf(((((2.0f / 5.0f) * i) - (1.0f / 2.0f)) * float(M_PI)));
		vertex[i].y = center.y + radius * sinf(((((2.0f / 5.0f) * i) - (1.0f / 2.0f)) * float(M_PI)));
	}

	crossPos[0] = CrossPos(vertex[2], vertex[4], vertex[3], vertex[0]);
	crossPos[1] = CrossPos(vertex[3], vertex[0], vertex[4], vertex[1]);
	crossPos[2] = CrossPos(vertex[4], vertex[1], vertex[0], vertex[2]);

	//回転
	for (int i = 0; i < 5; i++) {

		preVertex[i] = vertex[i];

		preVertex[i].x -= center.x;
		preVertex[i].y -= center.y;

		vertex[i].x = preVertex[i].x * cosf(theta) - preVertex[i].y * sinf(theta);
		vertex[i].y = preVertex[i].x * sinf(theta) + preVertex[i].y * cosf(theta);

		vertex[i].x += center.x;
		vertex[i].y += center.y;
	}

	crossPos[0] = CrossPos(vertex[2], vertex[4], vertex[3], vertex[0]);
	crossPos[1] = CrossPos(vertex[3], vertex[0], vertex[4], vertex[1]);
	crossPos[2] = CrossPos(vertex[4], vertex[1], vertex[0], vertex[2]);

	//描画
	for (int i = 0; i < 3; i++) {
		Novice::DrawTriangle(
			int(vertex[i].x),
			int(vertex[i].y),
			int(vertex[i + 2].x),
			int(vertex[i + 2].y),
			int(crossPos[i].x),
			int(crossPos[i].y),
			color,
			kFillModeSolid
		);
	}
};


//================================================================
//                     色を扱う関数
//================================================================

//色の各要素を求める関数
int Red(int color) { return (color >> 24) & 0xFF; }
int Green(int color) { return (color >> 16) & 0xFF; }
int Blue(int color) { return (color >> 8) & 0xFF; }
int Alpha(int color) { return color & 0xFF; }

//色の差を任意の値で割り、割合も任意に決めて色を変える関数
int ChangeColor(int startColor, int aimColor, float divideNum, float rate) {

	//二色の差を求める
	int difRed = Red(aimColor) - Red(startColor);
	int difGreen = Green(aimColor) - Green(startColor);
	int difBlue = Blue(aimColor) - Blue(startColor);
	int difAlpha = Alpha(aimColor) - Alpha(startColor);

	//差分を任意の値で割る
	float dividedRed = float(difRed) / divideNum;
	float dividedGreen = float(difGreen) / divideNum;
	float dividedBlue = float(difBlue) / divideNum;
	float dividedAlpha = float(difAlpha) / divideNum;

	//割った値をrate倍する
	int Red = int(dividedRed * rate) << 24;
	int Green = int(dividedGreen * rate) << 16;
	int Blue = int(dividedBlue * rate) << 8;
	int Alpha = int(dividedAlpha * rate);

	//色を足して返す
	return startColor + Red + Green + Blue + Alpha;
}

//媒介変数tで色を変更する
int ChangeColorT(int startColor, int aimColor, float t) {

	//二色の差を求める
	int difRed = Red(aimColor) - Red(startColor);
	int difGreen = Green(aimColor) - Green(startColor);
	int difBlue = Blue(aimColor) - Blue(startColor);
	int difAlpha = Alpha(aimColor) - Alpha(startColor);

	int Red = int(difRed * t) << 24;
	int Green = int(difGreen * t) << 16;
	int Blue = int(difBlue * t) << 8;
	int Alpha = int(difAlpha * t);

	//色を足して返す
	return startColor + Red + Green + Blue + Alpha;
}

//グレースケールを求める関数
int GrayScale(int color) {

	int Red = (color >> 24) & 0xFF;
	int Green = (color >> 16) & 0xFF;
	int Blue = (color >> 8) & 0xFF;

	int trancedRed = int(float(Red) * 0.2126f);
	int trancedGreen = int(float(Green) * 0.7152f);
	int trancedBlue = int(float(Blue) * 0.0722f);

	int gray = int(trancedRed + trancedGreen + trancedBlue);

	return 0xFF + (gray << 24) + (gray << 16) + (gray << 8);
};