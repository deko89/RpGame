#ifndef WND_HPP
#define WND_HPP

#include "SDL.h"
#include "EnGreen/Base/Base.h"

class Wnd
{	public:
	~Wnd();
	void Create(const str& name);
	void Clear();
	SDL_Window* NativeWnd() const;
protected:
	SDL_Window* pWnd = nullptr;
};

Wnd::~Wnd()
{	SDL_DestroyWindow(pWnd);
}

void Wnd::Create(const str& name)
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    pWnd = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
}

void Wnd::Clear()
{	SDL_DestroyWindow(pWnd);
	pWnd = nullptr;
}

SDL_Window* Wnd::NativeWnd() const
{
	return pWnd;
}

#endif
