#pragma once
enum SCENENAME {
	TITLE,
	SELECT,
	GAME,
	CLEAR
};

class Scene{
	
public:
	
	static int sceneNum_;
	Scene();
	~Scene();
	
	//int GetSceneNum() { return sceneNum_; }
};
