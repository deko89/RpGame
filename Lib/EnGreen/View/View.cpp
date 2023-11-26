#include "View.h"

namespace EnG
{

View::View()
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
void View::Draw() const
{   glViewport(pos.x, pos.y, pos.w, pos.h);
    world->Draw();
}

}
