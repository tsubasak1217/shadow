#include "Player.h"

void Player::Update(char* keys) {
	velocity_ = { 0.0f,0.0f };

	direction_.x = float(keys[DIK_RIGHT]- keys[DIK_LEFT]);
	direction_.y = float(keys[DIK_DOWN] - keys[DIK_UP]);

	velocity_ = Normalize({ 0.0f,0.0f }, direction_);

	velocity_.x *= speed_;
	velocity_.y *= speed_;

	pos_.x += velocity_.x;
	pos_.y += velocity_.y;
}

void Player::Draw(Resources rs,Map map) {

	Novice::DrawQuad(
		int(map.GetPuzzleLeftTop().x + pos_.x - size_.x * 0.5f),
		int(map.GetPuzzleLeftTop().y + pos_.y + size_.y * 0.5f),
		int(map.GetPuzzleLeftTop().x + pos_.x + size_.x * 0.5f),
		int(map.GetPuzzleLeftTop().y + pos_.y + size_.y * 0.5f),
		int(map.GetPuzzleLeftTop().x + pos_.x - size_.x * 0.5f),
		int(map.GetPuzzleLeftTop().y + pos_.y - size_.y * 0.5f),
		int(map.GetPuzzleLeftTop().x + pos_.x + size_.x * 0.5f),
		int(map.GetPuzzleLeftTop().y + pos_.y - size_.y * 0.5f),
		0, 0,
		1, 1,
		rs.whiteGH,
		0xff0000ff
	);
}