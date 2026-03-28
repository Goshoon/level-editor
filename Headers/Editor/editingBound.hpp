#pragma once
#include <memory>
#include "assetManager.hpp"
#include "level.hpp"

class EditingBound
{
public:
	EditingBound();
	std::shared_ptr<Level> level;
	std::shared_ptr<AssetManager> assetManager;
};