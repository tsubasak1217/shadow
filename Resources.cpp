#include "Resources.h"

Resources::Resources() {

	whiteGH_ = Novice::LoadTexture("white1x1.png");
	doorGH_ = Novice::LoadTexture("./Resources/images/Door.png");
	titleFontGH_ = Novice::LoadTexture("./Resources/images/title.png");
	pressSpaceFontGH_ = Novice::LoadTexture("./Resources/images/space2.png");
	pressSpaceFontGH2_ = Novice::LoadTexture("./Resources/images/space.png");
	pressSpaceFontGH3_ = Novice::LoadTexture("./Resources/images/space3.png");
	rengaGH_ = Novice::LoadTexture("./Resources/images/titleWall.png");
	titleBGGH_ = Novice::LoadTexture("./Resources/images/titleBG.png");
	pauseMenuGH_ = Novice::LoadTexture("./Resources/images/pauseMenu.png");
	pauseGH_ = Novice::LoadTexture("./Resources/images/pause.png");
	stageClearFontGH_ = Novice::LoadTexture("./Resources/images/stageClear.png");
	selectFontGH_ = Novice::LoadTexture("./Resources/images/stageSelect.png");
	keysGH_ = Novice::LoadTexture("./Resources/images/keys1.png");
	creditFontGH_ = Novice::LoadTexture("./Resources/images/credit.png");
	slashGH_ = Novice::LoadTexture("./Resources/images/slash.png");

	mapCsv_[0] = "./Resources/csv/stage1/mapChip.csv";
	mapCsv_[1] = "./Resources/csv/stage2/mapChip.csv";
	mapCsv_[2] = "./Resources/csv/stage3/mapChip.csv";
	mapCsv_[3] = "./Resources/csv/stage4/mapChip.csv";
	mapCsv_[4] = "./Resources/csv/stage5/mapChip.csv";
	mapCsv_[5] = "./Resources/csv/stage6/mapChip.csv";
	mapCsv_[6] = "./Resources/csv/stage7/mapChip.csv";
	mapCsv_[7] = "./Resources/csv/stage8/mapChip.csv";
	mapCsv_[8] = "./Resources/csv/stage9/mapChip.csv";
	mapCsv_[9] = "./Resources/csv/stage10/mapChip.csv";
	mapCsv_[10] = "./Resources/csv/stage11/mapChip.csv";
	mapCsv_[11] = "./Resources/csv/stage12/mapChip.csv";
	mapCsv_[12] = "./Resources/csv/stage13/mapChip.csv";
	mapCsv_[13] = "./Resources/csv/stage14/mapChip.csv";
	mapCsv_[14] = "./Resources/csv/stage15/mapChip.csv";
	mapCsv_[15] = "./Resources/csv/stage16/mapChip.csv";

	screenCsv_[0] = "./Resources/csv/stage1/screen.csv";
	screenCsv_[1] = "./Resources/csv/stage2/screen.csv";
	screenCsv_[2] = "./Resources/csv/stage3/screen.csv";
	screenCsv_[3] = "./Resources/csv/stage4/screen.csv";
	screenCsv_[4] = "./Resources/csv/stage5/screen.csv";
	screenCsv_[5] = "./Resources/csv/stage6/screen.csv";
	screenCsv_[6] = "./Resources/csv/stage7/screen.csv";
	screenCsv_[7] = "./Resources/csv/stage8/screen.csv";
	screenCsv_[8] = "./Resources/csv/stage9/screen.csv";
	screenCsv_[9] = "./Resources/csv/stage10/screen.csv";
	screenCsv_[10] = "./Resources/csv/stage11/screen.csv";
	screenCsv_[11] = "./Resources/csv/stage12/screen.csv";
	screenCsv_[12] = "./Resources/csv/stage13/screen.csv";
	screenCsv_[13] = "./Resources/csv/stage14/screen.csv";
	screenCsv_[14] = "./Resources/csv/stage15/screen.csv";
	screenCsv_[15] = "./Resources/csv/stage16/screen.csv";
}

Resources::~Resources() {
}
