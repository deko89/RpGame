#ifndef EnGreen_H
#define EnGreen_H

#include "EnGreen/Base/Context.h"
#include "EnGreen/View/Wnd/WndGui.h"
#include "EnGreen/World/World.h"

namespace EnG
{

/// Движок.
class Engine : public Environment
{	public:
    Engine();
    ~Engine();
    bool Init();                ///< Инициализация.
    View* CreateViewWorld();    ///< Создать мир и вид по умолчанию.
    void Clear();               ///< Очистка.
    int Execute();              ///< Запуск.
    WndGui& GetWnd();           ///< Получить активное окно.
protected:
	// Переменные.
    bool bRun = false;	///< Запущен ли.
    Context context;
    MassivPtr<World> aWorld;
    WndGui wnd;
    friend Context& GetContext();
    friend SlotMemG GetFreeCamSlot();
};

extern Engine eng;

}

#endif
