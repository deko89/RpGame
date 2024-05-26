#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "SDL.h"
#include "Std/Base.h"

namespace EnG
{

// Константы.
Str gAppPathS;	///< Путь до приложения (с разделителем).

/// Среда - в которой работает движок (уровень системы, sdl).
class Environment
{	public:
	Environment();
	~Environment();
	bool IsEnvironment(); ///< Создана ли среда?
};

}

#endif
