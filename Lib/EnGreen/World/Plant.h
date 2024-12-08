#ifndef Plant_H
#define Plant_H

#include "Models.h"

namespace EnG
{

/// Модель ствола (или ветки).
class ModelStvol : public ModelCylinder
{	public:
	static ValN	nSgmLen,	///< Число сегментов на 1 м длины.
				nSgmRad;	///< Число сегментов на 1 м радиуса.
	Val rRad = 0.02;		///< Коэффициент радиуса на 1 м длины.
	/** Конструктор.
		param[in] aKey - ключевые точки (через которые проходит).
		param[in] bVertical - 0 горизонтальная, 1 вертикальная. */
	ModelStvol(const vector<Pos>& aKey, bool bVertical = 0);
	void Update(); ///< Обновить модель (применить новые данные).
	vector<Pos>& GetKey(); ///< Получить ключевые точки (через которые проходит).
};

}

#endif
