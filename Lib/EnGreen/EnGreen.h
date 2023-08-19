#ifndef EnGreen_H
#define EnGreen_H

#include "EnGreen/View/Wnd/WndGui.hpp"

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
    WndGui wnd;
    friend Context& GetContext();
};

extern Engine eng;

#endif
