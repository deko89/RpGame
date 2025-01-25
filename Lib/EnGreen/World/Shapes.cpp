#include "Shapes.h"

namespace EnG
{

ImDrawList* gDrawL;
/// Позиция начала View (0,0 - с учётом полей и т.п.). Глобальные координаты.
Pos2 gViewBegPos;

/// Координаты из логических в глобальные.
Pos2 ToGlobC(const Pos2& p)
{
	return gViewBegPos + p;
}

// Line //////////////////////////////////////////////////////////////
void Line::Draw() const
{
	gDrawL->AddLine(ToGlobC(a), ToGlobC(b), c, w);
}
// Shapes ////////////////////////////////////////////////////////////
void Shapes::Draw() const
{
	gDrawL = ImGui::GetWindowDrawList();
	gViewBegPos = ImGui::GetCursorScreenPos();
	for (Shape* s : *this)
		s->Draw();
}

}
