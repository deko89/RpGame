#include "Types.h"
#include <cmath>

namespace EnG
{

// Points ///////////////////////////////////////////////////////////
	// Data //////////////////////////////////////////////////////////
Points::Data::Data(Points& p) :
	aPoint(&p)
{}
	// Modifs ////////////////////////////////////////////////////////
		// Rotate /////////////////////////////////////////////////////
Points::Modifs::Rotate::Rotate(const Angle& angle) :
	angle(angle)
{}
void Points::Modifs::Rotate::Set(Points::Data& pData)
{
	pData.aPoint->Rotate(angle);
}
		// Taper /////////////////////////////////////////////////////
Points::Modifs::Taper::Taper(Val taper) :
	taper(taper)
{}
void Points::Modifs::Taper::Set(Points::Data& pData)
{
	pData.aPoint->Taper(taper, pData.size.z);
}
		// ~Taper ////////////////////////////////////////////////////
void Points::Modifs::Set(Points::Data& pData)
{
	for (Modif* m : *this)
		m->Set(pData);
}
	// ~Modifs ///////////////////////////////////////////////////////
void Points::MakeQuad(Val szX, Val szY)
{	*(Base*) this =	{	{0,		0,		0},
						{szX,	0,		0},
						{0,		szY,	0},
						{szX,	szY,	0}
					};
}
void Points::MakeCube(Val s)
{   *(Base*) this = {   {-s,-s,-s},  { s,-s,-s},  {s, s,-s},  {-s,s,-s},     // Низ.
                        {-s,-s, s},  { s,-s, s},  {s, s, s},  {-s,s, s}   }; // Верх.
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
	{	pVert = data() + (size() - (bCloseUp? 2: 1));
		pVert->x = 0; pVert->y = 0; pVert->z = 0;
	}
	// Создание крышки.
	if (bCloseUp)
	{	pVert = data() + (size() - 1);
		pVert->x = 0; pVert->y = 0; pVert->z = height;
	}
}
void Points::Rotate(const Angle& angle)
{
	Mat4 mat(1);
	mat = glm::rotate(mat, angle.z, Vec3(0, 0, 1));
	mat = glm::rotate(mat, angle.y, Vec3(0, 1, 0));
	mat = glm::rotate(mat, angle.x, Vec3(1, 0, 0));

	for (Pos& point: *this)
		point = mat * Vec4(point, 1.0);
}
void Points::Taper(Val t, Val height)
{
	Val dist = 1 - t; // Общая дистанция (на сколько всего уменьшаем).
	for (Pos& point: *this)
	{
		Val m = point.z / height; // Пройденная дистанция (коэф.).
		Val sz = 1 - m * dist; // Коэф. размера.
		point.x *= sz;
		point.y *= sz;
	}
}
/// Вычисление и построение сплайна (в 3d).
struct SplineMake
{
	const bool bPrint = 0;	///< Печать отладочной информации.

	SplineMake(vector<Pos>& aVert, const vector<Pos>& aKey) :
		aVert(aVert), aKey(aKey)
	{
		aDer.resize( aKey.size() );
	}

	/// Рассчитать сплайн. И установить точки по нему. Вдоль оси X.
	bool Do()
	{
		// Проверка.
		if ( !Check() ) return false;
		// Плоскость XY.
		CalcDer();	// Расчёт производных в ключевых точках.
		MoveVert();	// Перемещение точек.
		// Плоскость XZ.
		oY = osZ;
		CalcDer();	// Расчёт производных в ключевых точках.
		MoveVert();	// Перемещение точек.
		return true;
	}

	/// Проверить на возможность вычисления.
	bool Check()
	{
		return aKey.size() > 1;
	}
private:
	vector<Pos>& aVert;			///< Обрабатываемые вершины.
	const vector<Pos>& aKey;	///< Ключевые точки.
	Os oX = osX, oY = osY;		///< Условные оси X, Y - относительно которых сейчас строится сплайн.
	vector<Val> aDer;			///< Производные в ключевых точках (в текущей условной плоскости XY).
	size_t iVert = 0;			///< Текущая вершина.
	/// Переменные в текущем отрезке. Для формулы.
	Val x0, lineLen, k0, k1, d0, d1;

	/** Рассчитать производные (в условной плоскости XY). */
	void CalcDer()
	{
		if (bPrint) std::cout << "CalcDer oX = " << oX << ", oY = " << oY << std::endl;
		// Производная №0 (самая первая).
		const Vec2 k0( aKey[0][oX],	aKey[0][oY]	);
		const Vec2 k1( aKey[1][oX],	aKey[1][oY]	);
		aDer[0] = (k1.y - k0.y) / (k1.x - k0.x);
		if (bPrint) std::cout << "Der 0 = " << aDer[0] << std::endl;
		// Производная №1+ (стандартные).
		for (size_t i = 1; i < aKey.size() - 1; ++i)
		{
			// Ближайшие ключевые точки.
			const Vec2 k0( aKey[i - 1][oX],	aKey[i - 1][oY]	);
			const Vec2 k1( aKey[i    ][oX],	aKey[i    ][oY]	);
			const Vec2 k2( aKey[i + 1][oX],	aKey[i + 1][oY]	);
			// Прилежащие вектора.
			Vec2 v1 = k1 - k0; // До.
			Vec2 v2 = k2 - k1; // После.
			if (bPrint)
			{
				std::cout << "Calc Der " << i << std::endl;
				std::cout << "\tk0 " << k0 << "; k1 " << k1 << "; k2 " << k2
						  << "\n\tv1 " << v1 << "; v2 " << v2 << std::endl;
			}
			// Нормализация, нужно для нахождения среднего по углу.
			v1 = normalize(v1);
			v2 = normalize(v2);
			// Нахождение среднего вектора.
			Vec2 v = v1 + v2;
			if (bPrint)
				std::cout << "\tnormalize v1: " << v1 << "; normalize v2: " << v2
						  << "\n\tv: " << v << std::endl;
			// Средняя производная (между ней и ключевыми отрезками равные углы).
			aDer[i] = v.y / v.x;
			if (bPrint)
				std::cout << "Der " << i << " = " << aDer[i] <<
				" (простая " << (k2.y - k0.y) / (k2.x - k0.x) << ")" << std::endl;
		}
		// Производная №N (самая последняя).
		const size_t p = aKey.size() - 2;
		const size_t l = p + 1;
		const Vec2 kp( aKey[p][oX],	aKey[p][oY]	);
		const Vec2 kl( aKey[l][oX],	aKey[l][oY]	);
		aDer[l] = (kl.y - kp.y) / (kl.x - kp.x);
		if (bPrint) std::cout << "Der " << l << " = " << aDer[l] << std::endl;
	}

	/// Установить вершины по сплайну.
	void MoveVert()
	{
		for (iVert = 0; iVert < aVert.size(); ++iVert)
		{
			SelectLine();
			Pos& vert = aVert[iVert];
			Val r = vert[oY];
			// Смещение.
			Val w = (vert[oX] - x0) / lineLen,
				w2 = w * w, w3 = w2 * w;
			vert[oY] =	k0 * (2*w3 - 3*w2 + 1) +
						k1 * (-2*w3 + 3*w2) +
						d0 * (w3 - 2*w2 + w) +
						d1 * (w3 - w2);
			// Поворот по углу касательной.
				// Производная за w.
			Val d = 	k0 * (6*w2 - 6*w) +
						k1 * (-6*w2 + 6*w) +
						d0 * (3*w2 - 4*w + 1) +
						d1 * (3*w2 - 2*w);
			d /= lineLen; // Приводим к обычной производной за 1.
			Val a = atan(d);
			Val cosA = cos(a);
			Val sinA = cosA * d;
			//if (bPrint) std::cout << "iVert = " << iVert << " a = " << glm::degrees(a) << " cosA = " << cosA << " sinA = " << sinA << " r = " << r << std::endl;
			vert[oX] -= sinA * r;
			vert[oY] += cosA * r;
		}
	}

	/// Установить подходящий отрезок.
	bool SelectLine()
	{
		Pos& vert = aVert[iVert];

		// Текущая первая ключевая точка (и отрезок сплайна).
		size_t iKey = 0;
		for (iKey = 1; iKey < aKey.size(); ++iKey)
			if ( vert[oX] <= aKey[iKey][oX] )
				break;

		if ( iKey >= aKey.size() )
		{
			if (bPrint)
				std::cout << "Не найден отрезок: iVert = " << iVert << " vert[oX] = " << vert[oX]
						  << " X_back = " << aKey.back()[oX] << std::endl;
			iKey = aKey.size() - 2;
			//return false;
		} else
			--iKey;

		// Переменные отрезка.
		x0      = aKey[iKey][oX];
		Val x1  = aKey[iKey + 1][oX];
		lineLen = x1 - x0;

		k0 = aKey[iKey][oY];
		k1 = aKey[iKey + 1][oY];
		d0 = aDer[iKey] * lineLen;
		d1 = aDer[iKey + 1] * lineLen;

		return true;
	}
};
void Points::Spline(const vector<Pos>& aKey)
{
	SplineMake splineMake(*this, aKey);
	splineMake.Do();
}
// Mesh /////////////////////////////////////////////////////////////
void Mesh::MakeQuad(Val szX, Val szY)
{
	aVert.MakeQuad(szX, szY);
	aInd = {0, 1, 2, 1, 3, 2};
}
void Mesh::MakeCubeIn(Val s)
{
    aVert.MakeCube(s);
    aInd =  {   0,1,2, 0,2,3,  4,6,5, 4,7,6,    // Низ, верх.
                3,2,7, 2,6,7,  0,4,1, 1,4,5,    // Вперёд, назад
                0,3,4, 3,7,4,  1,6,2, 1,5,6,    // Лево, право.
            };
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
