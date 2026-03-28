#pragma once
#include <memory>
#include <string>
#include "assetManager.hpp"
#include "level.hpp"

class EditingBound
{
public:
	EditingBound() = delete;
	EditingBound(const std::string& name, int width, int height);
	
	std::string levelName;
	std::shared_ptr<Level> level;
	std::shared_ptr<AssetManager> assetManager;
};