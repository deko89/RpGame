/** \file
	\brief Основные типы в 3d.
	\details Более специфичные типы используемые в общем моделировании, графики.
	Без привязки к библиотекам (OpenGL, Vulcan, ...).
*/

#include <vector>
#include "EnGreen/Base/Meta.h"

using std::vector;

/// Вершины.
class Points : public vector<Pos>
{	public:
	typedef vector<Pos> Base;

	/// Создать прямоугольник.
	void MakeQuad(Val szX, Val szY);

	/** Создать плоскость.
		param[in] szX, szY - размеры.
		param[in] sgmX, sgmY - число сегментов. */
	void MakePlane(Val szX, Val szY, ValN sgmX, ValN sgmY);

	/** Создать цилиндр
		param[in] rad, height - радиус и высота;
		param[in] sgmC, sgmH - количество сегментов в круге, и по высоте;
		param[in] bCloseBottom, bCloseUp - закрыть кругом снизу, и сверху. */
	void MakeCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom = 1, bool bCloseUp = 1);
};

/// Индексы (например точек).
typedef vector<Ind> Indexes;

/** Сетка.
	\details Геометрическая форма из отдельных треугольников. Вершин и правил их соединения в грани.
	Например, по 3 индекса для каждого треугольника. */
class Mesh
{	public:
	Points aVert; ///< Вершины.
	Indexes aInd; ///< Порядок соединения точек в грани.

	/// Создание фигур, см Points.
	void MakeQuad(Val szX, Val szY);
	void MakePlane(Val szX, Val szY, ValN sgmX, ValN sgmY);
	void MakeCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom = 1, bool bCloseUp = 1);
};
