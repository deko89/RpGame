#include "WndG.h"

namespace EnG
{

WndG::WndG()
{
    timePrev = system_clock::now();
}

void WndG::Draw()
{
	// Прошедшее время.
	Time timeNow = system_clock::now();
	duration<Val> dur = timeNow - timePrev;
	timePrev = timeNow;
	Val timeDelta = dur.count();
	// Рисование
	for (View* v : aView)
	{
		v->Draw();
	}
}

}
