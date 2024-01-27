#include "WndG.h"

namespace EnG
{

WndG::WndG()
{
    timePrev = system_clock::now();
}

void WndG::ProcessEvent(SDL_Event& event)
{	if (view)
		view->ProcessEventInput(event);
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
