#ifndef WNDG_HPP
#define WNDG_HPP

#include "EnGreen/View/Wnd/Wnd.hpp"
#include "EnGreen/Context.hpp"

/// Графическое окно (с 2d/3d графикой).
class WndG : public Wnd
{	public:
	Context context;
	void Create(const Str& name);	///< Создать.
	void Clear();					///< Очистить.
	void Draw();					///< Рисование.
protected:
};

void WndG::Create(const Str& name)
{
    Wnd::Create(name);
    context.Create(*this);
}
void WndG::Clear()
{
	context.Clear();
	Wnd::Clear();
}
void WndG::Draw()
{

}

#endif
