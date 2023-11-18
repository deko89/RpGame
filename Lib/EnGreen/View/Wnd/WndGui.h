#ifndef WNDGUI_H
#define WNDGUI_H

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "imgui.h"
#include "EnGreen/View/Wnd/Wnd.h"

namespace EnG
{

class WndGui : public Wnd
{	public:
	~WndGui();
	void Create(const Str& name);	///< Создать.
	void Clear();					///< Очистить.
	void CreateGui();	///< Создать интерфейс.
	void ClearGui();	///< Удалить интерфейс.
	void ProcessEvent(SDL_Event& event); ///< Обработка события.
	void Render(); ///< Рисование.
protected:
	ImGuiIO* pIO = nullptr;
    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    void UpdateUI();
};

}

#endif
