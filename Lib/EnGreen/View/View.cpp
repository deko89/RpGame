#include "View.h"

namespace EnG
{

View::View(World* w, const RectI& pos) :
    world(w),
    pos(pos)
{   SlotMemG uCamSlot = GetFreeCamSlot();
    cam.Create(uCamSlot);
    shaders.Compile(uCamSlot);
}
const RectI& View::GetPos() const
{   return pos;
}
void View::SetPos(const RectI& r)
{   pos = r;
}
void View::Update(Val timeDelta)
{   cam.Update();
}
void View::Draw()
{   glViewport(pos.x, pos.y, pos.w, pos.h);
    shaders[shCubeIn].Use();
    world->sky.Draw();
    shaders[shPosTex].Use(); //tmp
    world->models.Draw();
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
