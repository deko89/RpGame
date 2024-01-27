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
    MassivPtr<View> aView;      ///< Области.
    View* view = nullptr;       ///< Активная область.
    WndG();
    void Draw(); ///< Рисование.
private:
    Time timePrev;          ///< Время последнего рисования.
};

}

#endif
