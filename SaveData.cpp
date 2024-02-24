#include "SaveData.h"

Vec2 SaveData::savedPlayerPos_ = { 0.0f,0.0f };
Vec2 SaveData::savedPlayerShadowPos_ = { 0.0f,0.0f };
Vec2 SaveData::savedLightPos_ = { 0.0f,0.0f };
std::vector<std::vector<int>> SaveData::savedMap_ = { {0} };

Vec2 SaveData::playerPos_ = { 0.0f,0.0f };
Vec2 SaveData::playerShadowPos_ = { 0.0f,0.0f };
Vec2 SaveData::lightPos_ = { 0.0f,0.0f };
std::vector<std::vector<int>> SaveData::map_ = { {0} };


void SaveData::Init() {
}
