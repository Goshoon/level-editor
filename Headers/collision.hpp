#pragma once
#include "math.hpp"

#ifndef COLLISION_HPP
#define COLLISION_HPP

struct SDL_FRect;

bool Collide(SDL_FRect& rectA, SDL_FRect& rectB);
bool Collide(vec4<float>& rectA , vec4<float>& rectB);

#endif