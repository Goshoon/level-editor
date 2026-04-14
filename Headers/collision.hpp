#pragma once

#ifndef COLLISION_HPP
#define COLLISION_HPP

struct SDL_FRect;

bool Collide(SDL_FRect& rectA, SDL_FRect& rectB);

#endif