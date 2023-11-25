#include "Particle.h"

void Particle::Init(float theta, Vec2 pos, Vec2 size, float speed) {
	theta_ = theta;
	pos_ = pos;
	size_ = size;
	speed_ = speed;
}

void Particle::Update(Emitter emitter, PlayerShadow pShadow,const Shadow& shadow,Screen screen) {

	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================

		//プレイヤーが死んだときのエフェクト
		if (!pShadow.GetIsAlive()) {

			//プレイヤーが死んだ瞬間の初期化
			if (!isAlive_) {
				if (pShadow.GetIsPreAlive()) {

					Init(
						float(rand()),
						{
							pShadow.GetPos().x + cosf(float(rand())) * (emitter.GetRange_().x/8.0f),
							pShadow.GetPos().y + sinf(float(rand())) * (emitter.GetRange_().y/8.0f)
						},
						{pShadow.GetSize().x * 0.5f, pShadow.GetSize().y * 0.5f},
						float(rand() % 300) / 100.0f
					);

					isAlive_ = true;
				}

				if (pShadow.GetIsBackToResPawnPos()) {
					if (!pShadow.GetPreIsBackToResPawnPos()) {


						Init(
							float(rand()),
							{
								shadow.firstPlayerPos_.x + screen.GetScreenLeftTop().x + cosf(float(rand())) * float(rand()%180),
								(shadow.firstPlayerPos_.y + screen.GetScreenLeftTop().y + 10) + sinf(float(rand())) * float(rand() % 180)
							},
							{ float(rand() % 80),float(rand() % 80) },
							float(rand() % 300) / 100.0f
						);

						moveVec_.x = (shadow.firstPlayerPos_.x + screen.GetScreenLeftTop().x) - pos_.x;
						moveVec_.y = (shadow.firstPlayerPos_.y + screen.GetScreenLeftTop().y + 10) - pos_.y;

						startPos_ = pos_;
						lifeTime_ = 80;
						alpha_ = 0x00;
						isAlive_ = true;
					}
				}

			} else {

				//プレイヤーが霧散する処理
				if (!pShadow.GetIsBackToResPawnPos()) {
					lifeTime_--;
					pos_.x += cosf(theta_) * (EaseInExpo(1.0f - (lifeTime_ / kLifeTime_)) * speed_);
					pos_.y += sinf(theta_) * (EaseInExpo(1.0f - (lifeTime_ / kLifeTime_)) * speed_);
					pos_.y -= speed_ * EaseOutExpo(1.0f - (lifeTime_ / kLifeTime_));

					theta_ += ((1.0f / 60.0f) * float(M_PI)) * speed_;

					size_.x -= 0.2f;
					if (size_.x < 0.0f) {
						size_.x = 0.0f;
					}

					alpha_ -= int((float(0xff) / kLifeTime_) * 1.5f);
					if (alpha_ < 0) {
						alpha_ = 0;
					}

					if (lifeTime_ == 0) {
						lifeTime_ = kLifeTime_;
						isAlive_ = false;
						particleMax_ = 120;

						pos_ = { -100.0f,-100.0f };
						size_ = { 8.0f,8.0f };
						alpha_ = 0xff;
						theta_ = 0.0f;
						speed_ = float(rand() % 30) / 10.0f;
					}
				
				} else if (pShadow.GetIsBackToResPawnPos()) {//プレイヤーがリスポーン地点に収束する処理

					lifeTime_--;
					
					pos_.x = startPos_.x + (moveVec_.x * (EaseInOutQuint(1.0f - (float(lifeTime_) / 80.0f))));
					pos_.y = startPos_.y + (moveVec_.y * (EaseInOutQuint(1.0f - (float(lifeTime_) / 80.0f))));

					theta_ += ((1.0f / 60.0f) * float(M_PI)) * speed_;

					size_.x --;
					if (size_.x < 16.0f) {
						size_.x = 16.0f;
					}

					alpha_ += int( 0xFF / 160);
					if (alpha_ > 0xff) {
						alpha_ = 0xff;
					}

					if (lifeTime_ <= 2) {
						lifeTime_ = kLifeTime_;
						isAlive_ = false;
						particleMax_ = 120;

						pos_ = { -100.0f,-100.0f };
						size_ = { 8.0f,8.0f };
						alpha_ = 0xff;
						theta_ = 0.0f;
						speed_ = float(rand() % 30) / 10.0f;
					}
				}
			}
		}

		break;
	case CLEAR:
		break;
	default:
		break;
	}
}

void Particle::Draw() {

	//if (isAlive_) {
		My::DrawTriangle(
			pos_,
			size_.x,
			theta_,
			0x00000000 + alpha_
		);
	//}
}
