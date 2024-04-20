#include "WndG.h"

namespace EnG
{

WndG::WndG()
{
    timePrev = system_clock::now();
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void WndG::ProcessEvent(SDL_Event& event)
{	if (view && event.type == SDL_MOUSEMOTION)
		view->ProcessEventInput(event);
    if (event.type == SDL_KEYDOWN)
    {
    	if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
    		SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode()? SDL_FALSE: SDL_TRUE);
    }
}

void WndG::Draw()
{
	// Прошедшее время.
	Time timeNow = system_clock::now();
	duration<Val> dur = timeNow - timePrev;
	timePrev = timeNow;
	Val timeDelta = dur.count();
	// Обновление активного вида.
	if (view)
		view->ProcessStateInput(timeDelta);
	// Рисование
	for (View* v : aView)
	{
		v->Update(timeDelta);
		v->Draw();
	}
}

}
