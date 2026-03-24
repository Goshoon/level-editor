#pragma once
#include <SDL3/SDL.h>
template<typename T>
struct vec2
{
	T x, y;
};

template<typename T>
struct vec3
{
	T x, y, z;
};

template<typename T>
struct vec4
{
	T x, y, z, w;

	operator SDL_FRect() const
    {
        return SDL_FRect{ x, y, z, w };

        /*
			Using this will create a copy, casting needs to be done
			as less as posibble unless its used few times every once
			in a while.

			This can be avoided in the future by modifying SDL3's
			source code to take vec4 as a variable.

			NOT doing this last thing also generates more ram usage
			due to the fact that everywhere you use math.hpp you will
			be including <SDL3/SDL.h>. This is heavy amd unnecessary.
        */
    }
};
