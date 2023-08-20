#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <stdio.h>
#include "SDL.h"
#include "EnGreen/Base/Base.h"

// Константы.
Str gAppPathS;	///< Путь до приложения (с разделителем).

/// Среда - в которой работает движок.
class Environment
{	public:
	Environment();
	~Environment();
	bool IsEnvironment(); ///< Создана ли среда?
};

// Environment //////////////////////////////////////////////////////
Environment::Environment()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		printf(_("Error: %s\n"), SDL_GetError());
		return;
	}

	// Decide GL+GLSL versions
	#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	#elif defined(__APPLE__)
	// GL 3.2 Core + GLSL 150
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	#else
	// GL 3.0 + GLSL 130
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	#endif

	// From 2.0.18: Enable native IME.
	#ifdef SDL_HINT_IME_SHOW_UI
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
	#endif

	// Путь до приложения.
	char* cPath = SDL_GetBasePath();
	gAppPathS = cPath;
	SDL_free(cPath);
}
Environment::~Environment()
{
	SDL_Quit();
}
bool Environment::IsEnvironment()
{	return SDL_WasInit(0) != 0;
}

#endif
