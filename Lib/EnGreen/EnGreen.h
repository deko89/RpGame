#ifndef EnGreen_H
#define EnGreen_H

#include "EnGreen/Context.h"
#include "EnGreen/View/Wnd/WndGui.h"
#include "EnGreen/World/World.h"

namespace EnG
{

/// Движок.
class Engine : public Environment
{	public:
    Engine();
    ~Engine();
    bool Init();	///< Инициализация.
	void Clear();	///< Очистка.
	int Execute();	///< Запуск.
protected:
	// Переменные.
    bool bRun = false;	///< Запущен ли.
    Context context;
    MassivPtr<World> aWorld;
    WndGui wnd;
    friend Context& GetContext();
};

extern Engine eng;

}

#endif
