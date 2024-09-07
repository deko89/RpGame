#ifndef EnGreen_Math_H
#define EnGreen_Math_H

#include <vector>
#include "EnGreen/Base/Meta/Meta.h"

namespace EnG
{

using std::vector;

/// Калькулятор сплайна (в 3d).
struct SplineCalc
{
	const bool bPrint = 0;	///< Печать отладочной информации.
	/** @brief Конструктор.
		param[in] aKey - ключевые точки сплайна. Каждая следующая должна быть больше по X.
		param[in] osMain - основная ось, вдоль которой идёт цилиндр для сплайна. */
	SplineCalc(const vector<Pos>& aKey, Os osMain = osX);
	bool Check() const;		///< Проверить (правильные ли параметры на входе).
	void Calc();			///< Рассчитать необходимые общие параметры.
	Val GetLen();			///< Получить длину (по текущей оси X).
	/** @brief Получить позицию.
		@details Общая идея. Вдоль оси X есть цилиндр для сплайна.
			Сперва рассчитывается позиция центральной точки. По двум плоскостям.
			Затем позиция смещённой точки, представив что это вершина сегмента цилиндра.
			Сегмент (кольцо) сперва вращается по Y, затем по Z. Размеры сегмента не меняются, только вращение.
		param[in,out] vert - начальная позиция точки. В неё же запишется конечная позиция. */
	void CalcPos(Pos& vert);
private:
	const vector<Pos>& aKey;	///< Ключевые точки.
	/// Условные оси X, Y - относительно которых строится сплайн.
	/// Функции всегда думают что работают с осям XY.
	/// По факту их можно менять местами XYZ, YZX, ZXY. При этом совершенно ничего не меняется, всё остаётся также как будто XYZ.
	/// Можно просто думать что всегда "XYZ" = XYZ, всё так же.
	Os oX = osX, oY = osY;
	bool bXZ = 0;				///< 0 - установлена плоскость XY, 1 - XZ. См. SetPlaneXY.
	vector<Val> aDerY, aDerZ;	///< Производные в ключевых точках (в условных плоскостях "XY", "XZ").
	size_t iKey = 0;			///< Текущая ключевая точка начала отрезка.
	size_t iVert = 0;			///< Текущая вершина.
	/// Переменные в текущем отрезке (для формулы сплайна).
	Val x0, lineLen, k0, k1, d0, d1;
	/// Дополнительная смена осей при переключении плоскостей. Чтобы функции работали только с XY.
	/// Сделать условную плоскость "XY" / "XZ" текущей.
	/// Основная ось "X" не меняется (фактически она может быть Y, Z).
	void SetPlaneXY();
	void SetPlaneXZ();
	void CalcDer();			///< Рассчитать производные (в текущей плоскости "XY").
	bool SelectLine(Val x);	///< Установить подходящий отрезок для значения x (и все переменные). Вызывает также GetKD.
	void GetKD();			///< Получить только переменные для другой плоскости (k0, k1, d0, d1) текущего отрезка.
};

}

#endif



#ifdef Include_cpp

#include <cmath>
#include "glm/gtx/rotate_vector.hpp"

namespace EnG
{

// SplineCalc ////////////////////////////////////////////////////////
SplineCalc::SplineCalc(const vector<Pos>& aKey, Os osMain) :
	aKey(aKey)
{
	aDerY.resize( aKey.size() );
	aDerZ.resize( aKey.size() );
	// Установка осей.
	oX = osMain;
	switch (osMain)
	{	case osX:	oX = osY;	break;
		case osY:	oY = osZ;	break;
		case osZ:	oY = osX;	break;
	}
}
bool SplineCalc::Check() const
{
	return aKey.size() > 1;
}
Val SplineCalc::GetLen()
{
	return aKey.back()[oX];
}
void SplineCalc::SetPlaneXY()
{
	bXZ = 0;
	switch (oX)
	{
		case osX: oY = osY; break;
		case osY: oY = osZ; break;
		case osZ: oY = osX; break;
	}
}
void SplineCalc::SetPlaneXZ()
{
	bXZ = 1;
	switch (oX)
	{
		case osX: oY = osZ; break;
		case osY: oY = osX; break;
		case osZ: oY = osY; break;
	}
}
bool SplineCalc::SelectLine(Val x)
{
	// Поиск начальной ключевой точки (отрезка сплайна).
	for (iKey = 1; iKey < aKey.size(); ++iKey)
		if ( x <= aKey[iKey][oX] )
			break;

	if ( iKey >= aKey.size() )
	{
		if (bPrint)
			std::cout << "Не найден отрезок: x = " << x
					  << " X_back = " << aKey.back()[oX] << std::endl;
		iKey = aKey.size() - 2;
		//return false;
	} else
		--iKey;

	// Переменные отрезка.
	x0      = aKey[iKey][oX];
	Val x1  = aKey[iKey + 1][oX];
	lineLen = x1 - x0;

	GetKD();

	return true;
}
void SplineCalc::GetKD()
{
	k0 = aKey[iKey][oY];
	k1 = aKey[iKey + 1][oY];
	vector<Val>& aDer = bXZ? aDerZ: aDerY;
	d0 = aDer[iKey] * lineLen;
	d1 = aDer[iKey + 1] * lineLen;
}

}

#endif
