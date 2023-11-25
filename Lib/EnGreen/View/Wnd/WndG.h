#ifndef WndG_H
#define WndG_H

#include "Std/MassivPtr.h"
#include "EnGreen/View/Wnd/Wnd.h"
#include "EnGreen/View/View.h"

namespace EnG
{

/// Окно с графикой.
class WndG : public Wnd
{	public:
    MassivPtr<View> aView;
    void Draw() const; ///< Рисование.
};

}

#endif