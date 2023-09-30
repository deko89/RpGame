#ifndef CONTEXT_HPP
#define CONTEXT_HPP

/** \file
	\brief Контекст
	Основные структуры: устройство OpenGl, ввод и т.п.
*/

#include "EnGreen/Base/Meta/Meta.h"
#include "EnGreen/View/Wnd/Wnd.hpp"

/// Контекст графики.
class Context
{	public:
	~Context();
	void Create(Wnd& wnd);	///< Создание (требует окно).
	void Clear();
	SDL_GLContext& NativeContext();
private:
	SDL_GLContext gl_context = 0;
};

/// Получить текущий контекст.
Context& GetContext(); // Реализовано в Engine.hpp

Context::~Context()
{	Clear();
}

void Context::Create(Wnd& wnd)
{
	SDL_Window* pWnd = wnd.NativeWnd();
	gl_context = SDL_GL_CreateContext(pWnd);
	SDL_GL_MakeCurrent(pWnd, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync
}

void Context::Clear()
{	if (gl_context)
	{	SDL_GL_DeleteContext(gl_context);
		gl_context = 0;
	}
}

SDL_GLContext& Context::NativeContext()
{	return gl_context;
}

#endif
