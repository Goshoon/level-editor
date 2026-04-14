#include "collision.hpp"
#include <SDL3/SDL.h>

bool Collide(SDL_FRect& rectA, SDL_FRect& rectB)
{
	return rectA.x < rectB.x + rectB.w
	&& rectA.x + rectA.w > rectB.x
	&& rectA.y < rectB.y + rectB.h
	&& rectA.y + rectA.h > rectB.y;
}