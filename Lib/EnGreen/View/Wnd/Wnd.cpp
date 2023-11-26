#include "Wnd.h"

namespace EnG
{

Wnd::~Wnd()
{	Clear();
}

void Wnd::Create(const Str& name, const RectI& pos, uint32_t flag)
{
    pWnd = SDL_CreateWindow(name.c_str(), pos.x, pos.y, pos.w, pos.h, flag);
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

}
