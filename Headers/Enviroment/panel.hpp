#pragma once
#include "math.hpp"

class Panel
{
public:
	void Render(const vec2<float>& area) = 0;
};