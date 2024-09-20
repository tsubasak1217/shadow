#include "SaveManager.h"

// static initialize
SaveManager* SaveManager::instance_ = nullptr;



// basic
SaveManager* SaveManager::GetInstance(){

	if(!instance_){
		instance_ = new SaveManager();
	}

	return instance_;
}

void SaveManager::Initialize(){
	GetInstance();
	instance_->saveOder_ = false;
}

SaveManager::~SaveManager(){ Finalize(); }

void SaveManager::Finalize(){
	delete instance_;
	instance_ = nullptr;
}
