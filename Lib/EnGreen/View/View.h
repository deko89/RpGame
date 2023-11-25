#ifndef View_H
#define View_H

#include "EnGreen/World/World.h"
#include "EnGreen/View/Camera.h"

namespace EnG
{

/// Вид. Область в окне показывающая мир.
class View
{	public:
	World* world = nullptr; ///< Отображаемый мир.
	Camera cam;             ///< Камера.
	const RectI& GetPos() const;
	void SetPos(const RectI& r);
	void Draw() const;
private:
	RectI pos;              ///< Позиция в окне.
};

}

#endif