#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <Novice.h>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Easing.h"
#include "VectorN.h"
#include "MatrixNxN.h"


//何もしない関数
void Void();

//================================================================
//                     ファイル操作の関数
//================================================================
std::vector<std::vector<int>>LoadFile(const std::string& csvFilePath);

//================================================================
//                       時間の関数
//================================================================
//フレーム数を時間に換算する関数
/// <summary>
/// フレーム数を時間に換算する関数
/// </summary>
/// <param name="count">:フレーム数</param>
/// <param name="tranceMode">[0:秒][1:分][2:時間]</param>
/// <returns></returns>
int FrameToClock(int count, int tranceMode);

//================================================================
//                      数学的な関数
//================================================================

//長さを計る関数
float CheckLength(Vec2 pos1, Vec2 pos2);
float CheckLength(float pos1x, float pos1y, float pos2x, float pos2y);

//ノーマライズ関数
Vec2 Normalize(Vec2 pos1, Vec2 pos2);

//内積を求める
float Dot(Vec2 pos1, Vec2 pos2, Vec2 targetPos);

//外積を求める関数
float Cross(
	float line1StartX, float line1StartY,
	float line1EndX, float line1EndY,
	float targetX, float targetY
);

float Cross(Vec2 pos1, Vec2 pos2, Vec2 targetPos);

//線と線の交点を求める関数
Vec2 CrossPos(
	Vec2 line1Pos1, Vec2 line1Pos2,
	Vec2 line2Pos1, Vec2 line2Pos2
);

//線を平行移動する関数
Vec2 ShiftLine(Vec2 pos1, Vec2 pos2, float distance);
void ShiftLineCtrl(Vec2 pos1, Vec2 pos2, float distance);

//================================================================
//                      行列の計算関数
//================================================================
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix3x3 Add(Matrix3x3 matrix1, Matrix3x3 matrix2);

Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix3x3 Subtract(Matrix3x3 matrix1, Matrix3x3 matrix2);

Matrix2x2 Devide(Matrix2x2 matrix, float devideNum);
Matrix3x3 Devide(Matrix3x3 matrix, float devideNum);

Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
Vec2 Multiply(Vec2 vector, Matrix2x2 matrix);
Vec2 Multiply(Vec2 vector, Matrix3x3 matrix);
void Transform(Vec2& vector, Matrix3x3 matrix);

//目的に対応した行列を作る関数
Matrix3x3 RotateMatrix(float theta);
Matrix3x3 TranslateMatrix(float tx, float ty);
Matrix3x3 TranslateMatrix(Vec2 txy);
Matrix3x3 ScaleMatrix(float scaleX, float scaleY);
Matrix3x3 ScaleMatrix(Vec2 scaleXY);
Matrix3x3 AffineMatrix(Vec2 scale, float rotateTheta, Vec2 transLate);

//逆行列を求める関数
Matrix2x2 InverseMatrix(Matrix2x2 matrix);
Matrix3x3 InverseMatrix(Matrix3x3 matrix);

//転置行列を求める関数
Matrix2x2 Transpose(Matrix2x2 matrix);
Matrix3x3 Transpose(Matrix3x3 matrix);

//正射影行列を求める関数
Matrix3x3 OrthoMatrix(float left, float right, float top, float bottom);

//ビューポート変換行列を求める関数
Matrix3x3 ViewportMatrix(Vec2 size, Vec2 LeftTop);

//レンダリングパイプライン作る関数
Matrix3x3 WvpVpMatrix(
	Vec2 playerPos, Vec2 playerScale, float playerAngle,
	Vec2 cameraPos, Vec2 cameraScale, float cameraAngle,
	Vec2 cameraRange, Vec2 leftTop,
	Vec2 screenSize
);

//行列の情報を表示する関数
void MatrixScreenPrintf(int posX, int posY, Matrix2x2 matrix);
void MatrixScreenPrintf(int posX, int posY, Matrix3x3 matrix);
void Vec2ScreenPrintf(int posX, int posY, Vec2 vector);

//================================================================
//                     当たり判定関数
//================================================================

//回転していない矩形と円の当たり判定
bool IsHitBox_Ball(Vec2 boxCenter, Vec2 ballPos, Vec2 boxSize, float ballRasius);
//回転していない矩形と円の当たり判定(当たった面を返す)
int IsHitBox_BallDirection(Vec2 boxCenter, Vec2 ballPos, Vec2 boxSize, float ballRasius);

//================================================================
//                     オリジナル描画関数
//================================================================
namespace My {

	//中心基準矩形
	void DrawQuad(
		Vec2 center,
		Vec2 size,
		int drawPosX, int drawPosY,
		int drawWidth, int drawHight,
		float scaleX, float scaleY,
		int GH, float theta, int color
	);
	//中心座標基準三角
	void DrawTriangle(Vec2 center, float radius, float theta, int color);
	//星
	void DrawStar(Vec2 center, float radius, float theta, int color);
}

//================================================================
//                     色を扱う関数
//================================================================

//色の各成分を求める関数
int Red(int color);
int Green(int color);
int Blue(int color);
int Alpha(int color);

//色を変える関数
int ChangeColor(int startColor, int aimColor, float divideNum, float rate);
int ChangeColorT(int startColor, int aimColor, float t);

int GrayScale(int color);
