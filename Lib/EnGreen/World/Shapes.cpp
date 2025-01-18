#include "Shapes.h"

namespace EnG
{

ImDrawList* gDrawL;

// Line //////////////////////////////////////////////////////////////
void Line::Draw() const
{
	gDrawL->AddLine(a, b, c, w);
}
// Shapes ////////////////////////////////////////////////////////////
void Shapes::Draw() const
{
	gDrawL = ImGui::GetWindowDrawList();
	for (Shape* s : *this)
		s->Draw();
}

}
