#ifndef Shapes_H
#define Shapes_H

#include "EnGreen/Base/Meta/Meta.h"
#include "imgui.h"
#include "Std/MassivPtr.h"
#define M_Svg_OwnTypes
namespace EnG {typedef ImVec2 Pos2;}
namespace Svg {using namespace EnG;}
#include "Std/Svg.h"

namespace EnG
{

/// Базовая 2d фигура.
class Shape
{	public:
	virtual ~Shape() {}
	virtual void Draw() const = 0;	///< Рисование.
};

/// Линия.
class Line : public Shape
{	public:
	Pos2 a, b;		///< Позиция.
	Val w;			///< Ширина.
	Color c;		///< Цвет.
	Line() {}
	Line(Pos2 a, Pos2 b, Val w, Color c) : a(a), b(b), w(w), c(c) {}
	virtual void Draw() const override;
};

/** Путь (svg).
	\details Фигура - многоугольник, полилиния, сплайн. */
class ShPath : public Shape, public Svg::ShapePath
{	public:
	Svg::ShapeStyle style;
	virtual void Draw() const override;
};

/// 2д фигуры.
class Shapes : public MassivPtr<Shape>
{	public:
	typedef MassivPtr<Shape> Base;
	void Draw() const;
};

}

#endif
