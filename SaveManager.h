#pragma once

class SaveManager{

public:

	~SaveManager();

	static SaveManager* GetInstance();
	static void Initialize();
	static void Finalize();

private:

	// コピー禁止
	SaveManager() = default;
	SaveManager(const SaveManager&) = delete;
	void operator=(const SaveManager&) = delete;

private:

	static SaveManager* instance_;
	bool saveOder_ = false;

public:

	static void SetSaveOder(bool flag){ instance_->saveOder_ = flag; }
	static bool GetSaveOder(){ return instance_->saveOder_; }

};