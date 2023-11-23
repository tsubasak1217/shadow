#include "Resources.h"

Resources::Resources() {

	whiteGH_ = Novice::LoadTexture("white1x1.png");
	doorGH_ = Novice::LoadTexture("./Resources/images/Door.png");

	mapCsv_[0] = "./Resources/csv/stage1/mapChip.csv";
	mapCsv_[1] = "./Resources/csv/stage2/mapChip.csv";
	mapCsv_[2] = "./Resources/csv/stage3/mapChip.csv";
	mapCsv_[3] = "./Resources/csv/stage4/mapChip.csv";
	mapCsv_[4] = "./Resources/csv/stage5/mapChip.csv";
	mapCsv_[5] = "./Resources/csv/stage6/mapChip.csv";
	mapCsv_[6] = "./Resources/csv/stage7/mapChip.csv";
	mapCsv_[7] = "./Resources/csv/stage8/mapChip.csv";

	screenCsv_[0] = "./Resources/csv/stage1/screen.csv";
	screenCsv_[1] = "./Resources/csv/stage2/screen.csv";
	screenCsv_[2] = "./Resources/csv/stage3/screen.csv";
	screenCsv_[3] = "./Resources/csv/stage4/screen.csv";
	screenCsv_[4] = "./Resources/csv/stage5/screen.csv";
	screenCsv_[5] = "./Resources/csv/stage6/screen.csv";
	screenCsv_[6] = "./Resources/csv/stage7/screen.csv";
	screenCsv_[7] = "./Resources/csv/stage8/screen.csv";

}

Resources::~Resources() {
}
