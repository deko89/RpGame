#ifndef Camera_H
#define Camera_H

#include "EnGreen/Base/Meta/MemG.h"

namespace EnG
{

/// Камера.
class Camera
{	public:
	Pos     pos;    ///< Позиция.
	Angle   angle;	///< Углы последовательного поворота x, y, z.
	MemG    mem;    ///< Видеопамять, где хранятся данные.
	/** Создать.
		param[in] slot - слот глобальной видеопамяти, где будут данные. */
	void Create(SlotMemG slot);
	void Update();	///< Обновление данных в видеокарте.
private:
	const Vec3 vUp = {0.0f, 0.0f, 1.0f};    ///< Мировая ось вверх.
	float fFov = pi4,		                ///< Обзор камеры.
		  fAspect = 1.33f,	                ///< Соотношение сторон.
		  fNear = 0.04f,                    ///< Ближнее отсечение.
		  fFar = 512;                       ///< Дальнее отсечение.
	Vec3 vLook; ///< Направление куда смотрит камера. Вычисляется из angle.
};

}

#endif
