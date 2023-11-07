#include "LocalFunc.h"
/*===============================プレイヤーとブロックの当たり判定===================================*/
void CalcAddress(Vector2<int>address[4], Vec2 pos, Vec2 size, float radius){

	address[LeftTop].x = int((pos.x - radius) / size.x);
	address[LeftTop].y = int((pos.y - radius) / size.y);

	address[RightTop].x = int((pos.x + radius - 1) / size.x);
	address[RightTop].y = int((pos.y - radius) / size.y);

	address[LeftBottom].x = int((pos.x - radius) / size.x);
	address[LeftBottom].y = int((pos.y + radius - 1) / size.y);

	address[RightBottom].x = int((pos.x + radius - 1) / size.x);
	address[RightBottom].y = int((pos.y + radius - 1) / size.y);
}

int PushBackMapChip(
	int rowMAX, int colMAX,
	Vec2* playerCenterPos,
	Vector2<int>playerAddress[4], Vector2<int>playerPreAddress[4],
	Vec2 playerSize,
	Vec2 playerVelocity,
	std::vector<std::vector<Vec2>>blockPos,
	std::vector<std::vector<int>>blockType,
	Vec2 blockSize
) {

	enum HitSurface {
		Top = 1,
		Right = 2,
		Bottom = 3,
		Left = 4,
		Top_Right = 5,
		Right_Bottom = 6,
		Bottom_Left = 7,
		Left_Top = 8
	};

	int surface = 0;

	for (int i = 0; i < 4; i++) {

		if (playerAddress[i].x >= 0 && playerAddress[i].x < colMAX) {
			if (playerAddress[i].y >= 0 && playerAddress[i].y < rowMAX) {
				if (blockType[playerAddress[i].y][playerAddress[i].x] != 0) {
					/*------------------前フレームとX座標の番地のみが違う場合--------------------*/

					if (playerAddress[i].x != playerPreAddress[i].x &&
						playerAddress[i].y == playerPreAddress[i].y) {

						switch (i) {

						case LeftTop:

							if (playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//x座標を押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);


								}
							}

							surface = Right;
							break;

						case RightTop:

							if (playerAddress[i].x > playerPreAddress[i].x) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//x座標を押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

								}
							}

							surface = Left;
							break;

						case LeftBottom:

							if (playerAddress[i].x < playerPreAddress[i].x) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//x座標を押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

								}
							}

							surface = Right;
							break;

						case RightBottom:

							if (playerAddress[i].x > playerPreAddress[i].x) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//x座標を押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

								}
							}

							surface = Left;
							break;

						default:
							break;
						}
					}

					/*------------------前フレームとY座標の番地のみが違う場合--------------------*/

					else if (playerAddress[i].x == playerPreAddress[i].x &&
						playerAddress[i].y != playerPreAddress[i].y) {

						switch (i) {

						case LeftTop:

							if (playerAddress[i].y < playerPreAddress[i].y) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//y座標を押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);

								}
							}

							surface = Bottom;
							break;

						case RightTop:

							if (playerAddress[i].y < playerPreAddress[i].y) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//y座標を押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);
								}
							}

							surface = Bottom;
							break;

						case LeftBottom:

							if (playerAddress[i].y > playerPreAddress[i].y) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//y座標を押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

								}
							}

							surface = Top;
							break;

						case RightBottom:

							if (playerAddress[i].y > playerPreAddress[i].y) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//y座標を押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

								}
							}

							surface = Top;
							break;

						default:
							break;
						}
					}

					/*------------------前フレームとX番地,Y番地の両方が違う場合--------------------*/

					else if (playerAddress[i].x != playerPreAddress[i].x &&
						playerAddress[i].y != playerPreAddress[i].y) {

						switch (i) {

						case LeftTop:

							//左上に侵入した場合=================================
							if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								//===========================行先すべてにブロックがある場合===========================
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] >= 1) {

									//x,y両方押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

									surface = Right_Bottom;

									//=======================プレイヤーの上にブロックがない場合========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] < 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

									surface = Right;
									//======================プレイヤーの左にブロックがない場合=========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);

									surface = Bottom;
									//========================行先にしかブロックがない場合===========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] < 1) {

									//前フレームの座標を求める
									Vector2 prePos = { playerCenterPos->x - playerVelocity.x, playerCenterPos->y - playerVelocity.y };

									/*前座標　⇒　現座標までのYの移動量の比率*/
									float rateY = sqrtf(powf(playerCenterPos->y - prePos.y, 2)) / sqrtf(powf(playerCenterPos->x - prePos.x, 2));
									/*前座標　⇒　ブロック右下までのYの移動量の比率*/
									float rateY2 =
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].y + (blockSize.y  * 0.5f)- prePos.y, 2)) /
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].x + (blockSize.x * 0.5f)- prePos.x, 2));

									if (rateY > rateY2) {
										//xを押し戻す
										playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
											(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

										surface = Right;
									} else {
										//yを押し戻す
										playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
											(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);

										surface = Bottom;
									}
								}
							}


							//左下に侵入した場合=================================
							else if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

								}

								surface = Right;
							}

							//右上侵入した場合=================================
							else if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);

								}

								surface = Bottom;
							}

							break;

						case RightTop:

							if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								//===========================行先すべてにブロックがある場合===========================
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] >= 1) {

									//x,y両方押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

									surface = Bottom_Left;

									//=======================プレイヤーの上にブロックがない場合========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] < 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

									surface = Left;

									//======================プレイヤーの左にブロックがない場合=========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);

									surface = Bottom;

									//========================行先にしかブロックがない場合===========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] < 1) {

									//前フレームの座標を求める
									Vector2 prePos = { playerCenterPos->x - playerVelocity.x, playerCenterPos->y - playerVelocity.y };

									/*前座標　⇒　現座標までのYの移動量の比率*/
									float rateY = sqrtf(powf(playerCenterPos->y - prePos.y, 2)) / sqrtf(powf(playerCenterPos->x - prePos.x, 2));
									/*前座標　⇒　ブロック右下までのYの移動量の比率*/
									float rateY2 =
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].y + (blockSize.y  * 0.5f)- prePos.y, 2)) /
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].x + (blockSize.x * 0.5f)- prePos.x, 2));

									if (rateY > rateY2) {
										//xを押し戻す
										playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

										surface = Left;
									} else {
										//yを押し戻す
										playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
											(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);
										surface = Bottom;
									}
								}

							}

							//右下に侵入した場合=================================
							else if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

								}

								surface = Left;
							}

							//左上に侵入した場合=================================
							else if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y  * 0.5f)+ (playerSize.y * 0.5f);

								}

								surface = Bottom;
							}

							break;

						case LeftBottom:


							if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								//===========================行先すべてにブロックがある場合===========================
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] >= 1) {

									//x,y両方押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

									surface = Top_Right;

									//=======================プレイヤーの上にブロックがない場合========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] < 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

									surface = Right;

									//======================プレイヤーの左にブロックがない場合=========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

									surface = Top;

									//========================行先にしかブロックがない場合===========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] < 1) {

									//前フレームの座標を求める
									Vector2 prePos = { playerCenterPos->x - playerVelocity.x, playerCenterPos->y - playerVelocity.y };

									/*前座標　⇒　現座標までのYの移動量の比率*/
									float rateY = sqrtf(powf(playerCenterPos->y - prePos.y, 2)) / sqrtf(powf(playerCenterPos->x - prePos.x, 2));
									/*前座標　⇒　ブロック右下までのYの移動量の比率*/
									float rateY2 =
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].y + (blockSize.y  * 0.5f)- prePos.y, 2)) /
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].x + (blockSize.x * 0.5f)- prePos.x, 2));

									if (rateY > rateY2) {
										//xを押し戻す
										playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
											(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

										surface = Right;
									} else {
										//yを押し戻す
										playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

										surface = Top;
									}
								}
							}

							//左上に侵入した場合=================================
							else if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x  * 0.5f)+ (playerSize.x * 0.5f);

								}

								surface = Right;
							}

							//右下に侵入した場合=================================
							else if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

								}

								surface = Top;
							}

							break;

						case RightBottom:

							if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								//===========================行先すべてにブロックがある場合===========================
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] >= 1) {

									//x,y両方押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

									surface = Left_Top;
									//=======================プレイヤーの上にブロックがない場合========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] < 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

									surface = Left;

									//======================プレイヤーの左にブロックがない場合=========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

									surface = Top;

									//========================行先にしかブロックがない場合===========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] == 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] != 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] != 1) {

									//前フレームの座標を求める
									Vector2 prePos = { playerCenterPos->x - playerVelocity.x, playerCenterPos->y - playerVelocity.y };

									/*前座標　⇒　現座標までのYの移動量の比率*/
									float rateY = sqrtf(powf(playerCenterPos->y - prePos.y, 2)) / sqrtf(powf(playerCenterPos->x - prePos.x, 2));
									/*前座標　⇒　ブロック右下までのYの移動量の比率*/
									float rateY2 =
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].y + (blockSize.y  * 0.5f)- prePos.y, 2)) /
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].x + (blockSize.x * 0.5f)- prePos.x, 2));

									if (rateY > rateY2) {
										//xを押し戻す
										playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);

										surface = Left;
									} else {
										//yを押し戻す
										playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (playerSize.y * 0.5f + 1);

										surface = Top;
									}
								}
							}


							//右上に侵入した場合=================================
							else if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x -(blockSize.x * 0.5f) - (playerSize.x * 0.5f);
								}

								surface = Left;
							}

							//左下に侵入した場合=================================
							else if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

								}
								surface = Top;
							}

							break;

						default:
							break;

						}
					}
				}
			} else {
				surface = false;
			}
		} else {
			surface = false;
		}
	}

	return surface;
}