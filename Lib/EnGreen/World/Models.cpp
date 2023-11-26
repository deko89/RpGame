#include "Models.h"

namespace EnG
{

// BaseEngine ///////////////////////////////////////////////////////
void Models::Draw() const
{   for (Model* m : *this)
        m->Draw();
}

}
