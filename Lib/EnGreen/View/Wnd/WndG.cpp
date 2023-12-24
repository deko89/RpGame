#include "WndG.h"

namespace EnG
{

void WndG::Draw()
{
    for (const View* v : aView)
    {   v->Draw();
    }
}

}
