#include "EnGreen/EnGreen.h"

#ifdef One_Translation_Unit
	#include "EnGreen/EnGreen.cpp"
#endif

using namespace EnG;

int main()
{
	if (eng.Init() == false)
		return -1;

    // Настройка.
    View* view = eng.CreateViewWorld();
    // Установка камеры.
    view->cam.pos = {0, -3, 1};
    view->cam.angle = {0, 0, pi/2};
    // Создание текстуры.
    static Texture tex;
    tex.Load("SkyBox/clouds1_0.jpg");
    // Создание модели.
    ModelCylinder* mod = new ModelCylinder(0.3, 2, 8, 4);
    mod->SetTexture(tex);
    view->world->models.Add(mod);

	eng.Execute();

	return 0;
}
