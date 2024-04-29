#include "Plant.h"

namespace EnG
{

// ModelStvol ////////////////////////////////////////////////////////
ValN ModelStvol::nSgmLen = 30;
ValN ModelStvol::nSgmRad = nSgmLen * 2 * pi;
const size_t iModifSpline = 1; // Позиция Modifs::Spline.
ModelStvol::ModelStvol(const vector<Pos>& aKey)
{
	modif.Make<Modifs::Taper>(0.004 / rad);
	modif.Make<Modifs::Spline>(aKey); // Соответствует iModifSpline.
	Update();
}
void ModelStvol::Update()
{
	vector<Pos>& aKey = GetKey();

	// Проверка.
	if (aKey.size() < 2)
	{
		assert(0);
		return;
	}

	// Расчёт данных.
	height = aKey.back().z;
	rad = rRad * height;
	sgmH = height * nSgmLen;
	sgmC = rad * nSgmRad;
	if (sgmC < 2) sgmC = 2;
	else if (sgmC % 2) ++sgmC; //TODO Снять ограничение цилиндра.

	// Построение.
	ModelCylinder::Update();
}
vector<Pos>& ModelStvol::GetKey()
{
	Modifs::Spline* s = dynamic_cast<Modifs::Spline*>( modif[iModifSpline] );
	assert(s);
	return s->aKey;
}

}
