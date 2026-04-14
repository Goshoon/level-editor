#include "collision.hpp"
#include <SDL3/SDL.h>

// SDL_FRect AABB collision
bool Collide(SDL_FRect& rectA, SDL_FRect& rectB)
{
	return rectA.x < rectB.x + rectB.w
	&& rectA.x + rectA.w > rectB.x
	&& rectA.y < rectB.y + rectB.h
	&& rectA.y + rectA.h > rectB.y;
}

// Vec4<float> AABB collision
bool Collide(vec4<float>& rectA , vec4<float>& rectB)
{
	// Vec4 uses x, y, z, w (x, y, width, height)
	return rectA.x < rectB.x + rectB.z
	&& rectA.x + rectA.z > rectB.x
	&& rectA.y < rectB.y + rectB.w
	&& rectA.y + rectA.w > rectB.y;
}