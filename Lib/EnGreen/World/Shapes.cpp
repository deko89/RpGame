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
// ShPath ////////////////////////////////////////////////////////////
void ShPath::Draw() const
{
	using namespace Svg;
	int flag = 0;
	for (size_t pos = 0; pos < aCmd.size();)
	{	CmdType type = aCmd.Read<CmdType>(pos);
		switch (type)
		{
			case CmdType::cmdM:
			{	CmdM& c = aCmd.Read<CmdM>(pos);
				gDrawL->PathLineTo( ToGlobC(c.p) );
			}	break;
			case CmdType::cmdL:
			{	CmdL& c = aCmd.Read<CmdL>(pos);
				gDrawL->PathLineTo( ToGlobC(c.p) );
			}	break;
			case CmdType::cmdZ:
			{	flag = ImDrawFlags_Closed;
			}	break;
		}
	}
	if (style.col)
		gDrawL->PathFillConvex(style.col);
	else
		gDrawL->PathStroke(style.colStroke, flag, style.w);
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
