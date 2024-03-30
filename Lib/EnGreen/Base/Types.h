/** \file
	\brief Основные типы в 3d.
	\details Более специфичные типы используемые в общем моделировании, графики.
	Без привязки к библиотекам (OpenGL, Vulcan, ...).
*/

#ifndef Types_H
#define Types_H

#include <vector>
#include "EnGreen/Base/Meta/Meta.h"

namespace EnG
{

using std::vector;

/// Вершины.
class Points : public vector<Pos>
{	public:
	typedef vector<Pos> Base;

	/// Данные точек.
	struct Data
	{
		Points* points = nullptr;
		Vec3 size; ///< Размер.
		Data(Points& p);
	};

	/// Создать прямоугольник.
	void MakeQuad(Val szX, Val szY);

	/** Создать плоскость.
		param[in] szX, szY - размеры.
		param[in] sgmX, sgmY - число сегментов. */
	void MakePlane(Val szX, Val szY, ValN sgmX, ValN sgmY);

	/** Создать куб.
		param[in] s - размер. */
	void MakeCube(Val s);

	/** Создать цилиндр
		param[in] rad, height - радиус и высота;
		param[in] sgmC, sgmH - количество сегментов в круге, и по высоте;
		param[in] bCloseBottom, bCloseUp - закрыть кругом снизу, и сверху. */
	void MakeCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom = 1, bool bCloseUp = 1);

	// Модификаторы.
	/** Заострение (по оси Z).
		param[in] t - коэф. размера. 1 - заострения нет, 0 - максимальное.
		param[in] height - высота фигуры */
	void Taper(Val t, Val height);
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
	void MakeCubeIn(Val s); ///< Создать куб, который виден изнутри.
	void MakeCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom = 1, bool bCloseUp = 1);
};

/// Координаты текстуры. Предполагается что каждая координата будет соответствовать отдельной вершине.
class PlaceTex: public vector<PosTex>
{	public:
	typedef vector<PosTex> Base;

	/// Квадрат.
	void SetQuad();

	/** Плоскость.
		param[in] sgmX, sgmY - количество сегментов по осям X, Y.
		param[in] u, v - число повторений текстуры по осям X, Y. */
	void SetPlane(ValN sgmX, ValN sgmY, Val u, Val v);

	/** Цилиндр.
		param[in] sgmC - количество сегментов в круге. Должен быть чётным.
		param[in] sgmH - количество сегментов по высоте.
		param[in] u, v - число повторений текстуры. */
	void SetCylinder(ValN sgmC, ValN sgmH, Val u, Val v);
};

}

#endif
