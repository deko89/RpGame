#ifndef WND_HPP
#define WND_HPP

#include "EnGreen/Base/Environment.hpp"

class Wnd
{	public:
	~Wnd();
	void Create(const Str& name, uint32_t flag = 0);
	void Clear();
	SDL_Window* NativeWnd() const;
protected:
	SDL_Window* pWnd = nullptr;
};

Wnd::~Wnd()
{	Clear();
}

void Wnd::Create(const Str& name, uint32_t flag)
{
    pWnd = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, flag);
}

void Wnd::Clear()
{	if (pWnd)
	{	SDL_DestroyWindow(pWnd);
		pWnd = nullptr;
	}
}

SDL_Window* Wnd::NativeWnd() const
{
	return pWnd;
}

#endif
