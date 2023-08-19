#ifndef CONTEXT_HPP
#define CONTEXT_HPP

/** \file
	\brief Контекст
	Основные структуры: устройство OpenGl, ввод и т.п.
*/

#include <stdio.h>
#include "EnGreen/Base/Meta.h"
#include "EnGreen/View/Wnd/Wnd.hpp"

/// Контекст графики.
class Context
{	public:
	~Context();
	static bool Init();		///< Общая инициализация.
	static void DeInit();	///< Общее закрытие.
	void Create(Wnd& wnd);	///< Создание (требует окно).
	void Clear();
	SDL_GLContext& NativeContext();
private:
	SDL_GLContext gl_context;
};

/// Получить текущий контекст.
Context& GetContext(); // Реализовано в Engine.hpp

Context::~Context()
{	Clear();
}

bool Context::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		printf(_("Error: %s\n"), SDL_GetError());
		return false;
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

	return true;
}

void Context::DeInit()
{   SDL_Quit();
}

void Context::Create(Wnd& wnd)
{
	SDL_Window* pWnd = wnd.NativeWnd();
	gl_context = SDL_GL_CreateContext(pWnd);
	SDL_GL_MakeCurrent(pWnd, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync
}

void Context::Clear()
{   SDL_GL_DeleteContext(gl_context);
}

SDL_GLContext& Context::NativeContext()
{	return gl_context;
}

#endif
