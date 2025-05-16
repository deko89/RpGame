#ifndef Camera_H
#define Camera_H

#include "GEng/Base/Meta/MemG.h"

namespace GEng
{

/// Камера.
class Camera
{	public:
	Pos     pos;    ///< Позиция.
	Angle   angle;	///< Углы последовательного поворота x, y, z.
	float	fFov = pi4,						///< Обзор камеры.
			fAspect = gSzWndDef.Ratio(),	///< Соотношение сторон.
			fNear = 0.04f,					///< Ближнее отсечение.
			fFar = 512;						///< Дальнее отсечение.
	Mat4 GetMatrix() const;	///< Получить матрицу положения камеры.
	void ProcessEventInput(SDL_Event& event); /// Обработка событий клавиатуры / мыши.
	void ProcessStateInput(Val timeDelta); ///< Обработка состояния клавиатуры / мыши.
private:
	const Vec3 vUp = {0.0f, 0.0f, 1.0f};    ///< Мировая ось вверх.
	Vec3 vLook; ///< Направление куда смотрит камера. Вычисляется из angle.
	void UpdateLook(); ///< Обновление вектора направления.
};

}

#endif
