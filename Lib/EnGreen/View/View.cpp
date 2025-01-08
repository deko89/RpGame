#include "View.h"

namespace EnG
{

View::View(World* w, const RectI& pos) :
    world(w),
    pos(pos)
{
}
const RectI& View::GetPos() const
{   return pos;
}
void View::SetPos(const RectI& r)
{   pos = r;
}
void View::Update(Val timeDelta)
{
}
void View::Draw()
{   glViewport(pos.x, pos.y, pos.w, pos.h);
	// Установка текущей камеры шейдерам.
	Shaders& shaders = GetShaders();
	shaders.memCam.Copy( cam.GetMatrix() );
	// Рисование.
    shaders[shCubeIn].Use();
    if (world->sky)
    	world->sky->Draw();
    world->models.Draw();
}
void View::ProcessEvent(SDL_Event& event)
{
	if (event.type == SDL_WINDOWEVENT)
	{
		if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			pos.w = event.window.data1; //tmp Пока 1 вид на весь экран. #View1
			pos.h = event.window.data2;
			cam.fAspect = (Val)pos.w / pos.h;
		}
	}
}
void View::ProcessEventInput(SDL_Event& event)
{
    cam.ProcessEventInput(event);
}
void View::ProcessStateInput(Val timeDelta)
{
    cam.ProcessStateInput(timeDelta);
}

}
