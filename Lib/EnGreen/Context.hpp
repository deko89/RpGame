#ifndef CONTEXT_HPP
#define CONTEXT_HPP

/** \file
	\brief Контекст.
	Даёт доступ к графической библиотеке (можно считать что это она и есть).
*/

#include "EnGreen/Base/Meta/Meta.h"
#include "EnGreen/View/Wnd/Wnd.hpp"

/// Версия.
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
#endif

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
