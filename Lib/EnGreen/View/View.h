#ifndef View_H
#define View_H

#include "EnGreen/World/World.h"
#include "EnGreen/View/Camera.h"
#include "EnGreen/World/Shapes.h"

namespace EnG
{

/// Вид. Область в окне показывающая мир.
class View
{	public:
	World* world = nullptr; ///< Отображаемый мир.
	Camera cam;             ///< Камера.
	Shapes aShape;			///< Интерфейс и 2d фигуры.
	View(World* w, const RectI& pos);
	const RectI& GetPos() const;
	void SetPos(const RectI& r);
	void Update(Val timeDelta); ///< Обновить.
	void Draw();
	void ProcessEvent(SDL_Event& event); ///< Обработка события.
	void ProcessEventInput(SDL_Event& event); ///< Обработка события клавиатуры / мыши.
	void ProcessStateInput(Val timeDelta); ///< Обработка состояния клавиатуры / мыши.
private:
	RectI pos;              ///< Позиция в окне.
};

}

#endif
