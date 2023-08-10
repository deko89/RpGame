#ifndef EnGreen_H
#define EnGreen_H

#include "EnGreen/WndGui.hpp"

/// Движок.
class Engine
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
    WndGui wnd;
    friend Context& GetContext();
};

extern Engine eng;

#endif