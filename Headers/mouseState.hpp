#pragma once
#include "math.hpp"
struct MouseState
{
    vec2<float> f_mousePosition;
    bool mouseButtonLeft = false;
	bool mouseButtonRight = false;
    bool mouseWheelUp = false;
    bool mouseWheelDown = false;
};