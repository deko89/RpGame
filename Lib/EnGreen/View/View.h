#ifndef View_H
#define View_H

#include "EnGreen/Base/Meta/Shader.h"
#include "EnGreen/World/World.h"
#include "EnGreen/View/Camera.h"

namespace EnG
{

/// Вид. Область в окне показывающая мир.
class View
{	public:
	World* world = nullptr; ///< Отображаемый мир.
	Camera cam;             ///< Камера.
	Shaders shaders;        ///< Шейдеры. Им нужна глобальная позиция камеры (иначе каждый шейдер будет хранит её). Чтобы иметь возможность рендерить параллельно, и не переписывать её, они у каждого вида.
	View(World* w, const RectI& pos);
	const RectI& GetPos() const;
	void SetPos(const RectI& r);
	void Update(Val timeDelta); ///< Обновить.
	void Draw();
	void ProcessEventInput(SDL_Event& event); ///< Обработка события клавиатуры / мыши.
	void ProcessStateInput(Val timeDelta); ///< Обработка состояния клавиатуры / мыши.
private:
	RectI pos;              ///< Позиция в окне.
};

}

#endif
