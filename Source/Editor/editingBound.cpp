#include "editingBound.hpp"

EditingBound::EditingBound(const std::string& name, int width, int height) 
{
	levelName = name;
	level = std::make_shared<Level>(width, height);
	assetManager = std::make_shared<AssetManager>();
}