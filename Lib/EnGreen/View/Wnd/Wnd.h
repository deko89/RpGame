#ifndef WND_H
#define WND_H

#include "EnGreen/Base/Environment.h"

namespace EnG
{

class Wnd
{	public:
	~Wnd();
	void Create(const Str& name, uint32_t flag = 0);
	void Clear();
	SDL_Window* NativeWnd() const;
protected:
	SDL_Window* pWnd = nullptr;
};

}

#endif
