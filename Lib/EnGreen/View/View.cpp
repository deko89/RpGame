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
void View::Draw()
{   glViewport(pos.x, pos.y, pos.w, pos.h);
    shaders.cubeIn.Use();
    world->sky.Draw();
    shaders.posTex.Use(); //db
    world->models.Draw();
}

}
