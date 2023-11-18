#include "WndG.h"

namespace EnG
{

void WndG::Draw() const
{
    for (const View* v : aView)
    {   v->Draw();
    }
}

}
