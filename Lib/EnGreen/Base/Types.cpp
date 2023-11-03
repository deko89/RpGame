#include "Types.h"
#include <cmath>

namespace EnG
{

// Points ///////////////////////////////////////////////////////////
void Points::MakeQuad(Val szX, Val szY)
{	*(Base*) this =	{	{0,		0,		0},
						{szX,	0,		0},
						{0,		szY,	0},
						{szX,	szY,	0}
					};
}
void Points::MakePlane(Val szX, Val szY, ValN sgmX, ValN sgmY)
{	// Вычисление размера и выделение памяти.
	Ind nVertX = sgmX + 1, nVertY = sgmY + 1;
	resize(nVertX * nVertY);
	Pos* pVert = data();
	Val	vStepX = szX / sgmX, vPosX,
		vStepY = szY / sgmY, vPosY = 0;
	// Вершины.
	for (Ind y = 0; y < nVertY; ++y, vPosY += vStepY)
	{	vPosX = 0;
		for (Ind x = 0; x < nVertX; ++x, vPosX += vStepX, ++pVert)
		{	pVert->x = vPosX;
			pVert->y = vPosY;
			pVert->z = 0;
		}
	}
}
void Points::MakeCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom, bool bCloseUp)
{	// Вычисление размера и выделение памяти.
	const ValN nVertC = sgmC * (sgmH + 1);
	resize(nVertC + bCloseBottom + bCloseUp);
	Pos *pVert = data();
	const Pos *pEndC = pVert + sgmC,
			  *pEnd  = pVert + nVertC;
	// Цикл создания, по сегментам окружности.
	const Val angleStep = 2 * pi / sgmC,	// Текущий угол и шаг угла.
			  hStep = height / sgmH;		// Текущая высота и шаг.
	Val angle = 0;
	for (; pVert < pEndC; ++pVert, angle += angleStep)
	{	// Позиция внизу (на остальных уровнях будет аналогично).
		pVert->x = cos(angle) * rad;
		pVert->y = sin(angle) * rad;
		pVert->z = 0;
		// Устанавливаем данные по вертикали (на уровнях выше).
		Val h = hStep;
		for (Pos* pVertH = pVert + sgmC; pVertH < pEnd; pVertH += sgmC, h += hStep)
		{	pVertH->x = pVert->x;
			pVertH->y = pVert->y;
			pVertH->z = h;
		}
	}
	// Создание дна.
	if (bCloseBottom)
	{	pVert = data() + ((size() - bCloseUp)? 2: 1);
		pVert->x = 0; pVert->y = 0; pVert->z = 0;
	}
	// Создание крышки.
	if (bCloseUp)
	{	pVert = data() + (size() - 1);
		pVert->x = 0; pVert->y = 0; pVert->z = height;
	}
}
// Mesh /////////////////////////////////////////////////////////////
void Mesh::MakeQuad(Val szX, Val szY)
{
	aVert.MakeQuad(szX, szY);
	aInd = {0, 1, 2, 1, 3, 2};
}
void Mesh::MakePlane(Val szX, Val szY, ValN sgmX, ValN sgmY)
{
	aVert.MakePlane(szX, szY, sgmX, sgmY);
	// Расстановка индексов.
	aInd.resize(sgmX * sgmY * 6);
	Ind* pInd = aInd.data();
	const Ind nVertWidth = sgmX + 1;
	for (Ind uVert = 0, nVertEnd = nVertWidth * sgmY; uVert < nVertEnd; ++uVert)
	{	for (Ind nVertLastX = uVert + sgmX; uVert < nVertLastX; ++uVert, ++pInd)
		{	Ind uVertNextLine = uVert + nVertWidth;
			*pInd = uVert;
			*(++pInd) = uVertNextLine + 1;
			*(++pInd) = uVertNextLine;
			*(++pInd) = uVert;
			*(++pInd) = uVert + 1;
			*(++pInd) = uVertNextLine + 1;
		}
	}
}
void Mesh::MakeCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom, bool bCloseUp)
{	// Создание вершин.
	aVert.MakeCylinder(rad, height, sgmC, sgmH, bCloseBottom, bCloseUp);
	// Вычисление размера и выделение памяти для индексов.
	aInd.resize(sgmC * sgmH * 6 + ((ValN)bCloseBottom + bCloseUp) * sgmC * 3);
	Ind* pInd = aInd.data();
	for (ValN y = 0; y < sgmH; ++y)
	{	const Ind height  = sgmC * y,	   // Текущая высота.
				  heightN = height + sgmC; // Следующая высота.
		for (ValN s = 0; s < sgmC; ++s)
		{	const Ind n = (s + 1 == sgmC)? 0: s + 1; // Следующий сегмент.
			*(pInd++) = height	+ s;
			*(pInd++) = height	+ n;
			*(pInd++) = heightN	+ s;
			*(pInd++) = heightN	+ s;
			*(pInd++) = height	+ n;
			*(pInd++) = heightN	+ n;
		}
	}
	// Создание дна.
	if (bCloseBottom)
	{	const Ind iV = aVert.size() - (bCloseUp? 2: 1);
		for (Ind x = 0; x < sgmC; ++x)
		{	*(pInd++) = iV;
			*(pInd++) = (x + 1 == sgmC)? 0: x + 1; // Следующий по x.
			*(pInd++) = x;
		}
	}
	// Создание крышки.
	if (bCloseUp)
	{	const Ind iV = aVert.size() - 1, s = iV - bCloseBottom - sgmC, e = s + sgmC;
		for (Ind x = s; x < e; ++x)
		{	*(pInd++) = iV;
			*(pInd++) = x;
			*(pInd++) = (x + 1 == e)? s: x + 1; // Следующий по x.
		}
	}
}
// PlaceTex /////////////////////////////////////////////////////////
void PlaceTex::SetQuad()
{	*(Base*) this =	{	{0, 0},
						{1, 0},
						{0, 1},
						{1, 1}
					};
}
void PlaceTex::SetPlane(ValN sgmX, ValN sgmY, Val u, Val v)
{	const ValN	nVertX = sgmX + 1,
				nVertY = sgmY + 1;
	resize(nVertX * nVertY);
	PosTex* pPos = data();
	const Val	uStep = u / sgmX,
				vStep = v / sgmY;
	Val uPos, vPos = 0;
	// Вершины.
	for (ValN y = 0; y < nVertY; ++y, vPos += vStep)
	{	uPos = 0;
		for (ValN x = 0; x < nVertX; ++x, uPos += uStep, ++pPos)
		{	pPos->u = uPos;
			pPos->v = vPos;
		}
	}
}
void PlaceTex::SetCylinder(ValN sgmC, ValN sgmH, Val u, Val v)
{	assert(sgmC % 2 == 0);
	resize(sgmC * (sgmH + 1));
	PosTex* pPos = data();
	const PosTex *pEndC = pPos + sgmC,
				 *pEndH = pPos + sgmC / 2,
				 *pEnd  = pPos + size();
	// Цикл по сегментам окружности.
	const Val	uStep = u / sgmC, // Шаг u.
				vStep = v / sgmH; // Шаг v.
	u = 0;
	for (; pPos < pEndC; ++pPos)
	{	// Позиция внизу (на остальных уровнях будет аналогично).
		pPos->u = u;
		pPos->v = 0;
		// Устанавливаем данные по вертикали (на уровнях выше).
		v = vStep;
		for (PosTex* pPosH = pPos + sgmC; pPosH < pEnd; pPosH += sgmC, v += vStep)
		{	pPosH->u = u;
			pPosH->v = v;
		}
		// После середины зеркалим текстуру, чтобы к последней вершине u была 0 (первая и последняя это одна и та же вершина).
		u = pPos < pEndH ? u + uStep : u - uStep;
	}
}

}
