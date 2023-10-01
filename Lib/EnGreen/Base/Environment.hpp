#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <stdio.h>
#include "SDL.h"
#include "Std/Base.h"

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
