#pragma once
#include "Light.h"

class Screen {

	Vec2 size_;
	Vec2 leftTop_;
	Vec4 LRTB_;
	Vec2 centerPos_;

	std::vector<std::vector<Vec2>>boxPos_;
	std::vector<std::vector<Vec2>>preBoxPos_;

public:
	Screen(Map map, Light light) {

		boxPos_.clear();
		preBoxPos_.clear();

		size_ = {
			map.GetPuzzleMapSize().x,
			map.GetPuzzleMapSize().y * 2.0f
		};

		centerPos_ = {
		map.GetPuzzleLeftTop().x + (map.GetPuzzleMapSize().x * 0.5f),
		map.GetPuzzleLeftTop().y - (map.GetPuzzleMapSize().y * 0.5f)
		};


		LRTB_ = {
			map.GetPuzzleLeftTop().x,//left
			map.GetPuzzleLeftTop().x + size_.x,//right
			map.GetPuzzleLeftTop().y - size_.y,//top
			map.GetPuzzleLeftTop().y//bottom
		};

		leftTop_ = { LRTB_.x,LRTB_.z };


		for (int i = 0; i < map.GetVertex().size(); i++) {
			std::vector<Vec2>objVertex;
			for (int j = 0; j < map.GetVertex()[i].size(); j++) {

				//手前 → 奥
				//LT,RT,LB,RB の順番

				//光源から見て手前-------------------------------
				objVertex.push_back(
					{//左上
					CrossPos(
						light.GetEmitPos(),
						{
							map.GetVertex(i,j).x,
							map.GetVertex(i,j).y
						},
						map.GetPuzzleLeftTop(),
						{
							map.GetPuzzleLeftTop().x + 16,
							map.GetPuzzleLeftTop().y
						}
					).x,
					map.GetPuzzleLeftTop().y
					- (map.GetVertex(i,j).z * (((map.GetVertex(i,j).y - map.GetPuzzleLeftTop().y) / map.GetPuzzleMapSize().y) * 4.0f))
					}
				);
			}

			boxPos_.push_back(objVertex);
		}

		preBoxPos_ = boxPos_;
	};

	void Init(int sceneNum, Map map, Light light);

	void Update(char* keys, const ChangeScene& cs, Map map, Light light);

	void Draw(Map map, const Resources& rs, Light light);

	Vec2 GetScreenLeftTop() { return leftTop_; }
	Vec2 GetSize() { return size_; }

	std::vector<std::vector<Vec2>>GetPos() { return boxPos_; }
	Vec2 GetPos(int boxNumber,int vertex) { return boxPos_[boxNumber][vertex]; }
	Vec2 GetPrePos(int boxNumber, int vertex) { return preBoxPos_[boxNumber][vertex]; }
};

